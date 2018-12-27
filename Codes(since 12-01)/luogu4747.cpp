#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, q, per[N], p[N], id[N << 2], pid[N], p_l[N << 1], p_r[N << 1], node_cnt, dfn[N << 1], low[N << 1], dfn_cnt, sccno[N << 1], scc_cnt, scc_l[N << 1], scc_r[N << 1], visit[N << 1];
vector<int> graph[N << 1], scc_g[N << 1], p_stack;
pair<int, int> pos[N << 2];

#define lo (o<<1)
#define ro (o<<1|1)

void build(int l, int r, int o) {
  if (l == r) {
    pos[o] = pair<int, int> (p[l], p[l]);
  } else {
    int mid = l + r >> 1;
    build(l, mid, lo);
    build(mid + 1, r, ro);
    pos[o].first = min(pos[lo].first, pos[ro].first);
    pos[o].second = max(pos[lo].second, pos[ro].second);
  }
}

pair<int, int> query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return pos[o];
  } else {
    int mid = l + r >> 1;
    pair<int, int> result = pair<int, int> (n + 1, 0);
    if (ql <= mid) {
      pair<int, int> x = query(l, mid, lo, ql, qr);
      cmin(result.first, x.first);
      cmax(result.second, x.second);
    } if (qr > mid) {
      pair<int, int> x = query(mid + 1, r, ro, ql, qr);
      cmin(result.first, x.first);
      cmax(result.second, x.second);
    }
    return result;
  }
}

void add_edge(int u, int v) {
  graph[u].push_back(v);
}

void add_scc_edge(int u, int v) {
  scc_g[u].push_back(v);
}

void build_edge(int l, int r, int o) {
  id[o] = ++node_cnt;
  if (l == r) {
    p_l[node_cnt] = l;
    p_r[node_cnt] = r;
    pid[l] = node_cnt;
  } else {
    p_l[node_cnt] = n + 1;
    p_r[node_cnt] = 0;
    int mid = l + r >> 1;
    build_edge(l, mid, lo);
    build_edge(mid + 1, r, ro);
    add_edge(id[o], id[lo]);
    add_edge(id[o], id[ro]);
  }
}

void find_interval(int l, int r, int o, int ql, int qr, int node) {
  if (ql <= l && r <= qr) {
    add_edge(node, id[o]);
  } else {
    int mid = l + r >> 1;
    if (ql <= mid) {
      find_interval(l, mid, lo, ql, qr, node);
    } if (qr > mid) {
      find_interval(mid + 1, r, ro, ql, qr, node);
    }
  }
}

void tarjan(int u) {
  dfn[u] = low[u] = ++dfn_cnt;
  p_stack.push_back(u);
  for (auto v : graph[u]) {
    if (!dfn[v]) {
      tarjan(v);
      cmin(low[u], low[v]);
    } else if (!sccno[v]) {
      cmin(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++scc_cnt;
    scc_l[scc_cnt] = n + 1;
    scc_r[scc_cnt] = 0;
    while (1) {
      int x = p_stack.back();
      p_stack.pop_back();
      sccno[x] = scc_cnt;
      cmin(scc_l[scc_cnt], p_l[x]);
      cmax(scc_r[scc_cnt], p_r[x]);
      if (x == u) {
        break;
      }
    }
  }
}

void check(int u) {
  visit[u] = 1;
  for (auto v : scc_g[u]) {
    if (!visit[v]) {
      check(v);
    }
    cmin(scc_l[u], scc_l[v]);
    cmax(scc_r[u], scc_r[v]);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &per[i]);
    p[per[i]] = i;
  }
  build(1, n, 1);
  build_edge(1, n - 1, 1);
  for (int i = 1; i < n; ++i) {
    int pl = min(per[i], per[i + 1]);
    int pr = max(per[i], per[i + 1]);
    pair<int, int> position = query(1, n, 1, pl, pr);
    find_interval(1, n - 1, 1, position.first, position.second - 1, pid[i]);
  }
  for (int i = 1; i <= node_cnt; ++i) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }
  for (int u = 1; u <= node_cnt; ++u) {
    for (auto v : graph[u]) {
      if (sccno[u] != sccno[v]) {
        add_scc_edge(sccno[u], sccno[v]);
      }
    }
  }
  for (int i = 1; i <= scc_cnt; ++i) {
    check(i);
  }

  vector<pair<int, int>> t_node(n << 2, pair<int, int> (n + 1, 0));
  function<void(int, int, int)> build2 = [&] (int l, int r, int o) {
    if (l == r) {
      int scc = sccno[pid[l]];
      t_node[o].first = scc_l[scc];
      t_node[o].second = scc_r[scc];
    } else {
      int mid = l + r >> 1;
      build2(l, mid, lo);
      build2(mid + 1, r, ro);
      t_node[o].first = min(t_node[lo].first, t_node[ro].first);
      t_node[o].second = max(t_node[lo].second, t_node[ro].second);
    }
  };

  function<pair<int, int> (int, int, int, int, int)> query2 = [&] (int l, int r, int o, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return t_node[o];
    } else {
      int mid = l + r >> 1;
      pair<int, int> result = pair<int, int> (n + 1, 0);
      if (ql <= mid) {
        pair<int, int> x = query2(l, mid, lo, ql, qr);
        cmin(result.first, x.first);
        cmax(result.second, x.second);
      } if (qr > mid) {
        pair<int, int> x = query2(mid + 1, r, ro, ql, qr);
        cmin(result.first, x.first);
        cmax(result.second, x.second);
      }
      return result;
    }
  };

  build2(1, n - 1, 1);
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (l == r) {
      printf("%d %d\n", l, r);
    } else {
      pair<int, int> result = query2(1, n - 1, 1, l, r - 1);
      printf("%d %d\n", result.first, result.second + 1);
    }
  }
  return 0;
}
