#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, inf = 0x3f3f3f3f;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

struct edge_t {
  edge_t* next;
  int to;

  edge_t() {}
  edge_t(edge_t* next, int to): next(next), to(to) {}
} *first[N], *first2[N];

struct query_t {
  int id, u, w;

  query_t() {}
  query_t(int id, int u, int w): id(id), u(u), w(w) {}
};

int n, m, root, nodes, value[N], size[N], father[N], h[N], depth[N], dfn[N], edfn[N], top[N], dfn_cnt, maxv[N << 2], addv[N << 2], old_value[N], answer[N];
vector<query_t> queries[N];
bool visit[N];

void modify(int l, int r, int o, int p, int v) {
  addv[o] = 0;
  if (l == r) {
    maxv[o] = v;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, o << 1, p, v);
    } else {
      modify(mid + 1, r, o << 1 | 1, p, v);
    }
    maxv[o] = max(maxv[o << 1], maxv[o << 1 | 1]);
  }
}

void add(int o, int v) {
  addv[o] += v;
  maxv[o] += v;
}

void push_down(int o) {
  if (addv[o]) {
    add(o << 1, addv[o]);
    add(o << 1 | 1, addv[o]);
    addv[o] = 0;
  }
}

void modify(int l, int r, int o, int ql, int qr, int v) {
  if (ql <= l && r <= qr) {
    add(o, v);
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr, v);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    } else {
      modify(l, mid, o << 1, ql, qr, v);
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    }
    maxv[o] = max(maxv[o << 1], maxv[o << 1 | 1]);
  }
}

int query(int l, int r, int o, int ql, int qr) {
  if (ql > qr) {
    return -inf;
  }
  if (ql <= l && r <= qr) {
    return maxv[o];
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (qr <= mid) {
      return query(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      return max(query(l, mid, o << 1, ql, qr), query(mid + 1, r, o << 1 | 1, ql, qr));
    }
  }
}

void find_root(int u, int p) {
  size[u] = 1;
  h[u] = 0;
  for (edge_t* now = first[u]; now; now = now->next) {
    if (now->to != p && !visit[now->to]) {
      find_root(now->to, u);
      size[u] += size[now->to];
      cmax(h[u], size[now->to]);
    }
  }
  cmax(h[u], nodes - size[u]);
  if (h[u] < h[root]) {
    root = u;
  }
}

void solve(int u) {
  visit[u] = true;
  int old = nodes;
  for (edge_t* now = first[u]; now; now = now->next) {
    if (!visit[now->to]) {
      if (size[now->to] > size[u]) {
        nodes = old - size[u];
      } else {
        nodes = size[now->to];
      }
      root = 0;
      find_root(now->to, 0);
      depth[root] = depth[u] + 1;
      father[root] = u;
      first2[u] = new edge_t(first2[u], root);
      solve(root);
    }
  }
}

void dfs(int u, int p, int anc) {
  value[u] = old_value[u];
  dfn[u] = ++dfn_cnt;
  for (edge_t* now = first[u]; now; now = now->next) {
    if (now->to != p && depth[now->to] > depth[anc]) {
      dfs(now->to, u, anc);
    }
  }
  edfn[u] = dfn_cnt;
}

void build(int u, int p, int anc, int sum) {
  sum += value[u];
  modify(1, dfn_cnt, 1, dfn[u], sum);
  for (edge_t* now = first[u]; now; now = now->next) {
    if (now->to != p && depth[now->to] > depth[anc]) {
      build(now->to, u, anc, sum);
    }
  }
}

void modify_top_info(int u, int p, int anc, int t) {
  top[u] = t;
  for (edge_t* now = first[u]; now; now = now->next) {
    if (now->to != p && depth[now->to] > depth[anc]) {
      modify_top_info(now->to, u, anc, t);
    }
  }
}

void dfs(int u) {
  for (edge_t* now = first2[u]; now; now = now->next) {
    dfs(now->to);
  }
  dfn_cnt = 0;
  dfs(u, 0, u);
  build(u, 0, u, 0);
  for (edge_t* now = first[u]; now; now = now->next) {
    if (depth[now->to] > depth[u]) {
      modify_top_info(now->to, u, u, now->to);
    }
  }
  for (int i = 0; i < queries[u].size(); ++i) {
    int opt = queries[u][i].u > 0 ? 2 : 1, x = abs(queries[u][i].u);
    if (opt == 1) {
      int id = queries[u][i].id;
      if (x == u) {
        cmax(answer[id], query(1, dfn_cnt, 1, 1, dfn_cnt));
      } else {
        cmax(answer[id], query(1, dfn_cnt, 1, dfn[x], dfn[x]) - value[u] + max(query(1, dfn_cnt, 1, 1, dfn[top[x]] - 1), query(1, dfn_cnt, 1, edfn[top[x]] + 1, dfn_cnt)));
      }
    } else {
      int w = queries[u][i].w;
      modify(1, dfn_cnt, 1, dfn[x], edfn[x], w - value[x]);
      value[x] = w;
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 2; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    first[i] = new edge_t(first[i], x);
    first[x] = new edge_t(first[x], i);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &value[i]);
    old_value[i] = value[i];
  }
  h[0] = n + 1;
  nodes = n;
  find_root(1, 0);
  int final_root = root;
  solve(root);
  memset(answer, 0xc0, sizeof answer);
  for (int i = 1; i <= m; ++i) {
    int opt, u, w;
    scanf("%d%d", &opt, &u);
    if (opt == 1) {
      u = -u;
    } else {
      scanf("%d", &w);
    }
    for (int x = abs(u); x; x = father[x]) {
      queries[x].push_back(query_t(i, u, w));
    }
  }
  dfs(final_root);
  for (int i = 1; i <= m; ++i) {
    if (answer[i] > -inf) {
      printf("%d\n", answer[i]);
    }
  }
  return 0;
}
