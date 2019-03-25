#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

template<typename T>
void cmax(T& x, T y) {
  if (x < y) {
    x = y;
  }
}

int n;
long long answer;

namespace tree_1 {
  int m, pu, pv, all, diff, type[N], size[N];
  vector<pair<int, long long>> adj[N], nodes[N], go[N];
  long long px, dist[N];
  bool visit[N];

  void dfs(int u, int p);
  int newnode(int u);
  void build(int l, int r, int u, int anc);
  void rebuild(int u);
  void find_edge(int u, int p);
  void find_node(int u, int p, vector<int>& s, int opt);
  void solve(int u, int s);
}

namespace tree_2 {
  int dfn[N], edfn[N], father[20][N], dfn_cnt, depth[N], sta[N], tt;
  long long dist[N];
  vector<pair<int, long long>> adj[N];
  vector<int> virt[N];
  pair<int, int> dir[2][N];

  void dfs(int u, int p);
  int get_lca(int u, int v);
  pair<int, int> merge(pair<int, int> x, pair<int, int> y);
  long long get_max_dist(pair<int, int> x, pair<int, int> y);
  void solve(int u);
  void solve_virtual_tree(vector<int> s);
}

namespace tree_3 {
  int logv[N << 1], firstp[N], id[20][N << 1], depth[20][N << 1], tt;
  vector<pair<int, long long>> adj[N];
  long long dist[N];

  void dfs(int u, int p, int d);
  void rmq_init();
  int get_lca(int u, int v);
  long long get_dist(int u, int v);
  void init();
  void build(vector<int> s);
}

void tree_1::dfs(int u, int p) {
  for (auto v : adj[u]) {
    if (v.first != p) {
      nodes[u].push_back(v);
      dfs(v.first, u);
    }
  }
}

int tree_1::newnode(int u) {
  ++m;
  go[m].emplace_back(u, 0);
  go[u].emplace_back(m, 0);
  return m;
}

void tree_1::build(int l, int r, int u, int anc) {
  if (l == r) {
    go[u].emplace_back(nodes[anc][l].first, nodes[anc][l].second);
    go[nodes[anc][l].first].emplace_back(u, nodes[anc][l].second);
  } else {
    int mid = l + r >> 1;
    build(l, mid, l == mid ? u : newnode(u), anc);
    build(mid + 1, r, mid + 1 == r ? u : newnode(u), anc);
  }
}

void tree_1::rebuild(int u) {
  if (nodes[u].size()) {
    build(0, nodes[u].size() - 1, u, u);
    for (auto v : nodes[u]) {
      rebuild(v.first);
    }
  }
}

void tree_1::find_edge(int u, int p) {
  size[u] = 1;
  for (auto v : go[u]) {
    if (v.first != p && !visit[v.first]) {
      find_edge(v.first, u);
      size[u] += size[v.first];
      if (abs(all - 2 * size[v.first]) < diff) {
        diff = abs(all - 2 * size[v.first]);
        pu = u;
        pv = v.first;
        px = v.second;
      }
    }
  }
}

void tree_1::find_node(int u, int p, vector<int>& s, int opt) {
  if (u <= n) {
    type[u] = opt;
    s.push_back(u);
  }
  for (auto v : go[u]) {
    if (v.first != p && !visit[v.first]) {
      dist[v.first] = dist[u] + v.second;
      find_node(v.first, u, s, opt);
    }
  }
}

void tree_1::solve(int u, int s) {
  if (s == 1) {
    return;
  }
  all = s;
  diff = s + 1;
  find_edge(u, 0);
  vector<int> node;
  dist[pu] = 0;
  dist[pv] = px;
  find_node(pu, pv, node, 0);
  find_node(pv, pu, node, 1);
  if (node.size()) {
    tree_2::solve_virtual_tree(node);
    for (auto v : node) {
      type[v] = -1;
    }
    int oldu = pu, oldv = pv, sizeu = s - size[pv], sizev = size[pv];
    visit[oldv] = true;
    solve(oldu, sizeu);
    visit[oldv] = false;
    visit[oldu] = true;
    solve(oldv, sizev);
    visit[oldu] = false;
  }
}

void tree_2::dfs(int u, int p) {
  dfn[u] = ++dfn_cnt;
  for (int i = 1; (1 << i) <= n; ++i) {
    father[i][u] = father[i - 1][father[i - 1][u]];
  }
  for (auto v : adj[u]) {
    if (v.first != p) {
      depth[v.first] = depth[u] + 1;
      dist[v.first] = dist[u] + v.second;
      father[0][v.first] = u;
      dfs(v.first, u);
    }
  }
  edfn[u] = dfn_cnt;
}

int tree_2::get_lca(int u, int v) {
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  for (int i = 18; ~i; --i) {
    if (depth[u] - (1 << i) >= depth[v]) {
      u = father[i][u];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 18; ~i; --i) {
    if (father[i][u] != father[i][v]) {
      u = father[i][u];
      v = father[i][v];
    }
  }
  return father[0][u];
}

pair<int, int> tree_2::merge(pair<int, int> x, pair<int, int> y) {
  if (!x.first) {
    return y;
  }
  if (!y.first) {
    return x;
  }
  int a = x.first, b = x.second, c = y.first, d = y.second;
  long long d1 = tree_3::get_dist(a, b);
  long long d2 = tree_3::get_dist(a, c);
  long long d3 = tree_3::get_dist(a, d);
  long long d4 = tree_3::get_dist(b, c);
  long long d5 = tree_3::get_dist(b, d);
  long long d6 = tree_3::get_dist(c, d);
  long long result = max({d1, d2, d3, d4, d5, d6});
  if (d1 == result) {
    return {a, b};
  }
  if (d2 == result) {
    return {a, c};
  }
  if (d3 == result) {
    return {a, d};
  }
  if (d4 == result) {
    return {b, c};
  }
  if (d5 == result) {
    return {b, d};
  }
  if (d6 == result) {
    return {c, d};
  }
}

long long tree_2::get_max_dist(pair<int, int> x, pair<int, int> y) {
  int a = x.first, b = x.second, c = y.first, d = y.second;
  long long d1 = tree_3::get_dist(a, c);
  long long d2 = tree_3::get_dist(a, d);
  long long d3 = tree_3::get_dist(b, c);
  long long d4 = tree_3::get_dist(b, d);
  return max({d1, d2, d3, d4});
}

void tree_2::solve(int u) {
  if (~tree_1::type[u]) {
    dir[tree_1::type[u]][u] = {u, u + n};
  }
  for (auto v : virt[u]) {
    solve(v);
    if (dir[0][u].first && dir[1][v].first) {
      cmax(answer, get_max_dist(dir[0][u], dir[1][v]) - (dist[u] << 1));
    }
    if (dir[1][u].first && dir[0][v].first) {
      cmax(answer, get_max_dist(dir[1][u], dir[0][v]) - (dist[u] << 1));
    }
    dir[0][u] = merge(dir[0][u], dir[0][v]);
    dir[1][u] = merge(dir[1][u], dir[1][v]);
  }
}

void tree_2::solve_virtual_tree(vector<int> s) {
  sort(s.begin(), s.end(), [&] (const int& x, const int& y) {
    return dfn[x] < dfn[y];
  });
  int old = s.size();
  for (int i = 0; i + 1 < old; ++i) {
    s.push_back(get_lca(s[i], s[i + 1]));
  }
  sort(s.begin(), s.end(), [&] (const int& x, const int& y) {
    return dfn[x] < dfn[y];
  });
  s.erase(unique(s.begin(), s.end()), s.end());
  tt = 0;
  for (auto v : s) {
    for (; tt && edfn[sta[tt]] < dfn[v]; --tt);
    if (tt) {
      virt[sta[tt]].push_back(v);
    }
    sta[++tt] = v;
  }
  tree_3::build(s);
  for (auto v : s) {
    dir[0][v] = {0, 0};
    dir[1][v] = {0, 0};
  }
  solve(s[0]);
  for (auto v : s) {
    virt[v].clear();
  }
}

void tree_3::dfs(int u, int p, int d) {
  firstp[u] = ++tt;
  id[0][tt] = u;
  depth[0][tt] = d;
  for (auto v : adj[u]) {
    if (v.first != p) {
      dist[v.first] = dist[u] + v.second;
      dfs(v.first, u, d + 1);
      ++tt;
      id[0][tt] = u;
      depth[0][tt] = d;
    }
  }
}

void tree_3::rmq_init() {
  for (int i = 2; i <= tt; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= tt; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= tt; ++j) {
      int d1 = depth[i - 1][j], d2 = depth[i - 1][j + (1 << i - 1)];
      depth[i][j] = min(d1, d2);
      id[i][j] = d1 < d2 ? id[i - 1][j] : id[i - 1][j + (1 << i - 1)];
    }
  }
}

int tree_3::get_lca(int u, int v) {
  u = firstp[u];
  v = firstp[v];
  if (u > v) {
    swap(u, v);
  }
  int k = logv[v - u + 1];
  return depth[k][u] < depth[k][v - (1 << k) + 1] ? id[k][u] : id[k][v - (1 << k) + 1];
}

long long tree_3::get_dist(int u, int v) {
  int lca = get_lca(u, v);
  return dist[u] + dist[v] - (dist[lca] << 1);
}

void tree_3::init() {
  for (int i = 1; i <= n; ++i) {
    adj[i].emplace_back(n + i, 0);
    adj[n + i].emplace_back(i, 0);
  }
  dfs(1, 0, 0);
  rmq_init();
}

void tree_3::build(vector<int> s) {
  for (auto v : s) {
    dist[v + n] = dist[v] + tree_1::dist[v] + tree_2::dist[v];
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    long long w;
    scanf("%d%d%lld", &u, &v, &w);
    tree_1::adj[u].emplace_back(v, w);
    tree_1::adj[v].emplace_back(u, w);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    long long w;
    scanf("%d%d%lld", &u, &v, &w);
    tree_2::adj[u].emplace_back(v, w);
    tree_2::adj[v].emplace_back(u, w);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    long long w;
    scanf("%d%d%lld", &u, &v, &w);
    tree_3::adj[u].emplace_back(v, w);
    tree_3::adj[v].emplace_back(u, w);
  }
  memset(tree_1::type, -1, sizeof tree_1::type);
  tree_2::dfs(1, 0);
  tree_3::init();
  tree_1::m = n;
  tree_1::dfs(1, 0);
  tree_1::rebuild(1);
  tree_1::solve(1, tree_1::m);
  printf("%lld\n", answer);
  return 0;
}
