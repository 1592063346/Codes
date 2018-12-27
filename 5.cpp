#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, inf = 0x3f3f3f3f;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

struct info_t {
  int x, y1, y2, type;

  info_t () {}
  info_t (int x, int y1, int y2, int type): x(x), y1(y1), y2(y2), type(type) {}

  bool operator < (const info_t& a) const {
    return x == a.x ? !type : x < a.x;
  }
};

int n, m, q, tt, dfn[N], fenw[N], adfn[N], depth[N], father[N], size[N], heavy[N], top[N], be[N], answer[N];
vector<int> graph[N];
vector<pair<int, int>> path;
vector<info_t> events;

void dfs1(int u) {
  size[u] = 1;
  for (auto v : graph[u]) {
    depth[v] = depth[u] + 1;
    father[v] = u;
    dfs1(v);
    size[u] += size[v];
    if (size[v] > size[heavy[u]]) {
      heavy[u] = v;
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++tt;
  adfn[tt] = u;
  if (heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : graph[u]) {
      if (v != heavy[u]) {
        dfs2(v, v);
      }
    }
  }
}

int getlca(int u, int v) {
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

int jump(int u, int d) {
  for (; depth[top[u]] > d; u = father[top[u]]);
  return adfn[dfn[u] - depth[u] + d];
}

#define lo (o<<1)
#define ro (o<<1|1)

int minv[N << 2];

void modify(int l, int r, int o, int ql, int qr, int v) {
  if (ql <= l && r <= qr) {
    cmin(minv[o], v);
  } else {
    int mid = l + r >> 1;
    if (ql <= mid) {
      modify(l, mid, lo, ql, qr, v);
    } if (qr > mid) {
      modify(mid + 1, r, ro, ql, qr, v);
    }
  }
}

int query(int l, int r, int o, int p, int value = inf) {
  cmin(value, minv[o]);
  if (l == r) {
    return value;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      return query(l, mid, lo, p, value);
    } else {
      return query(mid + 1, r, ro, p, value);
    }
  }
}

void add_up(int u, int v, int d) {
  for (; top[u] != top[v]; u = father[top[u]]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    }
    modify(1, n, 1, dfn[top[u]], dfn[u], d);
  }
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  modify(1, n, 1, dfn[u], dfn[v], d);
}

void modify(int p) {
  for (; p <= n; p += p & -p) {
    ++fenw[p];
  }
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    result += fenw[p];
  }
  return result;
}

int query(int l, int r) {
  return query(r) - query(l - 1);
}

int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    graph[x].push_back(i);
  }
  dfs1(1);
  dfs2(1, 1);
  memset(minv, 0x3f, sizeof minv);
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    path.emplace_back(x, y);
    int lca = getlca(x, y);
    add_up(x, y, depth[lca]);
    events.emplace_back(dfn[x], dfn[y], 0, 0);
    events.emplace_back(dfn[y], dfn[x], 0, 0);
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    int lca = getlca(x, y), d;
    while ((d = query(1, n, 1, dfn[x])) > depth[lca]) {
      if (d >= depth[x]) {
        break;
      }
      ++answer[i];
      x = jump(x, d);
    }
    while ((d = query(1, n, 1, dfn[y])) > depth[lca]) {
      if (d >= depth[y]) {
        break;
      }
      ++answer[i];
      y = jump(y, d);
    }
    if (query(1, n, 1, dfn[x]) > depth[lca] || query(1, n, 1, dfn[y]) > depth[lca]) {
      answer[i] = -1;
    } else {
      answer[i] += 2;
    }
    if (~answer[i]) {
      if (depth[x] < depth[y]) {
        swap(x, y);
      }
      if (y == lca) {
        int down = jump(x, depth[lca] + 1);
        events.emplace_back(0, dfn[y], dfn[y] + size[y] - 1, -i);
        events.emplace_back(dfn[down] - 1, dfn[y], dfn[y] + size[y] - 1, i);
        events.emplace_back(dfn[down] + size[down] - 1, dfn[y], dfn[y] + size[y] - 1, -i);
        events.emplace_back(n, dfn[y], dfn[y] + size[y] - 1, i);
      } else {
        events.emplace_back(dfn[x] - 1, dfn[y], dfn[y] + size[y] - 1, -i);
        events.emplace_back(dfn[x] + size[x] - 1, dfn[y], dfn[y] + size[y] - 1, i);
      }
    }
  }
  sort(events.begin(), events.end());
  for (auto v : events) {
    if (!v.type) {
      modify(v.y1);
    } else {
      int coef = v.type < 0 ? -1 : 1;
      be[abs(v.type)] += coef * query(v.y1, v.y2);
    }
  }
  for (int i = 1; i <= q; ++i) {
    if (~answer[i]) {
      answer[i] -= be[i] > 0;
    }
  }
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
