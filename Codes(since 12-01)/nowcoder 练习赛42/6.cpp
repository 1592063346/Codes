#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10, md = 19260817, inf = 0x3f3f3f3f;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, m, q, nodes, root, size[N], d[N], f[N], go[N], father[20][N];
bool visit[N];
vector<int> adj[N], color[N];

struct hash_table {
  struct edge_t {
    edge_t* next;
    int x, y, to;

    edge_t() {}
    edge_t(edge_t* next, int x, int y, int to): next(next), x(x), y(y), to(to) {}
  } *first[md];

  int find(int x, int y) {
    int z = (long long) x * y % md;
    for (edge_t* now = first[z]; now; now = now->next) {
      if (now->x == x && now->y == y) {
        return now->to;
      }
    }
    return inf;
  }

  void insert(int x, int y, int w) {
    int z = (long long) x * y % md;
    for (edge_t* now = first[z]; now; now = now->next) {
      if (now->x == x && now->y == y) {
        cmin(now->to, w);
        return;
      }
    }
    first[z] = new edge_t(first[z], x, y, w);
  }
} table;

void dfs(int u, int p) {
  for (int i = 1; (1 << i) <= n; ++i) {
    father[i][u] = father[i - 1][father[i - 1][u]];
  }
  for (auto v : adj[u]) {
    if (v != p) {
      d[v] = d[u] + 1;
      father[0][v] = u;
      dfs(v, u);
    }
  }
}

int get_lca(int u, int v) {
  if (d[u] < d[v]) {
    swap(u, v);
  }
  for (int i = 18; ~i; --i) {
    if (d[u] - (1 << i) >= d[v]) {
      u = father[i][u];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 15; ~i; --i) {
    if (father[i][u] != father[i][v]) {
      u = father[i][u];
      v = father[i][v];
    }
  }
  return father[0][u];
}

int get_dist(int u, int v) {
  return d[u] + d[v] - d[get_lca(u, v)] * 2;
}

void find_root(int u, int p) {
  f[u] = 0;
  size[u] = 1;
  for (auto v : adj[u]) {
    if (v != p && !visit[v]) {
      find_root(v, u);
      size[u] += size[v];
      cmax(f[u], size[v]);
    }
  }
  cmax(f[u], nodes - size[u]);
  if (f[u] < f[root]) {
    root = u;
  }
}

void find_dist(int u, int p, int d, int anc) {
  for (auto x : color[u]) {
    table.insert(anc, x, d);
  }
  for (auto v : adj[u]) {
    if (v != p && !visit[v]) {
      find_dist(v, u, d + 1, anc);
    }
  }
}

void solve(int u) {
  visit[u] = true;
  find_dist(u, 0, 0, u);
  int old = nodes;
  for (auto v : adj[u]) {
    if (!visit[v]) {
      if (size[v] > size[u]) {
        nodes = old - size[u];
      } else {
        nodes = size[v];
      }
      root = 0;
      find_root(v, u);
      go[root] = u;
      solve(root);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= m; ++i) {
    int k, x;
    cin >> k;
    for (int j = 1; j <= k; ++j) {
      cin >> x;
      color[x].push_back(i);
    }
  }
  f[0] = n + 1;
  nodes = n;
  find_root(1, 0);
  solve(root);
  int last_answer = 0;
  while (q--) {
    int x, id;
    cin >> x >> id;
    x = (x + last_answer) % n + 1;
    id = (id + last_answer) % m + 1;
    last_answer = inf;
    for (int u = x; u; u = go[u]) {
      cmin(last_answer, table.find(u, id) + get_dist(u, x));
    }
    printf("%d\n", last_answer);
  }
  return 0;
}
