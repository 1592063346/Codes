#include<bits/stdc++.h>

using namespace std;

const int N = 2e4 + 10;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, m, q, t, low[N], dfn[N], dfn_cnt, depth[N], father[20][N];
long long dist1[N], dist2[N], all[N];
vector<int> pstack;
vector<pair<int, int>> graph[N], v_graph[N];
map<pair<int, int>, int> edge_dist;

void tarjan(int u, int p) {
  dfn[u] = low[u] = ++dfn_cnt;
  pstack.push_back(u);
  for (auto v : graph[u]) {
    if (!dfn[v.first]) {
      tarjan(v.first, u);
      cmin(low[u], low[v.first]);
      if (low[v.first] >= dfn[u]) {
        ++t;
        int nodes = 0, last = u;
        while (1) {
          int x = pstack.back();
          all[t] += edge_dist[{x, last}];
          dist2[x] = dist2[last] + edge_dist[{x, last}];
          v_graph[t].emplace_back(x, 0);
          last = x;
          ++nodes;
          pstack.pop_back();
          if (x == v.first) {
            all[t] += edge_dist[{x, u}];
            break;
          }
        }
        for (auto& v : v_graph[t]) {
          v.second = min(dist2[v.first], all[t] - dist2[v.first]);
        }
        v_graph[u].emplace_back(t, 0);
      }
    } else if (dfn[v.first] < dfn[u]) {
      cmin(low[u], dfn[v.first]);
    }
  }
}

void dfs(int u) {
  for (int i = 1; (1 << i) <= t; ++i) {
    father[i][u] = father[i - 1][father[i - 1][u]];
  }
  for (auto v : v_graph[u]) {
    dist1[v.first] = dist1[u] + v.second;
    depth[v.first] = depth[u] + 1;
    father[0][v.first] = u;
    dfs(v.first);
  }
}

long long query(int u, int v) {
  int old_u = u, old_v = v;
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  for (int i = 17; ~i; --i) {
    if (depth[u] - (1 << i) >= depth[v]) {
      u = father[i][u];
    }
  }
  for (int i = 17; ~i; --i) {
    if (father[i][u] != father[i][v]) {
      u = father[i][u];
      v = father[i][v];
    }
  }
  int lca = father[0][u];
  if (lca <= n) {
    return dist1[old_u] + dist1[old_v] - (dist1[lca] << 1);
  } else {
    return dist1[old_u] - dist1[u] + dist1[old_v] - dist1[v] + min(abs(dist2[u] - dist2[v]), all[lca] - abs(dist2[u] - dist2[v]));
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  t = n;
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edge_dist[{u, v}] = w;
    edge_dist[{v, u}] = w;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }
  tarjan(1, 0);
  dfs(1);
  while (q--) {
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%lld\n", query(u, v));
  }
  return 0;
}
