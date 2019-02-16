#include<bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10, inf = 0x3f3f3f3f;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

struct edge {
  int to, cap, flow;

  edge() {}
  edge(int to, int cap, int flow): to(to), cap(cap), flow(flow) {}
};

int n, m, s, t, color[N], cur[N], d[N], dfn[N], low[N], scc[N], dfn_cnt, scc_cnt;
vector<int> graph[N], flow_graph[N], scc_graph[N], pstack;
vector<edge> edges;

void dfs(int u) {
  for (auto v : graph[u]) {
    if (!~color[v]) {
      color[v] = !color[u];
      dfs(v);
    }
  }
}

void add_edge(int u, int v, int cap) {
  edges.emplace_back(v, cap, 0);
  edges.emplace_back(u, 0, 0);
  flow_graph[u].push_back(edges.size() - 2);
  flow_graph[v].push_back(edges.size() - 1);
}

bool bfs() {
  memset(d, 0, sizeof d);
  memset(cur, 0, sizeof cur);
  d[s] = 1;
  queue<int> que;
  que.push(s);
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (auto p : flow_graph[x]) {
      edge& e = edges[p];
      if (e.flow < e.cap && !d[e.to]) {
        d[e.to] = d[x] + 1;
        que.push(e.to);
      }
    }
  }
  return d[t];
}

int dfs(int u, int a) {
  if (u == t || !a) {
    return a;
  }
  int flow = 0, f;
  for (int& i = cur[u]; i < flow_graph[u].size(); ++i) {
    edge& e = edges[flow_graph[u][i]];
    if (d[e.to] == d[u] + 1 && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
      e.flow += f;
      edges[flow_graph[u][i] ^ 1].flow -= f;
      flow += f;
      a -= f;
      if (!a) {
        break;
      }
    }
  }
  return flow;
}

int dinic() {
  int flow = 0;
  for (; bfs(); flow += dfs(s, inf));
  return flow;
}

void tarjan(int u) {
  pstack.push_back(u);
  dfn[u] = low[u] = ++dfn_cnt;
  for (auto v : scc_graph[u]) {
    if (!dfn[v]) {
      tarjan(v);
      cmin(low[u], low[v]);
    } else if (!scc[v]) {
      cmin(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    ++scc_cnt;
    while (1) {
      int x = pstack.back();
      pstack.pop_back();
      scc[x] = scc_cnt;
      if (x == u) {
        break;
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  memset(color, -1, sizeof color);
  for (int i = 1; i <= n; ++i) {
    if (!~color[i]) {
      color[i] = 0;
      dfs(i);
    }
  }
  s = n + 1;
  t = n + 2;
  for (int i = 1; i <= n; ++i) {
    if (!color[i]) {
      add_edge(s, i, 1);
      for (auto v : graph[i]) {
        add_edge(i, v, 1);
      }
    } else {
      add_edge(i, t, 1);
    }
  }
  dinic();
  for (int i = 1; i <= n + 2; ++i) {
    for (auto p : flow_graph[i]) {
      edge& e = edges[p];
      if (e.flow < e.cap) {
        scc_graph[i].push_back(e.to);
      }
    }
  }
  for (int i = 1; i <= n + 2; ++i) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }
  vector<pair<int, int>> answer;
  for (int i = 1; i <= n; ++i) {
    for (auto p : flow_graph[i]) {
      edge& e = edges[p];
      if (e.flow == e.cap && e.cap == 1 && e.to <= n && scc[i] != scc[e.to]) {
        answer.emplace_back(min(i, e.to), max(i, e.to));
      }
    }
  }
  sort(answer.begin(), answer.end());
  printf("%d\n", answer.size());
  for (auto p : answer) {
    printf("%d %d\n", p.first, p.second);
  }
  return 0;
}
