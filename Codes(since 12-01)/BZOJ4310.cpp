#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, k, sa[N], x[N], y[N], c[N], suffix_rank[N], height[N][21], logv[N], total[N];
char str[N];

void build_sa(int m) {
  for (int i = 0; i < n; ++i) {
    ++c[x[i] = str[i]];
  }
  for (int i = 1; i < m; ++i) {
    c[i] += c[i - 1];
  }
  for (int i = n - 1; ~i; --i) {
    sa[--c[x[i]]] = i;
  }
  for (int k = 1; k <= n; k <<= 1) {
    int p = 0;
    for (int i = n - 1; i >= n - k; --i) {
      y[p++] = i;
    }
    for (int i = 0; i < n; ++i) {
      if (sa[i] >= k) {
        y[p++] = sa[i] - k;
      }
    }
    fill(c, c + m, 0);
    for (int i = 0; i < n; ++i) {
      ++c[x[y[i]]];
    }
    for (int i = 1; i < m; ++i) {
      c[i] += c[i - 1];
    }
    for (int i = n - 1; ~i; --i) {
      sa[--c[x[y[i]]]] = y[i];
    }
    swap(x, y);
    x[sa[0]] = 0;
    p = 1;
    for (int i = 1; i < n; ++i) {
      x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p - 1 : p++;
    }
    if (p >= n) {
      break;
    }
    m = p;
  }
}

void build_height() {
  for (int i = 2; i <= n; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int i = 0; i < n; ++i) {
    suffix_rank[sa[i]] = i;
  }
  for (int i = 0, k = 0; i < n; ++i) {
    k -= k ? 1 : 0;
    if (!suffix_rank[i]) {
      continue;
    }
    int j = sa[suffix_rank[i] - 1];
    for (; str[i + k] == str[j + k]; ++k);
    height[suffix_rank[i]][0] = k;
  }
  for (int j = 1; (1 << j) <= n; ++j) {
    for (int i = 0; i + (1 << j) - 1 < n; ++i) {
      height[i][j] = min(height[i][j - 1], height[i + (1 << j - 1)][j - 1]);
    }
  }
}

int lcp(int x, int y) {
  if (x == y) {
    return n - x;
  } else {
    x = suffix_rank[x];
    y = suffix_rank[y];
    if (x > y) {
      swap(x, y);
    }
    ++x;
    int k = logv[y - x + 1];
    return min(height[x][k], height[y - (1 << k) + 1][k]);
  }
}

pair<int, int> find(long long k) {
  for (int i = 0; i < n; ++i) {
    if (k <= total[i]) {
      int p = sa[i];
      return {p, p + height[i][0] - 1 + (int) k};
    } else {
      k -= total[i];
    }
  }
}

bool bigger(pair<int, int> sub1, pair<int, int> sub2) {
  int len1 = sub1.second - sub1.first + 1;
  int len2 = sub2.second - sub2.first + 1;
  int len_lcp = min(min(len1, len2), lcp(sub1.first, sub2.first));
  if (len_lcp == len1) {
    return false;
  }
  if (len_lcp == len2) {
    return true;
  }
  return str[sub1.first + len_lcp] > str[sub2.first + len_lcp];
}

int check(pair<int, int> substring) {
  int cut = 0;
  for (int i = n - 1, j = n - 1; ~i; --i) {
    if (bigger({i, j}, substring)) {
      ++cut;
      j = i;
    }
  }
  return cut;
}

void print(pair<int, int> substring) {
  for (int i = substring.first; i <= substring.second; ++i) {
    printf("%c", str[i]);
  }
  puts("");
}

int main() {
  scanf("%d%s", &k, str);
  n = strlen(str);
  build_sa('z' + 1);
  build_height();
  long long l = 0, r = 0;
  map<char, bool> appeared;
  for (int i = 0; i < n; ++i) {
    if (!appeared.count(str[i])) {
      appeared[str[i]] = true;
      ++l;
    }
  }
  for (int i = 0; i < n; ++i) {
    int p = sa[i];
    total[i] = n - p - height[i][0];
    r += total[i];
  }
  while (l != r) {
    long long mid = l + r >> 1;
    if (check(find(mid)) < k) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  print(find(l));
  return 0;
}
