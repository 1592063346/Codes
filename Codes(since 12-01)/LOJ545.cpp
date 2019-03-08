#include<bits/stdc++.h>

using namespace std;

const int N = 12e5 + 10;
const long long inf = 1e15;

struct edge_t {
  int to, cap, flow;
  long long cost;

  edge_t() {}
  edge_t(int to, int cap, int flow, long long cost): to(to), cap(cap), flow(flow), cost(cost) {}
};

int n, m, s, c, t, k, a[N], b[N], cur[N];
bool inq[N], visit[N];
long long d[N];
map<int, int> times_a, times_b, appeared, same;
vector<int> adj[N];
vector<edge_t> edges;

void add_edge(int u, int v, int cap, long long cost) {
  edges.emplace_back(v, cap, 0, cost);
  edges.emplace_back(u, 0, 0, -cost);
  adj[u].push_back(edges.size() - 2);
  adj[v].push_back(edges.size() - 1);
}

bool bfs() {
  for (int i = 0; i < 70; ++i) {
    cur[i] = 0;
    inq[i] = false;
    visit[i] = false;
    d[i] = inf;
  }
  queue<int> que;
  que.push(s);
  d[s] = 0;
  inq[s] = true;
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    inq[x] = false;
    for (auto v : adj[x]) {
      edge_t& e = edges[v];
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
    for (int& i = cur[u]; i < adj[u].size(); ++i) {
      edge_t& e = edges[adj[u][i]];
      if (d[e.to] == d[u] + e.cost && !visit[e.to]) {
        pair<int, long long> go = dfs(e.to, min(a, e.cap - e.flow));
        if (go.first > 0) {
          e.flow += go.first;
          edges[adj[u][i] ^ 1].flow -= go.first;
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
    pair<int, long long> x = dfs(s, k);
    if (x.second > 0) {
      break;
    }
    result.first += x.first;
    result.second += x.second;
  }
  return result;
}

int main() {
  scanf("%d", &n);
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    if (a[i]) {
      ++appeared[a[i]];
      answer += a[i] & -a[i];
      ++times_a[a[i] & -a[i]];
    }
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &b[i]);
    if (b[i]) {
      if (appeared[b[i]]) {
        --appeared[b[i]];
        ++same[b[i] & -b[i]];
      }
      ++times_b[b[i] & -b[i]];
    }
  }
  s = 0;
  c = 1;
  t = 2;
  scanf("%d", &k);
  add_edge(s, c, k, 0);
  for (int i = 0, x = 3; (1 << i) <= 1e9; ++i, x += 2) {
    add_edge(c, x, times_a[1 << i], 0);
    add_edge(x + 1, t, times_b[1 << i], 0);
    add_edge(x, x + 1, same[1 << i], -(1 << i));
    for (int j = i - 1, y = x - 1; ~j; --j, y -= 2) {
      add_edge(x, y, k, (1 << j) - (1 << i));
    }
  }
  answer += solve().second;
  printf("%lld\n", answer);
  return 0;
}
