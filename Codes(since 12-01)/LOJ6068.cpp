#include<bits/stdc++.h>

using namespace std;

const int N = 55, max_node = N * N, inf = 0x3f3f3f3f;

struct edge {
  int to, cap, flow, cost;

  edge() {}
  edge(int to, int cap, int flow, int cost): to(to), cap(cap), flow(flow), cost(cost) {}
};

int n, tt, q, s, t, id1[N][N], id2[N][N], cur[max_node], d[max_node], answer[max_node];
bool inq[max_node], visit[max_node];
char grid[N][N];
vector<edge> edges;
vector<int> graph[max_node];

void add_edge(int u, int v, int cap, int cost) {
  edges.emplace_back(v, cap, 0, cost);
  edges.emplace_back(u, 0, 0, -cost);
  graph[u].push_back(edges.size() - 2);
  graph[v].push_back(edges.size() - 1);
}

bool bfs() {
  memset(cur, 0, sizeof cur);
  memset(inq, false, sizeof inq);
  memset(visit, false, sizeof visit);
  memset(d, 0x3f, sizeof d);
  queue<int> que;
  que.push(s);
  d[s] = 0;
  inq[s] = true;
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    inq[x] = false;
    for (auto v : graph[x]) {
      edge& e = edges[v];
      if (e.flow < e.cap && d[e.to] > d[x] + e.cost) {
        d[e.to] = d[x] + e.cost;
        if (!inq[e.to]) {
          que.push(e.to);
          inq[e.to] = true;
        }
      }
    }
  }
  return d[t] != inf;
}

pair<int, int> dfs(int u, int a) {
  if (u == t || !a) {
    return {a, 0};
  } else {
    visit[u] = true;
    pair<int, int> result(0, 0);
    for (int& i = cur[u]; i < graph[u].size(); ++i) {
      edge& e = edges[graph[u][i]];
      if (d[e.to] == d[u] + e.cost && !visit[e.to]) {
        pair<int, int> go = dfs(e.to, min(a, e.cap - e.flow));
        if (go.first > 0) {
          e.flow += go.first;
          edges[graph[u][i] ^ 1].flow -= go.first;
          result.first += go.first;
          result.second += go.second + go.first * e.cost;
          a -= go.first;
          if (!a) {
            break;
          }
        }
      }
    }
    return result;
  }
}

pair<int, int> solve() {
  pair<int, int> result(0, 0);
  while (bfs()) {
    pair<int, int> x = dfs(s, inf);
    for (int i = 1; i <= x.first; ++i) {
      answer[result.first + i] = answer[result.first] + i * d[t];
    }
    result.first += x.first;
    result.second += x.second;
  }
  return result;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", grid[i] + 1);
  }
  s = ++tt;
  t = ++tt;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (grid[i][j] == '.') {
        if (i == 1 || grid[i - 1][j] == '#') {
          ++tt;
          for (int l = i; l <= n && grid[l][j] == '.'; ++l) {
            add_edge(s, id1[l][j] = tt, 1, l - i);
          }
        }
        if (j == 1 || grid[i][j - 1] == '#') {
          ++tt;
          for (int l = j; l <= n && grid[i][l] == '.'; ++l) {
            add_edge(id2[i][l] = tt, t, 1, l - j);
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (grid[i][j] == '.') {
        add_edge(id1[i][j], id2[i][j], 1, 0);
      }
    }
  }
  solve();
  scanf("%d", &q);
  while (q--) {
    int x;
    scanf("%d", &x);
    printf("%d\n", answer[x]);
  }
  return 0;
}
