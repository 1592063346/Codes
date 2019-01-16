#include<bits/stdc++.h>

using namespace std;

const int N = 6e2 + 10, inf = 0x3f3f3f3f;

struct edge {
  int to, cap, flow;

  edge() {}
  edge(int to, int cap, int flow): to(to), cap(cap), flow(flow) {}
};

int n, tt, s, t, nodes, visit[N], go[N], d[N], cur[N];
vector<int> net[N], graph[N];
vector<edge> edges;

void add_edge(int u, int v, int cap) {
  edges.emplace_back(v, cap, 0);
  edges.emplace_back(u, 0, 0);
  graph[u].push_back(edges.size() - 2);
  graph[v].push_back(edges.size() - 1);
}

bool bfs() {
  memset(cur, 0, sizeof cur);
  memset(d, 0, sizeof d);
  d[s] = 1;
  queue<int> que;
  que.push(s);
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (auto v : graph[x]) {
      edge& e = edges[v];
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
  } else {
    int flow = 0, f;
    for (int& i = cur[u]; i < graph[u].size(); ++i) {
      edge& e = edges[graph[u][i]];
      if (d[u] + 1 == d[e.to] && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
        e.flow += f;
        edges[graph[u][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (!a) {
          break;
        }
      }
    }
    return flow;
  }
}

int dinic() {
  int flow = 0;
  while (bfs()) {
    flow += dfs(s, inf);
  }
  return flow;
}

bool find(int u) {
  visit[u] = tt;
  for (auto v : net[u]) {
    if (visit[v] != tt) {
      visit[v] = tt;
      if (!go[v] || find(go[v])) {
        go[v] = u;
        return true;
      }
    }
  }
  return false;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int t, x;
    scanf("%d", &t);
    while (t--) {
      scanf("%d", &x);
      net[i].push_back(x + n);
    }
  }
  for (int i = 1; i <= n; ++i) {
    ++tt;
    find(i);
  }
  nodes = n;
  for (int i = 1; i <= n; ++i) {
    for (auto v : net[i]) {
      add_edge(i, go[v], inf);
    }
  }
  s = ++nodes;
  t = ++nodes;
  int posit = 0;
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    x = -x;
    if (x > 0) {
      add_edge(s, i, x);
      posit += x;
    } else {
      add_edge(i, t, -x);
    }
  }
  printf("%d\n", -(posit - dinic()));
  return 0;
}
