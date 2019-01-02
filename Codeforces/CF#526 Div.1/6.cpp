#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, block = 400;

int n, k, q, a[N], b[N], c[N], endv[N], result[N], id[N], pos[N], num[N], total, answer;
vector<vector<int>> team[500];
vector<int> team_v[500];

void init(bool common) {
  if (common) {
    for (int i = 0; i < k; ++i) {
      int value = 0;
      for (int j = !i ? k : i; j <= n; j += k) {
        value ^= c[j];
        if (value) {
          ++result[i];
        }
        if (j + k > n) {
          endv[i] = !value;
        }
      }
      answer += result[i];
      total += endv[i];
    }
  } else {
    for (int i = 0; i < n; ++i) {
      id[i] = i / block;
    }
    for (int i = 0; i < k; ++i) {
      int t = 0;
      for (int j = !i ? k : i; j <= n; j += k) {
        pos[j] = t++;
      }
      num[i] = t;
      vector<int> empty_vec(1 << 14, 0);
      for (int j = 0; j <= id[t - 1]; ++j) {
        team[i].push_back(empty_vec);
      }
      team_v[i].resize(team[i].size());
      int value = 0;
      for (int j = !i ? k : i; j <= n; j += k) {
        value ^= c[j];
        ++team[i][id[pos[j]]][value];
        if (j + k > n || id[pos[j]] != id[pos[j + k]]) {
          team_v[i][id[pos[j]]] = value;
          value = 0;
        }
      }
      result[i] = num[i];
      for (int j = 0; j < team[i].size(); ++j) {
        result[i] -= team[i][j][value];
        value ^= team_v[i][j];
      }
      endv[i] = !value;
      answer += result[i];
      total += endv[i];
    }
  }
}

void modify(bool common, int i, int p) {
  total -= endv[i];
  answer -= result[i];
  if (common) {
    result[i] = 0;
    int value = 0;
    for (int j = !i ? k : i; j <= n; j += k) {
      value ^= c[j];
      if (value) {
        ++result[i];
      }
      if (j + k > n) {
        endv[i] = !value;
      }
    }
  } else {
    result[i] = num[i];
    int ind = id[pos[p]];
    fill(team[i][ind].begin(), team[i][ind].end(), 0);
    int l = p, r = p;
    for (; l > 0 && id[pos[l]] == ind; l -= k);
    for (; r <= n && id[pos[r]] == ind; r += k);
    l += k;
    r -= k;
    int value = 0;
    for (int j = l; j <= r; j += k) {
      value ^= c[j];
      ++team[i][ind][value];
    }
    team_v[i][ind] = value;
    value = 0;
    for (int j = 0; j < team[i].size(); ++j) {
      result[i] -= team[i][j][value];
      value ^= team_v[i][j];
    }
    endv[i] = !value;
  }
  answer += result[i];
  total += endv[i];
}

int main() {
  scanf("%d%d%d", &n, &k, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &b[i]);
  }
  ++n;
  for (int i = 1; i <= n; ++i) {
    c[i] = a[i] ^ a[i - 1] ^ b[i] ^ b[i - 1];
  }
  init(k > block);
  printf("%d\n", total == k ? answer : -1);
  while (q--) {
    char type[2];
    int p, v;
    scanf("%s%d%d", type, &p, &v);
    if (*type == 'a') {
      a[p] = v;
    } else {
      b[p] = v;
    }
    c[p] = a[p] ^ a[p - 1] ^ b[p] ^ b[p - 1];
    ++p;
    c[p] = a[p] ^ a[p - 1] ^ b[p] ^ b[p - 1];
    --p;
    modify(k > block, p % k, p);
    ++p;
    modify(k > block, p % k, p);
    printf("%d\n", total == k ? answer : -1);
  }
  return 0;
}
