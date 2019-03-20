#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10, inf = 2e9;

bool cmin(int& x, int y) {
  return x > y ? x = y, true : false;
}

struct node_t {
  int u, d;

  node_t() {}
  node_t(int u, int d): u(u), d(d) {}

  bool operator < (const node_t& a) const {
    return d > a.d;
  }
};

int tt, n, m, k, x[N], y[N], value[N], node[N], depth[N], dfn[N], dist[N], father[20][N], dfn_cnt, node_cnt;
vector<int> in[N], out[N], adj[N];
vector<pair<int, int>> go[N];
map<pair<int, int>, int> pre[2], suf[2];
bool visit[N];

void dfs(int u) {
  dfn[u] = ++dfn_cnt;
  for (int i = 1; (1 << i) <= k; ++i) {
    father[i][u] = father[i - 1][father[i - 1][u]];
  }
  for (auto v : adj[u]) {
    depth[v] = depth[u] + 1;
    father[0][v] = u;
    dfs(v);
  }
}

int get_lca(int u, int v) {
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  for (int i = 15; ~i; --i) {
    if (depth[u] - (1 << i) >= depth[v]) {
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

void add_edge(int u, int v, int w) {
  go[u].emplace_back(v, w);
}

void dijkstra() {
  fill(visit, visit + node_cnt + 1, false);
  fill(dist, dist + node_cnt + 1, inf);
  priority_queue<node_t> que;
  que.emplace(0, 0);
  dist[0] = 0;
  while (!que.empty()) {
    int x = que.top().u;
    que.pop();
    if (!visit[x]) {
      visit[x] = true;
      for (auto e : go[x]) {
        if (cmin(dist[e.first], dist[x] + e.second)) {
          que.emplace(e.first, dist[e.first]);
        }
      }
    }
  }
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d%d", &n, &m, &k);
    memset(father, 0, sizeof father);
    for (int a = 0; a < 2; ++a) {
      pre[a].clear();
      suf[a].clear();
    }
    for (int i = 0; i <= (m << 3); ++i) {
      go[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
      in[i].clear();
      out[i].clear();
    }
    for (int i = 1; i <= k; ++i) {
      adj[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
      scanf("%d%d%d%d", &x[i], &y[i], &value[i], &node[i]);
      out[x[i]].push_back(i);
      in[y[i]].push_back(i);
    }
    for (int i = 1; i < k; ++i) {
      int x, y;
      scanf("%d%d%*d", &x, &y);
      adj[x].push_back(y);
    }
    dfn_cnt = 0;
    dfs(1);
    for (int i = 1; i <= n; ++i) {
      sort(in[i].begin(), in[i].end(), [&] (const int& x, const int& y) {
        return dfn[node[x]] < dfn[node[y]];
      });
      sort(out[i].begin(), out[i].end(), [&] (const int& x, const int& y) {
        return dfn[node[x]] < dfn[node[y]];
      });
    }
    node_cnt = 0;
    for (int i = 1; i <= n; ++i) {
      vector<pair<int, int>> nodes;
      for (int j = 0; j < in[i].size(); ++j) {
        nodes.emplace_back(dfn[node[in[i][j]]], in[i][j]);
      }
      for (int j = 0; j < out[i].size(); ++j) {
        nodes.emplace_back(dfn[node[out[i][j]]], out[i][j]);
      }
      sort(nodes.begin(), nodes.end(), [&] (const pair<int, int>& x, const pair<int, int>& y) {
        return x.first == y.first ? x.second < y.second : x.first < y.first;
      });
      nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
      for (int j = 0; j < nodes.size(); ++j) {
        pre[0][{i, nodes[j].second}] = ++node_cnt;
        suf[0][{i, nodes[j].second}] = ++node_cnt;
        pre[1][{i, nodes[j].second}] = ++node_cnt;
        suf[1][{i, nodes[j].second}] = ++node_cnt;
        add_edge(pre[0][{i, nodes[j].second}], pre[1][{i, nodes[j].second}], depth[node[nodes[j].second]]);
        add_edge(suf[0][{i, nodes[j].second}], suf[1][{i, nodes[j].second}], depth[node[nodes[j].second]]);
        if (j) {
          add_edge(pre[0][{i, nodes[j - 1].second}], pre[0][{i, nodes[j].second}], 0);
          add_edge(suf[0][{i, nodes[j].second}], suf[0][{i, nodes[j - 1].second}], 0);
          add_edge(pre[1][{i, nodes[j - 1].second}], pre[1][{i, nodes[j].second}], 0);
          add_edge(suf[1][{i, nodes[j].second}], suf[1][{i, nodes[j - 1].second}], 0);
          add_edge(pre[0][{i, nodes[j - 1].second}], pre[1][{i, nodes[j].second}], depth[get_lca(node[nodes[j - 1].second], node[nodes[j].second])]);
          add_edge(suf[0][{i, nodes[j].second}], suf[1][{i, nodes[j - 1].second}], depth[get_lca(node[nodes[j - 1].second], node[nodes[j].second])]);
        }
      }
    }
    for (int i = 1; i <= m; ++i) {
      add_edge(pre[1][{x[i], i}], pre[0][{y[i], i}], value[i]);
      add_edge(pre[1][{x[i], i}], suf[0][{y[i], i}], value[i]);
      add_edge(suf[1][{x[i], i}], pre[0][{y[i], i}], value[i]);
      add_edge(suf[1][{x[i], i}], suf[0][{y[i], i}], value[i]);
    }
    for (int i = 0; i < out[1].size(); ++i) {
      add_edge(0, pre[1][{1, out[1][i]}], 0);
      add_edge(0, suf[1][{1, out[1][i]}], 0);
    }
    dijkstra();
    for (int i = 2; i <= n; ++i) {
      int result = inf;
      for (int j = 0; j < in[i].size(); ++j) {
        cmin(result, dist[pre[0][{i, in[i][j]}]]);
        cmin(result, dist[suf[0][{i, in[i][j]}]]);
      }
      printf("%d\n", result);
    }
  }
  return 0;
}
