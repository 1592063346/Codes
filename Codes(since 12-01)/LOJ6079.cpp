#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;
const long long inf = 1e15;

struct edge {
  int to, cap, flow;
  long long cost;

  edge() {}
  edge(int to, int cap, int flow, long long cost): to(to), cap(cap), flow(flow), cost(cost) {}
};

int n, k, ms, me, s, t, a[N], b[N], cur[N];
long long d[N];
bool inq[N], visit[N];
vector<edge> edges;
vector<int> graph[N];

void add_edge(int u, int v, int cap, long long cost) {
  edges.emplace_back(v, cap, 0, cost);
  edges.emplace_back(u, 0, 0, -cost);
  graph[u].push_back(edges.size() - 2);
  graph[v].push_back(edges.size() - 1);
}

bool bfs() {
  memset(cur, 0, sizeof cur);
  memset(inq, false, sizeof inq);
  memset(visit, false, sizeof visit);
  fill(d, d + N, inf);
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

pair<int, long long> dfs(int u, int a) {
  if (u == t || !a) {
    return {a, 0};
  } else {
    visit[u] = true;
    pair<int, long long> result(0, 0);
    for (int& i = cur[u]; i < graph[u].size(); ++i) {
      edge& e = edges[graph[u][i]];
      if (d[e.to] == d[u] + e.cost && !visit[e.to]) {
        pair<int, long long> go = dfs(e.to, min(a, e.cap - e.flow));
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

pair<int, long long> solve() {
  pair<int, long long> result(0, 0);
  while (bfs()) {
    pair<int, long long> x = dfs(s, 0x3f3f3f3f);
    result.first += x.first;
    result.second += x.second;
  }
  return result;
}

int main() {
  scanf("%d%d%d%d", &n, &k, &ms, &me);
  int down = me, up = k - ms;
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    answer += a[i];
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &b[i]);
  }
  s = 0;
  t = n + 1;
  for (int i = 1; i <= n; ++i) {
    add_edge(i, min(i + k, t), 1, a[i] - b[i]);
  }
  for (int i = 1; i <= n; ++i) {
    add_edge(i, i + 1, i + 1 > k ? up - down : 0x3f3f3f3f, 0);
  }
  add_edge(s, 1, up, 0);
  printf("%lld\n", answer - solve().second);
  for (int i = 1; i <= n; ++i) {
    printf("%c", edges[i - 1 << 1].flow ? 'E' : 'S');
  }
  return puts(""), 0;
}
