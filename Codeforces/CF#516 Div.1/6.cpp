#include<bits/stdc++.h>

using namespace std;

#define rg register

template<typename T> inline bool checkMax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}

const int N = 5e5 + 10;

int n, c[N], x[N], y[N], sa[N], _rank[N], height[N], f[N][20], logv[N], g[N];
char s[N];

inline void get_sa(int m) {
  for (rg int i = 0; i < n; ++i) {
    ++c[x[i] = s[i]];
  }
  for (rg int i = 1; i < m; ++i) {
    c[i] += c[i - 1];
  }
  for (rg int i = n - 1; ~i; --i) {
    sa[--c[x[i]]] = i;
  }
  for (rg int k = 1; k <= n; k <<= 1) {
    int p = 0;
    for (rg int i = n - 1; i >= n - k; --i) {
      y[p++] = i;
    }
    for (rg int i = 0; i < n; ++i) {
      if (sa[i] >= k) {
        y[p++] = sa[i] - k;
      }
    }
    fill(c, c + m, 0);
    for (rg int i = 0; i < n; ++i) {
      ++c[x[y[i]]];
    }
    for (rg int i = 1; i < m; ++i) {
      c[i] += c[i - 1];
    }
    for (rg int i = n - 1; ~i; --i) {
      sa[--c[x[y[i]]]] = y[i];
    }
    swap(x, y);
    p = 1, x[sa[0]] = 0;
    for (rg int i = 1; i < n; ++i) {
      x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p - 1 : p++;
    }
    if (p >= n) {
      break;
    }
    m = p;
  }
}

inline void get_height() {
  for (rg int i = 0; i < n; ++i) {
    _rank[sa[i]] = i;
  }
  int k = 0;
  for (rg int i = 0; i < n; ++i) {
    k -= k ? 1 : 0;
    if (!_rank[i]) {
      continue;
    }
    int j = sa[_rank[i] - 1];
    for (; s[i + k] == s[j + k]; ++k);
    height[_rank[i]] = k;
  }
  for (rg int i = 0; i < n; ++i) {
    f[i][0] = height[i];
  }
  for (rg int i = 2; i <= n; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (rg int j = 1; (1 << j) <= n; ++j) {
    for (rg int i = 0; i + (1 << j) - 1 < n; ++i) {
      f[i][j] = min(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
    }
  }
}

inline int query(int x, int y) {
  x = _rank[x];
  y = _rank[y];
  if (x > y) {
    swap(x, y);
  }
  ++x;
  int k = logv[y - x + 1];
  return min(f[x][k], f[y - (1 << k) + 1][k]);
}

#define lo (o<<1)
#define ro (o<<1|1)

int maxv[N << 2];

inline void modify(int l, int r, int o, int p, int v) {
  if (l == r) {
    maxv[o] = v;
  } else {
    int mid = l + r >> 1;
    (p <= mid) ? modify(l, mid, lo, p, v) : modify(mid + 1, r, ro, p, v);
    maxv[o] = max(maxv[lo], maxv[ro]);
  }
}

inline int query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return maxv[o];
  } else {
    int mid = l + r >> 1, res = 0;
    if (ql <= mid) {
      checkMax(res, query(l, mid, lo, ql, qr));
    } if (qr > mid) {
      checkMax(res, query(mid + 1, r, ro, ql, qr));
    }
    return res;
  }
}

inline bool binary_search(int p, int len) {
  int l = 0, r = _rank[p], ql, qr;
  while (l ^ r) {
    int mid = l + r >> 1;
    if (query(sa[mid], p) >= len) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  ql = l;
  l = _rank[p], r = n - 1;
  while (l ^ r) {
    int mid = (l + r >> 1) + 1;
    if (query(sa[mid], p) >= len) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  qr = l;
  return query(0, n - 1, 1, ql, qr) >= len;
}

inline bool check(int p, int len) {
  --len;
  return binary_search(p, len) | binary_search(p + 1, len);
}

int main() {
  scanf("%d%s", &n, s);
  get_sa('z' + 1);
  get_height();
  int ans = 0;
  for (rg int i = n - 1, p = n - 1, last_val = 0; ~i; --i) {
    for (++last_val; !check(i, last_val); --last_val, modify(0, n - 1, 1, _rank[p], g[p]), --p);
    checkMax(ans, g[i] = last_val);
  }
  printf("%d\n", ans);
  return 0;
}
