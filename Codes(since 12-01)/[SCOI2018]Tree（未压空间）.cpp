#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, inf = 2e9;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, m, value[N], nodes, root, subtree[N], max_subtree[N], depth[N], pa[N], son[N], seg_t_root[N], seg_t_size[N], dfn_cnt, node_cnt;
vector<int> graph[N], dfn[N], subsize[N];
bool visit[N];

#define lo t_node[o].l
#define ro t_node[o].r

struct node {
  int l, r, maxv, addv;

  node () {}
  node (int l, int r, int maxv, int addv): l(l), r(r), maxv(maxv), addv(addv) {}
} t_node[N * 40];

void add_t(int o, int tag) {
  t_node[o].maxv += tag;
  t_node[o].addv += tag;
}

void push_down(int o) {
  if (t_node[o].addv) {
    if (lo) {
      add_t(lo, t_node[o].addv);
    }
    if (ro) {
      add_t(ro, t_node[o].addv);
    }
    t_node[o].addv = 0;
  }
}

void modify(int l, int r, int& o, int ql, int qr, int v) {
  if (!o) {
    o = ++node_cnt;
  }
  if (ql <= l && r <= qr) {
    add_t(o, v);
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (ql <= mid) {
      modify(l, mid, lo, ql, qr, v);
    } if (qr > mid) {
      modify(mid + 1, r, ro, ql, qr, v);
    }
    t_node[o].maxv = max(t_node[lo].maxv, t_node[ro].maxv);
  }
}

int query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return t_node[o].maxv;
  } else {
    int mid = l + r >> 1, result = -inf;
    push_down(o);
    if (ql <= mid) {
      cmax(result, query(l, mid, lo, ql, qr));
    } if (qr > mid) {
      cmax(result, query(mid + 1, r, ro, ql, qr));
    }
    return result;
  }
}

void get_root(int u, int pa) {
  subtree[u] = 1;
  max_subtree[u] = 0;
  for (auto v : graph[u]) {
    if (!visit[v] && v ^ pa) {
      get_root(v, u);
      subtree[u] += subtree[v];
      cmax(max_subtree[u], subtree[v]);
    }
  }
  cmax(max_subtree[u], nodes - subtree[u]);
  if (max_subtree[u] < max_subtree[root]) {
    root = u;
  }
}

void dfs(int u, int pa, int sum, int anc) {
  dfn[u].push_back(++dfn_cnt);
  subsize[u].push_back(1);
  sum += value[u];
  modify(1, seg_t_size[anc], seg_t_root[anc], dfn_cnt, dfn_cnt, sum);
  for (auto v : graph[u]) {
    if (!visit[v] && v ^ pa) {
      dfs(v, u, sum, anc);
      subsize[u].back() += subsize[v].back();
    }
  }
}

void dfs(int u) {
  visit[u] = true;
  dfn_cnt = 0;
  seg_t_size[u] = nodes;
  dfs(u, 0, 0, u);
  int old = nodes;
  for (auto v : graph[u]) {
    if (!visit[v]) {
      if (subtree[v] > subtree[u]) {
        nodes = old - subtree[u];
      } else {
        nodes = subtree[v];
      }
      root = 0;
      get_root(v, u);
      pa[root] = u;
      son[root] = v;
      depth[root] = depth[u] + 1;
      dfs(root);
    }
  }
}

int query(int u) {
  int l = 1, r = seg_t_size[u];
  int result = query(1, seg_t_size[u], seg_t_root[u], l, r);
  for (int v = u; pa[v]; v = pa[v]) {
    int par = pa[v];
    int other = query(1, seg_t_size[par], seg_t_root[par], dfn[u][depth[par]], dfn[u][depth[par]]) - value[par];
    l = 1;
    r = dfn[son[v]][depth[par]] - 1;
    if (l <= r) {
      cmax(result, query(1, seg_t_size[par], seg_t_root[par], l, r) + other);
    }
    l = dfn[son[v]][depth[par]] + subsize[son[v]][depth[par]];
    r = seg_t_size[par];
    if (l <= r) {
      cmax(result, query(1, seg_t_size[par], seg_t_root[par], l, r) + other);
    }
  }
  return result;
}

void modify(int u, int diff) {
  int l = 1, r = seg_t_size[u];
  modify(1, seg_t_size[u], seg_t_root[u], l, r, diff);
  for (int v = u; pa[v]; v = pa[v]) {
    int par = pa[v];
    l = dfn[u][depth[par]];
    r = dfn[u][depth[par]] + subsize[u][depth[par]] - 1;
    modify(1, seg_t_size[par], seg_t_root[par], l, r, diff);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 2; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    graph[i].push_back(x);
    graph[x].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &value[i]);
  }
  max_subtree[0] = nodes = n;
  get_root(1, 0);
  dfs(root);
  for (int i = 1; i <= m; ++i) {
    int type, u, v;
    scanf("%d", &type);
    if (type == 1) {
      scanf("%d", &u);
      printf("%d\n", query(u));
    } else {
      scanf("%d%d", &u, &v);
      modify(u, v - value[u]);
      value[u] = v;
    }
  }
  return 0;
}
