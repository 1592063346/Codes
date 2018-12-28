#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int sigma, n, bestp[N], a[N], c[N], x[N], y[N], sa[N], suffix_rank[N], height[N], f[N][20], logv[N];
char s[N];

#define lo (o<<1)
#define ro (o<<1|1)

int id[N << 2];

void build(int l, int r, int o) {
  if (l == r) {
    id[o] = sa[l];
  } else {
    int mid = l + r >> 1;
    build(l, mid, lo);
    build(mid + 1, r, ro);
    id[o] = min(id[lo], id[ro]);
  }
}

int query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return id[o];
  } else {
    int mid = l + r >> 1, result = n + 1;
    if (ql <= mid) {
      cmin(result, query(l, mid, lo, ql, qr));
    }
    if (qr > mid) {
      cmin(result, query(mid + 1, r, ro, ql, qr));
    }
    return result;
  }
}

void get_sa(int m) {
  for (int i = 0; i < n; ++i) {
    ++c[x[i] = a[i]];
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
    p = 1, x[sa[0]] = 0;
    for (int i = 1; i < n; ++i) {
      x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p - 1 : p++;
    }
    if (p >= n) {
      break;
    }
    m = p;
  }
}

void get_height() {
  for (int i = 0; i < n; ++i) {
    suffix_rank[sa[i]] = i;
  }
  int k = 0;
  for (int i = 0; i < n; ++i) {
    k -= k ? 1 : 0;
    if (!suffix_rank[i]) {
      continue;
    }
    int j = sa[suffix_rank[i] - 1];
    for (; a[i + k] == a[j + k]; ++k);
    height[suffix_rank[i]] = k;
  }
  for (int i = 0; i < n; ++i) {
    f[i][0] = height[i];
  }
  for (int i = 2; i <= n; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int j = 1; (1 << j) <= n; ++j) {
    for (int i = 0; i + (1 << j) - 1 < n; ++i) {
      f[i][j] = min(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
    }
  }
}

int query(int x, int y) {
  x = suffix_rank[x];
  y = suffix_rank[y];
  if (x > y) {
    swap(x, y);
  }
  ++x;
  int k = logv[y - x + 1];
  return min(f[x][k], f[y - (1 << k) + 1][k]);
}

int main() {
  scanf("%d%d", &sigma, &n);
  if (sigma == 26) {
    scanf("%s", s);
    for (int i = 0; i < n; ++i) {
      a[i] = s[i] - 'a';
    }
  } else {
    vector<int> h;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      h.push_back(a[i]);
    }
    sort(h.begin(), h.end());
    h.erase(unique(h.begin(), h.end()), h.end());
    sigma = h.size();
    for (int i = 0; i < n; ++i) {
      a[i] = lower_bound(h.begin(), h.end(), a[i]) - h.begin();
    }
  }
  get_sa(sigma);
  get_height();
  build(0, n - 1, 1);
  int maxp = 0;
  for (int i = 0; i < n; ++i) {
    int p = sa[i];
    for (int i = maxp + 1; i <= n - p; ++i) {
      bestp[i] = p;
    }
    cmax(maxp, n - p);
  }
  for (int i = 1; i <= n; ++i) {
    int l = 0, r = suffix_rank[bestp[i]], ql, qr;
    while (l ^ r) {
      int mid = l + r >> 1;
      if (query(sa[mid], bestp[i]) >= i) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    ql = l;
    l = suffix_rank[bestp[i]], r = n - 1;
    while (l ^ r) {
      int mid = (l + r >> 1) + 1;
      if (query(sa[mid], bestp[i]) >= i) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    qr = l;
    printf("%d%c", query(0, n - 1, 1, ql, qr) + 1, " \n"[i == n]);
  }
  return 0;
}
