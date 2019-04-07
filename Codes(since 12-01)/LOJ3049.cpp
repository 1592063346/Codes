#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10;

int t, tt, n, na, nb, nc, number[N], x[N], y[N], suffix_array[N], suffix_rank[N], height[20][N], logv[N], id[N << 2], degree[N * 40];
long long f[N * 40];
vector<pair<int, int>> adj[N * 40];
char s[N];

void build_sa(int m) {
  fill(number, number + m, 0);
  for (int i = 0; i < n; ++i) {
    ++number[x[i] = s[i]];
  }
  for (int i = 1; i < m; ++i) {
    number[i] += number[i - 1];
  }
  for (int i = n - 1; ~i; --i) {
    suffix_array[--number[x[i]]] = i;
  }
  for (int k = 1; k <= n; k <<= 1) {
    int p = 0;
    for (int i = n - 1; i >= n - k; --i) {
      y[p++] = i;
    }
    for (int i = 0; i < n; ++i) {
      if (suffix_array[i] >= k) {
        y[p++] = suffix_array[i] - k;
      }
    }
    fill(number, number + m, 0);
    for (int i = 0; i < n; ++i) {
      ++number[x[y[i]]];
    }
    for (int i = 1; i < m; ++i) {
      number[i] += number[i - 1];
    }
    for (int i = n - 1; ~i; --i) {
      suffix_array[--number[x[y[i]]]] = y[i];
    }
    swap(x, y);
    p = 1;
    x[suffix_array[0]] = 0;
    for (int i = 1; i < n; ++i) {
      x[suffix_array[i]] = y[suffix_array[i]] == y[suffix_array[i - 1]] && y[suffix_array[i] + k] == y[suffix_array[i - 1] + k] ? p - 1 : p++;
    }
    if (p >= n) {
      break;
    }
    m = p;
  }
}

void build_height() {
  for (int i = 0; i < n; ++i) {
    suffix_rank[suffix_array[i]] = i;
  }
  for (int i = 0, k = 0; i < n; ++i) {
    if (k) {
      --k;
    }
    if (suffix_rank[i]) {
      int j = suffix_array[suffix_rank[i] - 1];
      while (s[i + k] == s[j + k]) {
        ++k;
      }
      height[0][suffix_rank[i]] = k;
    }
  }
  for (int i = 2; i <= n; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= n; ++i) {
    for (int j = 0; j + (1 << i) - 1 < n; ++j) {
      height[i][j] = min(height[i - 1][j], height[i - 1][j + (1 << i - 1)]);
    }
  }
}

int get_lcp(int x, int y) {
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
    return min(height[k][x], height[k][y - (1 << k) + 1]);
  }
}

void add_edge(int u, int v, int w = 0) {
  adj[u].emplace_back(v, w);
  ++degree[v];
}

void modify(int l, int r, int o, int p, int father, int x) {
  if (id[o]) {
    add_edge(t + 1, id[o]);
  }
  id[o] = ++t;
  if (father) {
    add_edge(father, id[o]);
  }
  if (l == r) {
    add_edge(id[o], x);
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, o << 1, p, id[o], x);
    } else {
      modify(mid + 1, r, o << 1 | 1, p, id[o], x);
    }
  }
}

void solve(int l, int r, int o, int ql, int qr, int x) {
  if (ql <= l && r <= qr) {
    if (id[o]) {
      add_edge(x, id[o]);
    }
  } else {
    int mid = l + r >> 1;
    if (qr <= mid) {
      solve(l, mid, o << 1, ql, qr, x);
    } else if (ql > mid) {
      solve(mid + 1, r, o << 1 | 1, ql, qr, x);
    } else {
      solve(l, mid, o << 1, ql, qr, x);
      solve(mid + 1, r, o << 1 | 1, ql, qr, x);
    }
  }
}

struct info_t {
  int l, r, id;

  info_t() {}
  info_t(int l, int r, int id): l(l), r(r), id(id) {}

  bool operator < (const info_t& a) const {
    return r - l > a.r - a.l;
  }
};

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%s", s);
    n = strlen(s);
    build_sa('z' + 1);
    build_height();
    scanf("%d", &na);
    vector<info_t> a(na);
    for (int i = 0; i < na; ++i) {
      scanf("%d%d", &a[i].l, &a[i].r);
      --a[i].l;
      --a[i].r;
      a[i].id = i; 
    }
    scanf("%d", &nb);
    vector<info_t> b(nb);
    for (int i = 0; i < nb; ++i) {
      scanf("%d%d", &b[i].l, &b[i].r);
      --b[i].l;
      --b[i].r;
      b[i].id = i;
    }
    vector<int> pa(na), pb(nb);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < na; ++i) {
      pa[a[i].id] = i;
    }
    for (int i = 0; i < nb; ++i) {
      pb[b[i].id] = i;
    }
    vector<int> ida(na), idb(nb);
    for (int i = 0; i < na; ++i) {
      ida[i] = ++t;
    }
    for (int i = 0; i < nb; ++i) {
      idb[i] = ++t;
    }
    for (int i = 0, j = 0; j < nb; ++j) {
      for (; i < na && a[i].r - a[i].l >= b[j].r - b[j].l; ++i) {
        modify(0, n - 1, 1, suffix_rank[a[i].l], 0, ida[i]);
      }
      int l, r, ql, qr, len = b[j].r - b[j].l + 1;
      l = 0;
      r = suffix_rank[b[j].l];
      while (l != r) {
        int mid = l + r >> 1;
        if (get_lcp(suffix_array[mid], b[j].l) >= len) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      ql = l;
      l = suffix_rank[b[j].l];
      r = n - 1;
      while (l != r) {
        int mid = (l + r >> 1) + 1;
        if (get_lcp(suffix_array[mid], b[j].l) >= len) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }
      qr = l;
      solve(0, n - 1, 1, ql, qr, idb[j]);
    }
    scanf("%d", &nc);
    for (int i = 0; i < nc; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      --x;
      --y;
      x = pa[x];
      y = pb[y];
      add_edge(ida[x], idb[y], a[x].r - a[x].l + 1);
    }
    queue<int> que;
    for (int i = 1; i <= t; ++i) {
      if (degree[i] == 0) {
        que.push(i);
      }
    }
    int all = 0;
    long long answer = 0;
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      ++all;
      for (auto y : adj[x]) {
        f[y.first] = max(f[y.first], f[x] + y.second);
        if (--degree[y.first] == 0) {
          que.push(y.first);
        }
      }
    }
    for (int i = 0; i < na; ++i) {
      answer = max(answer, a[i].r - a[i].l + 1 + f[ida[i]]);
    }
    printf("%lld\n", all == t ? answer : -1);
    for (int i = 1; i <= t; ++i) {
      adj[i].clear();
      degree[i] = f[i] = 0;
    }
    memset(id, 0, sizeof id);
    t = 0;
  }
  return 0;
}
