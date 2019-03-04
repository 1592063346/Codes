#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, m, ff[N], u[N], v[N], size[N], last[N], father[N], f[N][2], g[N][2], opt[N], v_opt[N];
vector<int> graph[N], v_graph[N];
vector<pair<int, int>> others, subtree_dp[N];
vector<pair<pair<int, int>, pair<int, int>>> subpart_dp[N];
bool ban[N], vir[N];

int find(int x) {
  return ff[x] == x ? x : ff[x] = find(ff[x]);
}

void dfs(int u, int p) {
  for (auto v : graph[u]) {
    if (v != p) {
      father[v] = u;
      dfs(v, u);
      size[u] += size[v];
      if (last[v]) {
        last[u] = last[v];
      }
    }
  }
  if (size[u] >= 2 || (size[u] == 1 && vir[u])) {
    last[u] = u;
    for (auto v : graph[u]) {
      if (v != p && size[v]) {
        v_graph[u].push_back(last[v]);
      }
    }
  }
  if (vir[u]) {
    last[u] = u;
    ++size[u];
  }
  size[u] = min(size[u], 1);
}

void dp(int u, int p) {
  f[u][0] = opt[u] != 2;
  f[u][1] = opt[u] != 1;
  for (auto v : graph[u]) {
    if (v != p && !ban[v]) {
      dp(v, u);
      f[u][0] = mul(f[u][0], f[v][0] + f[v][1]);
      f[u][1] = mul(f[u][1], f[v][0]);
    }
  }
}

void dfs(int u) {
  for (auto v : graph[u]) {
    if (!size[v]) {
      dp(v, u);
      subtree_dp[u].emplace_back(f[v][0], f[v][1]);
    }
  }
  for (auto go : v_graph[u]) {
    dfs(go);
    if (father[go] != u) {
      int v = go;
      for (; father[v] != u; v = father[v]);
      ban[go] = true;
      opt[father[go]] = 1;
      dp(v, u);
      pair<int, int> x = {f[v][0], f[v][1]};
      opt[father[go]] = 2;
      dp(v, u);
      pair<int, int> y = {f[v][0], f[v][1]};
      subpart_dp[u].emplace_back(x, y);
      opt[father[go]] = 0;
      ban[go] = false;
    }
  }
}

void dp(int u) {
  g[u][0] = v_opt[u] != 2;
  g[u][1] = v_opt[u] != 1;
  int pis = 0;
  for (auto v : graph[u]) {
    if (!size[v]) {
      g[u][0] = mul(g[u][0], subtree_dp[u][pis].first + subtree_dp[u][pis].second);
      g[u][1] = mul(g[u][1], subtree_dp[u][pis].first);
      ++pis;
    }
  }
  pis = 0;
  for (auto v : v_graph[u]) {
    dp(v);
    if (father[v] == u) {
      g[u][0] = mul(g[u][0], g[v][0] + g[v][1]);
      g[u][1] = mul(g[u][1], g[v][0]);
    } else {
      int a = subpart_dp[u][pis].first.first;
      int b = subpart_dp[u][pis].first.second;
      int c = subpart_dp[u][pis].second.first;
      int d = subpart_dp[u][pis].second.second;
      g[u][0] = mul(g[u][0], mul(((long long) a + b + c + d) % mod, g[v][0]) + mul(a + b, g[v][1]));
      g[u][1] = mul(g[u][1], mul(a + c, g[v][0]) + mul(a, g[v][1]));
      ++pis;
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    ff[i] = i;
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (find(u) != find(v)) {
      ff[find(u)] = find(v);
      graph[u].push_back(v);
      graph[v].push_back(u);
    } else {
      others.emplace_back(u, v);
      vir[u] = true;
      vir[v] = true;
    }
  }
  vir[1] = true;
  dfs(1, 0);
  dfs(1);
  int answer = 0;
  for (int i = 0; i < 1 << others.size(); ++i) {
    for (auto e : others) {
      v_opt[e.first] = 0;
      v_opt[e.second] = 0;
    }
    for (int j = 0; j < others.size(); ++j) {
      if (i >> j & 1) {
        if (v_opt[others[j].first] == 2) {
          goto _end;
        } else {
          v_opt[others[j].first] = 1;
        }
      } else {
        if (v_opt[others[j].first] == 1 || v_opt[others[j].second] == 2) {
          goto _end;
        } else {
          v_opt[others[j].first] = 2;
          v_opt[others[j].second] = 1;
        }
      }
    }
    for (auto e : others) {
      if (v_opt[e.first] == 2 && v_opt[e.second] == 2) {
        goto _end;
      }
    }
    dp(1);
    add(answer, g[1][0]);
    add(answer, g[1][1]);
    _end: continue;
  }
  printf("%d\n", answer);
  return 0;
}
