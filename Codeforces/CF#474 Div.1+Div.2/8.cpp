#include<bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10, max_node = N * 300;

int n, m, q, C, c[N], a[N], size[N], heavy[N], dfn[N], dfn_t, top[N], father[N], tt, lo[max_node], ro[max_node], addv[max_node];
long long sum[max_node], sum2[max_node];
vector<int> graph[N], nodes[N];

void dfs1(int u) {
  size[u] = 1;
  for (auto v : graph[u]) {
    dfs1(v);
    size[u] += size[v];
    if (size[v] > size[heavy[u]]) {
      heavy[u] = v;
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++dfn_t;
  if (heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : graph[u]) {
      if (v != heavy[u]) {
        dfs2(v, v);
      }
    }
  }
}

void add(int l, int r, int o, int v) {
  addv[o] += v;
  sum2[o] += ((sum[o] << 1) + (r - l + 1) * v) * v;
  sum[o] += (r - l + 1) * v;
}

void push_down(int l, int r, int o) {
  if (addv[o]) {
    int mid = l + r >> 1;
    if (!lo[o]) {
      lo[o] = ++tt;
    }
    if (!ro[o]) {
      ro[o] = ++tt;
    }
    add(l, mid, lo[o], addv[o]);
    add(mid + 1, r, ro[o], addv[o]);
    addv[o] = 0;
  }
}

void push_up(int o) {
  sum[o] = sum[lo[o]] + sum[ro[o]];
  sum2[o] = sum2[lo[o]] + sum2[ro[o]];
}

void modify(int l, int r, int& o, int ql, int qr, int v) {
  if (!o) {
    o = ++tt;
  }
  if (ql <= l && r <= qr) {
    return add(l, r, o, v);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (ql <= mid) {
      modify(l, mid, lo[o], ql, qr, v);
    }
    if (qr > mid) {
      modify(mid + 1, r, ro[o], ql, qr, v);
    }
    push_up(o);
  }
}

struct info_t {
  int root;

  void init(vector<int>& nodes) {
    for (auto v : nodes) {
      for (int x = v; x; x = father[top[x]]) {
        modify(1, n, root, dfn[top[x]], dfn[x], 1);
      }
    }
  }

  void update(int u, int type) {
    for (int x = u; x; x = father[top[x]]) {
      modify(1, n, root, dfn[top[x]], dfn[x], type);
    }
  }

  double get_answer(int c) {
    double result = (double) C * C;
    result -= 2.0 * C * c * sum[root] / n;
    result += 1.0 * c * c * sum2[root] / n;
    return result;
  }
} info[N];

int main() {
  scanf("%d%d%d%d", &n, &m, &q, &C);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    nodes[a[i]].push_back(i);
  }
  for (int i = 2; i <= n; ++i) {
    scanf("%d", &father[i]);
    graph[father[i]].push_back(i);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &c[i]);
  }
  dfs1(1);
  dfs2(1, 1);
  for (int i = 1; i <= m; ++i) {
    info[i].init(nodes[i]);
  }
  while (q--) {
    int type, x, w;
    scanf("%d", &type);
    if (type == 1) {
      scanf("%d%d", &x, &w);
      info[a[x]].update(x, -1);
      a[x] = w;
      info[a[x]].update(x, 1);
    } else {
      scanf("%d", &x);
      printf("%.12lf\n", info[x].get_answer(c[x]));
    }
  }
  return 0;
}
