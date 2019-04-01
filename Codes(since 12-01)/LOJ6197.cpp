#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, inf = 0x3f3f3f3f;

struct edge_t {
  int to, cap, flow;

  edge_t() {}
  edge_t(int to, int cap, int flow): to(to), cap(cap), flow(flow) {}
};

int n, m, s, t, s0, t0, cur[N], d[N];
vector<int> adj[N], flow_adj[N], nodes;
vector<edge_t> edges;
bool visit[N];

void add_edge(int u, int v, int cap) {
  edges.emplace_back(v, cap, 0);
  edges.emplace_back(u, 0, 0);
  flow_adj[u].push_back(edges.size() - 2);
  flow_adj[v].push_back(edges.size() - 1);
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
    for (auto p : flow_adj[x]) {
      edge_t& e = edges[p];
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
  for (int& i = cur[u]; i < flow_adj[u].size(); ++i) {
    edge_t& e = edges[flow_adj[u][i]];
    if (d[e.to] == d[u] + 1 && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
      e.flow += f;
      edges[flow_adj[u][i] ^ 1].flow -= f;
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

void reset(edge_t& e) {
  e.cap = e.flow = 0;
}

int main() {
  scanf("%d%d", &n, &m);
  s0 = (n << 1) + 2;
  t0 = (n << 1) + 3;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    add_edge(u << 1, (v << 1) - 1, inf);
  }
  for (int i = 1; i <= n; ++i) {
    add_edge(0, (i << 1) - 1, inf);
    add_edge(i << 1, n << 1 | 1, inf);
    add_edge((i << 1) - 1, i << 1, inf);
    add_edge((i << 1) - 1, t0, 1);
    add_edge(s0, i << 1, 1);
  }
  add_edge(n << 1 | 1, 0, inf);
  int last = edges.size() - 2;
  s = s0;
  t = t0;
  dinic();
  int answer = edges[last].flow;
  reset(edges[last]);
  reset(edges[last ^ 1]);
  for (auto i : flow_adj[s0]) {
    reset(edges[i]);
    reset(edges[i ^ 1]);
  }
  for (auto i : flow_adj[t0]) {
    reset(edges[i]);
    reset(edges[i ^ 1]);
  }
  s = n << 1 | 1;
  t = 0;
  answer -= dinic();
  printf("%d\n", answer);
  return 0;
}
