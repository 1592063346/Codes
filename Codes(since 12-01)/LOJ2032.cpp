#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const long long inf = 123456789123456789ll;

void cmin(long long& x, long long y) {
  if (x > y) {
    x = y;
  }
}

int n, m, father[N], depth[N], size[N], heavy[N], dfn[N], top[N], dfn_cnt;
vector<pair<int, int>> graph[N];
bool exist[N << 2];
long long dist[N], minv[N << 2], k[N << 2], b[N << 2], h[N];

long long get_y(long long k, long long b, long long x) {
  return k * x + b;
}

void build(int l, int r, int o) {
  minv[o] = inf;
  if (l != r) {
    int mid = l + r >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
  }
}

void modify(int l, int r, int o, long long tk, long long tb) {
  if (!exist[o]) {
    k[o] = tk;
    b[o] = tb;
    exist[o] = true;
    cmin(minv[o], min(get_y(tk, tb, h[l]), get_y(tk, tb, h[r])));
    return;
  } else if (get_y(k[o], b[o], h[l]) >= get_y(tk, tb, h[l]) && get_y(k[o], b[o], h[r]) >= get_y(tk, tb, h[r])) {
    k[o] = tk;
    b[o] = tb;
    cmin(minv[o], min(get_y(tk, tb, h[l]), get_y(tk, tb, h[r])));
    return;
  } else if (get_y(k[o], b[o], h[l]) <= get_y(tk, tb, h[l]) && get_y(k[o], b[o], h[r]) <= get_y(tk, tb, h[r])) {
    return;
  } else {
    int mid = l + r >> 1;
    if (get_y(k[o], b[o], h[mid]) <= get_y(tk, tb, h[mid])) {
      if (get_y(k[o], b[o], h[l]) <= get_y(tk, tb, h[l])) {
        modify(mid + 1, r, o << 1 | 1, tk, tb);
      } else {
        modify(l, mid, o << 1, tk, tb);
      }
    } else {
      if (get_y(k[o], b[o], h[r]) >= get_y(tk, tb, h[r])) {
        modify(l, mid, o << 1, k[o], b[o]);
      } else {
        modify(mid + 1, r, o << 1 | 1, k[o], b[o]);
      }
      k[o] = tk;
      b[o] = tb;
    }
    cmin(minv[o], min(get_y(k[o], b[o], h[l]), get_y(k[o], b[o], h[r])));
    cmin(minv[o], min(minv[o << 1], minv[o << 1 | 1]));
  }
}

void modify(int l, int r, int o, int ql, int qr, long long tk, long long tb) {
  if (ql <= l && r <= qr) {
    modify(l, r, o, tk, tb);
  } else {
    int mid = l + r >> 1;
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr, tk, tb);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr, tk, tb);
    } else {
      modify(l, mid, o << 1, ql, qr, tk, tb);
      modify(mid + 1, r, o << 1 | 1, ql, qr, tk, tb);
    }
    cmin(minv[o], min(minv[o << 1], minv[o << 1 | 1]));
  }
}

long long query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return minv[o];
  } else {
    int mid = l + r >> 1;
    long long result = exist[o] ? min(get_y(k[o], b[o], h[max(l, ql)]), get_y(k[o], b[o], h[min(r, qr)])) : inf;
    if (qr <= mid) {
      return min(result, query(l, mid, o << 1, ql, qr));
    } else if (ql > mid) {
      return min(result, query(mid + 1, r, o << 1 | 1, ql, qr));
    } else {
      return min(result, min(query(l, mid, o << 1, ql, qr), query(mid + 1, r, o << 1 | 1, ql, qr)));
    }
  }
}

void dfs1(int u, int p) {
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v.first != p) {
      father[v.first] = u;
      depth[v.first] = depth[u] + 1;
      dist[v.first] = dist[u] + v.second;
      dfs1(v.first, u);
      size[u] += size[v.first];
      if (size[v.first] > size[heavy[u]]) {
        heavy[u] = v.first;
      }
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++dfn_cnt;
  h[dfn_cnt] = dist[u];
  if (heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : graph[u]) {
      if (v.first != father[u] && v.first != heavy[u]) {
        dfs2(v.first, v.first);
      }
    }
  }
}

int get_lca(int u, int v) {
  for (; top[u] != top[v]; u = father[top[u]]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    }
  }
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  return u;
}

long long get_dist(int u, int v) {
  int lca = get_lca(u, v);
  return dist[u] + dist[v] - (dist[lca] << 1);
}

void modify(int u, int v, long long c, long long d) {
  int from = u;
  for (; top[u] != top[v]; u = father[top[u]]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    }
    if (u == top[u]) {
      modify(1, n, 1, dfn[u], dfn[u], 0, get_dist(from, u) * c + d);
    } else {
      long long x1 = dist[top[u]], w1 = get_dist(from, top[u]) * c + d;
      long long x2 = dist[u], w2 = get_dist(from, u) * c + d;
      long long tk = (w1 - w2) / (x1 - x2), tb = w1 - x1 * tk;
      modify(1, n, 1, dfn[top[u]], dfn[u], tk, tb);
    }
  }
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  if (u == v) {
    modify(1, n, 1, dfn[u], dfn[u], 0, get_dist(from, u) * c + d);
  } else {
    long long x1 = dist[u], w1 = get_dist(from, u) * c + d;
    long long x2 = dist[v], w2 = get_dist(from, v) * c + d;
    long long tk = (w1 - w2) / (x1 - x2), tb = w1 - x1 * tk;
    modify(1, n, 1, dfn[u], dfn[v], tk, tb);
  }
}

long long query(int u, int v) {
  long long result = inf;
  for (; top[u] != top[v]; u = father[top[u]]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    }
    cmin(result, query(1, n, 1, dfn[top[u]], dfn[u]));
  }
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  cmin(result, query(1, n, 1, dfn[u], dfn[v]));
  return result;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  build(1, n, 1);
  while (m--) {
    int opt, s, t, c, d;
    scanf("%d%d%d", &opt, &s, &t);
    if (opt == 1) {
      scanf("%d%d", &c, &d);
      modify(s, t, c, d);
    } else {
      printf("%lld\n", query(s, t));
    }
  }
  return 0;
}
