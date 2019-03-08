#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

struct edge_t {
  int to, cap, flow;

  edge_t() {}
  edge_t(int to, int cap, int flow): to(to), cap(cap), flow(flow) {}
};

int m, c, n1, n2, s, t, x[N], y[N], cur[N], d[N];
vector<edge_t> edges;
vector<int> graph[N];
bool visit[N], answer[N];

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
      edge_t& e = edges[v];
      if (e.flow < e.cap && !d[e.to]) {
        d[e.to] = d[x] + 1;
        que.push(e.to);
      }
    }
  }
  return d[t] != 0;
}

int dfs(int u, int a) {
  if (u == t || !a) {
    return a;
  } else {
    int flow = 0, f;
    for (int& i = cur[u]; i < graph[u].size(); ++i) {
      edge_t& e = edges[graph[u][i]];
      if (d[e.to] == d[u] + 1 && (f = dfs(e.to, min(e.cap - e.flow, a))) > 0) {
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

void dfs(int u) {
  visit[u] = true;
  if (u >= 1 && u <= n1) {
    answer[u] = false;
  }
  for (auto v : graph[u]) {
    edge_t& e = edges[v];
    if (e.flow < e.cap && !visit[e.to]) {
      dfs(e.to);
    }
  }
}

int main() {
  scanf("%d%d%d", &m, &c, &n1);
  for (int i = 1; i <= n1; ++i) {
    scanf("%d%d", &x[i], &y[i]);
  }
  scanf("%d", &n2);
  s = 0;
  t = n1 + n2 + 1;
  for (int i = 1; i <= n1; ++i) {
    add_edge(s, i, 1);
    add_edge(i, n1 + n2 + 1 + x[i], 1);
    add_edge(i, n1 + n2 + 1 + m + y[i], 1);
  }
  for (int i = 1; i <= n2; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    add_edge(n1 + i, t, 1);
    add_edge(n1 + n2 + 1 + x, n1 + i, 1);
    add_edge(n1 + n2 + 1 + m + y, n1 + i, 1);
  }
  for (; bfs(); dfs(s, n1));
  memset(answer, true, sizeof answer);
  dfs(s);
  for (int i = 1; i <= n1; ++i) {
    printf("%d\n", (int) answer[i]);
  }
  return 0;
}
