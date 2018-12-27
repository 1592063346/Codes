#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n, k, m, f[N][20], depth[N], father[N], visit[N], on_tree[N];
vector<int> graph[N];
map<int, bool> check[N];

int find(int x) {
  return father[x] == x ? x : father[x] = find(father[x]);
}

void add_edge(int u, int v) {
  graph[u].push_back(v);
  graph[v].push_back(u);
}

void dfs(int u, int pa) {
  for (int i = 1; (1 << i) <= n; ++i) {
    f[u][i] = f[f[u][i - 1]][i - 1];
  }
  for (auto v : graph[u]) {
    if (v != pa) {
      f[v][0] = u;
      depth[v] = depth[u] + 1;
      dfs(v, u);
    }
  }
  if (check[u].count(pa)) {
    on_tree[u] = 1;
  }
}

int get_lca(int u, int v) {
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  for (int i = 19; ~i; --i) {
    if (depth[u] - (1 << i) >= depth[v]) {
      u = f[u][i];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 19; ~i; --i) {
    if (f[u][i] != f[v][i]) {
      u = f[u][i];
      v = f[v][i];
    }
  }
  return f[u][0];
}

int main() {
  scanf("%d%d%d", &n, &k, &m);
  for (int i = 1; i <= n; ++i) {
    father[i] = i;
  }
  for (int i = 1; i <= k; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    add_edge(u, v);
    check[u][v] = check[v][u] = true;
    father[find(u)] = find(v);
  }
  vector<pair<int, pair<int, int>>> edge;
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edge.emplace_back(w, make_pair(u, v));
  }
  sort(edge.begin(), edge.end());
  for (auto e : edge) {
    int u = e.second.first;
    int v = e.second.second;
    if (find(u) != find(v)) {
      add_edge(u, v);
      father[find(u)] = find(v);
    }
  }
  dfs(1, 0);
  for (int i = 1; i <= n; ++i) {
    father[i] = i;
  }
  long long answer = 0;
  for (auto e : edge) {
    int u = e.second.first;
    int v = e.second.second;
    int lca = get_lca(u, v);
    if (lca) {
      for (u = find(u); u && depth[u] > depth[lca]; u = find(u)) {
        visit[u] = 1;
        if (on_tree[u]) {
          answer += e.first;
        }
        father[find(u)] = find(f[u][0]);
      }
      for (v = find(v); v && depth[v] > depth[lca]; v = find(v)) {
        visit[v] = 1;
        if (on_tree[v]) {
          answer += e.first;
        }
        father[find(v)] = find(f[v][0]);
      }
    }
  }
  bool infty = false;
  for (int i = 2; i <= n; ++i) {
    if (!visit[i]) {
      infty = true;
    }
  }
  printf("%I64d\n", infty ? -1 : answer);
  return 0;
}
