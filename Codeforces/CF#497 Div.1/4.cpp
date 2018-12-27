#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, maxnode = N * 60;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, m, pa[N], dep[N], size[N], heavy[N], dfn[maxnode], dfn_cnt, top[N], node_cnt, low[maxnode], sccno[maxnode], scc;
vector<int> graph[N], graph_t[maxnode], nodes[N << 2], stack_t;

void dfs1(int u, int pa) {
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v != pa) {
      ::pa[v] = u;
      dep[v] = dep[u] + 1;
      dfs1(v, u);
      size[u] += size[v];
      if (size[v] > size[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++dfn_cnt;
  if (heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : graph[u]) {
      if (v != pa[u] && v != heavy[u]) {
        dfs2(v, v);
      }
    }
  }
}

void add_edge(int u, int v) {
  graph_t[u].push_back(v);
  graph_t[v ^ 1].push_back(u ^ 1);
}

#define lo (o<<1)
#define ro (o<<1|1)

void modify(int l, int r, int o, int ql, int qr, int id) {
  if (ql <= l && r <= qr) {
    nodes[o].push_back(id);
  } else {
    int mid = l + r >> 1;
    if (ql <= mid) {
      modify(l, mid, lo, ql, qr, id);
    } if (qr > mid) {
      modify(mid + 1, r, ro, ql, qr, id);
    }
  }
}

void build(int l, int r, int o, int lastid) {
  int ql = ++node_cnt;
  int qr = (node_cnt += nodes[o].size());
  if (qr > ql) {
    add_edge(qr << 1 | 1, qr - 1 << 1 | 1);
  } else if (lastid) {
    add_edge(ql << 1 | 1, lastid << 1 | 1);
  }
  for (int i = 0; i < nodes[o].size(); ++i) {
    int id = nodes[o][i];
    if (i > 0) {
      add_edge(ql + i << 1 | 1, ql + i - 1 << 1 | 1);
    } else if (lastid) {
      add_edge(ql << 1 | 1, lastid << 1 | 1);
    }
    add_edge(id, ql + i << 1);
    if (i > 0) {
      add_edge(ql + i - 1 << 1, id ^ 1);
    } else if (lastid) {
      add_edge(lastid << 1, id ^ 1);
    }
  }
  if (l < r) {
    int mid = l + r >> 1;
    build(l, mid, lo, qr);
    build(mid + 1, r, ro, qr);
  }
}

void add_tag(int u, int v, int id) {
  for (; top[u] != top[v]; u = pa[top[u]]) {
    if (dep[top[u]] < dep[top[v]]) {
      swap(u, v);
    }
    modify(2, n, 1, dfn[top[u]], dfn[u], id);
  }
  if (dep[u] > dep[v]) {
    swap(u, v);
  }
  if (dfn[u] < dfn[v]) {
    modify(2, n, 1, dfn[u] + 1, dfn[v], id);
  }
}

void tarjan(int u) {
  stack_t.push_back(u);
  dfn[u] = low[u] = ++dfn_cnt;
  for (auto v : graph_t[u]) {
    if (!dfn[v]) {
      tarjan(v);
      cmin(low[u], low[v]);
    } else if (!sccno[v]) {
      cmin(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++scc;
    while (1) {
      int x = stack_t.back();
      stack_t.pop_back();
      sccno[x] = scc;
      if (x == u) {
        break;
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  scanf("%d", &m);
  node_cnt = m;
  for (int i = 1; i <= m; ++i) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    add_tag(a, b, i << 1);
    add_tag(c, d, i << 1 | 1);
  }
  build(2, n, 1, 0);
  memset(dfn, 0, sizeof dfn);
  dfn_cnt = 0;
  for (int i = 2; i <= (node_cnt << 1 | 1); ++i) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }
  for (int i = 1; i <= m; ++i) {
    if (sccno[i << 1] == sccno[i << 1 | 1]) {
      return puts("NO"), 0;
    }
  }
  puts("YES");
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", sccno[i << 1] < sccno[i << 1 | 1] ? 1 : 2);
  }
  return 0;
}
