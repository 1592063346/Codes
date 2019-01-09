#include<bits/stdc++.h>

using namespace std;

template<typename T> inline void read(T& x) {
  char c = getchar();
  bool f = false;
  for (x = 0; !isdigit(c); c = getchar()) {
    if (c == '-') {
      f = true;
    }
  }
  for (; isdigit(c); c = getchar()) {
    x = x * 10 + c - '0';
  }
  if (f) {
    x = -x;
  }
}

template<typename T, typename... U> inline void read(T& x, U&... y) {
  read(x), read(y...);
}

const int N = 2e5 + 10;

int tt, n, q, c[N], dfn[N], rdfn[N], depth[N], dfn_out[N], dfn_t, first_p[N], id[N][18], d[N][18], total, logv[N], root[N], t, sum[N * 40], lo[N * 40], ro[N * 40];
vector<int> graph[N], depth_set[N];
set<int> color_set[N];

void rmq_add(int u) {
  ++total;
  id[total][0] = u;
  d[total][0] = depth[u];
}

void dfs(int u) {
  dfn[u] = ++dfn_t;
  rdfn[dfn_t] = u;
  depth_set[depth[u]].push_back(u);
  rmq_add(u);
  first_p[u] = total;
  for (int i = 0; i < graph[u].size(); ++i) {
    int v = graph[u][i];
    depth[v] = depth[u] + 1;
    dfs(v);
    rmq_add(u);
  }
  dfn_out[u] = dfn_t;
}

void rmq_init() {
  for (int i = 2; i <= total; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int j = 1; (1 << j) <= total; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= total; ++i) {
      int d1 = d[i][j - 1], d2 = d[i + (1 << j - 1)][j - 1];
      d[i][j] = min(d1, d2);
      id[i][j] = d1 < d2 ? id[i][j - 1] : id[i + (1 << j - 1)][j - 1];
    }
  }
}

int getlca(int u, int v) {
  u = first_p[u];
  v = first_p[v];
  if (u > v) {
    swap(u, v);
  }
  int k = logv[v - u + 1];
  return d[u][k] < d[v - (1 << k) + 1][k] ? id[u][k] : id[v - (1 << k) + 1][k];
}

bool cmp(const int& x, const int& y) {
  return depth[x] <= depth[y];
}

void modify(int l, int r, int& o, int p, int v) {
  sum[++t] = sum[o] + v;
  lo[t] = lo[o];
  ro[t] = ro[o];
  o = t;
  if (l == r) {
    return;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, lo[t], p, v);
    } else {
      modify(mid + 1, r, ro[t], p, v);
    }
  }
}

int query(int l, int r, int o, int ql, int qr) {
  if (!o) {
    return 0;
  }
  if (ql <= l && r <= qr) {
    return sum[o];
  } else {
    int mid = l + r >> 1, result = 0;
    if (ql <= mid) {
      result += query(l, mid, lo[o], ql, qr);
    } if (qr > mid) {
      result += query(mid + 1, r, ro[o], ql, qr);
    }
    return result;
  }
}

int main() {
  read(tt);
  while (tt--) {
    read(n, q);
    for (int i = 1; i <= n; ++i) {
      graph[i].clear();
      depth_set[i].clear();
      color_set[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
      read(c[i]);
    }
    for (int i = 2; i <= n; ++i) {
      int x;
      read(x);
      graph[x].push_back(i);
    }
    dfn_t = 0;
    total = 0;
    depth[1] = 1;
    dfs(1);
    rmq_init();
    t = 0;
    root[0] = 0;
    for (int i = 1; i <= n; ++i) {
      root[i] = root[i - 1];
      for (int j = 0; j < depth_set[i].size(); ++j) {
        int u = depth_set[i][j];
        color_set[c[u]].insert(dfn[u]);
        set<int>:: iterator a = color_set[c[u]].lower_bound(dfn[u]), b = a;
        int left = -1, right = -1;
        if (a != color_set[c[u]].begin()) {
          left = *--a;
        }
        if (++b != color_set[c[u]].end()) {
          right = *b;
        }
        modify(1, n, root[i], dfn[u], 1);
        if (~left) {
          modify(1, n, root[i], dfn[getlca(u, rdfn[left])], -1);
        }
        if (~right) {
          modify(1, n, root[i], dfn[getlca(u, rdfn[right])], -1);
        }
        if (~left && ~right) {
          modify(1, n, root[i], dfn[getlca(rdfn[left], rdfn[right])], 1);
        }
      }
    }
    int last_answer = 0;
    for (int i = 1; i <= q; ++i) {
      int x, d;
      read(x, d);
      x ^= last_answer;
      d ^= last_answer;
      d = min(d + depth[x], n);
      last_answer = query(1, n, root[d], dfn[x], dfn_out[x]);
      printf("%d\n", last_answer);
    }
  }
  return 0;
}
