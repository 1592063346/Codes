#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, m, tt, dfn_t, node_t, dfn[N], father[N], root[N], depth[N], firstp[N], log_value[N << 1];
vector<int> adj[N], add[N], del[N];
pair<int, int> info[20][N << 1];
long long answer;

struct node_t {
  int l, r, foo, bar, key;
  long long sum;

  void put(int x) {
    foo = x;
    bar = x;
    sum = depth[x];
  }
} nodes[N * 50];

void dfs(int u) {
  dfn[u] = ++dfn_t;
  info[0][firstp[u] = ++tt] = pair<int, int>(depth[u], u);
  for (auto v : adj[u]) {
    if (v != father[u]) {
      father[v] = u;
      depth[v] = depth[u] + 1;
      dfs(v);
      info[0][++tt] = info[0][firstp[u]];
    }
  }
}

int get_lca(int x, int y) {
  x = firstp[x];
  y = firstp[y];
  if (x > y) {
    swap(x, y);
  }
  int k = log_value[y - x + 1];
  return min(info[k][x], info[k][y - (1 << k) + 1]).second;
}

#define ll nodes[x].l
#define rr nodes[x].r

void pull(int x) {
  nodes[x].foo = nodes[ll].foo ? nodes[ll].foo : nodes[rr].foo;
  nodes[x].bar = nodes[rr].bar ? nodes[rr].bar : nodes[ll].bar;
  nodes[x].sum = nodes[ll].sum + nodes[rr].sum;
  if (nodes[ll].bar && nodes[rr].foo) {
    int lca = get_lca(nodes[ll].bar, nodes[rr].foo);
    nodes[x].sum -= depth[lca];
  }
}

void modify(int l, int r, int& x, int p, int y) {
  if (!x) {
    x = ++node_t;
  }
  if (l == r) {
    nodes[x].key += y;
    if (nodes[x].key) {
      nodes[x].put(p);
    } else {
      nodes[x].put(0);
    }
  } else {
    int mid = l + r >> 1;
    if (dfn[p] <= mid) {
      modify(l, mid, nodes[x].l, p, y);
    } else {
      modify(mid + 1, r, nodes[x].r, p, y);
    }
    pull(x);
  }
}

int merge(int l, int r, int x, int y) {
  if (!x || !y) {
    return x | y;
  } else if (l == r) {
    if (nodes[x].key < nodes[y].key) {
      swap(x, y);
    }
    nodes[x].key += nodes[y].key;
    return x;
  } else {
    int mid = l + r >> 1;
    nodes[x].l = merge(l, mid, nodes[x].l, nodes[y].l);
    nodes[x].r = merge(mid + 1, r, nodes[x].r, nodes[y].r);
    pull(x);
    return x;
  }
}

void solve(int u) {
  for (auto v : adj[u]) {
    if (v != father[u]) {
      solve(v);
      root[u] = merge(1, n, root[u], root[v]);
    }
  }
  for (auto x : add[u]) {
    modify(1, n, root[u], x, 1);
  }
  for (auto x : del[u]) {
    modify(1, n, root[u], x, -2);
  }
  answer += nodes[root[u]].sum;
  if (nodes[root[u]].foo && nodes[root[u]].bar) {
    int lca = get_lca(nodes[root[u]].foo, nodes[root[u]].bar);
    answer -= depth[lca];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  depth[1] = 1;
  dfs(1);
  for (int i = 2; i <= tt; ++i) {
    log_value[i] = log_value[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= tt; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= tt; ++j) {
      info[i][j] = min(info[i - 1][j], info[i - 1][j + (1 << i - 1)]);
    }
  }
  for (int i = 0, x, y; i < m; ++i) {
    cin >> x >> y;
    add[x].push_back(x);
    add[x].push_back(y);
    add[y].push_back(x);
    add[y].push_back(y);
    int lca = get_lca(x, y);
    if (father[lca]) {
      del[father[lca]].push_back(x);
      del[father[lca]].push_back(y);
    }
  }
  solve(1);
  cout << (answer >> 1) << '\n';
  return 0;
}
