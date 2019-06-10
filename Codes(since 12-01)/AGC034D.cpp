#include<bits/stdc++.h>

using namespace std;

const int N = 12345, inf = 1e9;
const long long llinf = 1e18;

struct edge_t {
  int to, cap, flow;
  long long cost;

  edge_t() {
  }

  edge_t(int to, int cap, int flow, long long cost): to(to), cap(cap), flow(flow), cost(cost) {
  }
};

class flow_t {
  int n, s, t, cur[N];
  vector<edge_t> edges;
  vector<int> adj[N];
  long long d[N];
  bool visit[N], inq[N];

  bool bfs() {
    for (int i = 0; i < n; ++i) {
      d[i] = llinf;
    }
    memset(cur, 0, sizeof cur);
    memset(visit, false, sizeof visit);
    memset(inq, false, sizeof inq);
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      inq[x] = false;
      for (auto i : adj[x]) {
        edge_t e = edges[i];
        if (e.flow < e.cap && d[e.to] > d[x] + e.cost) {
          d[e.to] = d[x] + e.cost;
          if (!inq[e.to]) {
            inq[e.to] = true;
            q.push(e.to);
          }
        }
      }
    }
    return d[t] != llinf;
  }

  pair<int, long long> dfs(int x, int a) {
    if (x == t || !a) {
      return pair<int, long long>(a, 0);
    } else {
      visit[x] = true;
      pair<int, long long> result(0, 0);
      for (int& i = cur[x]; i < adj[x].size(); ++i) {
        edge_t& e = edges[adj[x][i]];
        if (d[e.to] == d[x] + e.cost && !visit[e.to]) {
          pair<int, long long> go = dfs(e.to, min(a, e.cap - e.flow));
          if (go.first > 0) {
            e.flow += go.first;
            edges[adj[x][i] ^ 1].flow -= go.first;
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

 public:
  flow_t() {
  }

  flow_t(int n, int s, int t): n(n), s(s), t(t) {
  }

  void add_edge(int x, int y, int cap, long long cost) {
    edges.emplace_back(y, cap, 0, cost);
    edges.emplace_back(x, 0, 0, -cost);
    adj[x].push_back(edges.size() - 2);
    adj[y].push_back(edges.size() - 1);
  }

  pair<int, long long> min_cost_max_flow() {
    pair<int, long long> result(0, 0);
    while (bfs()) {
      pair<int, long long> t = dfs(s, inf);
      result.first += t.first;
      result.second += t.second;
    }
    return result;
  }
};

int n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  int s = 0, t = 10 * n + 1, p0 = 10 * n + 2, p1 = 10 * n + 3, p2 = 10 * n + 4, p3 = 10 * n + 5;
  flow_t graph(10 * n + 6, s, t);
  for (int i = 1, x, y, z; i <= n; ++i) {
    cin >> x >> y >> z;
    int mid = (i - 1) * 5 + 1;
    graph.add_edge(s, mid, z, 0);
    graph.add_edge(mid, (i - 1) * 5 + 2, z, x + y);
    graph.add_edge(mid, (i - 1) * 5 + 3, z, x - y);
    graph.add_edge(mid, (i - 1) * 5 + 4, z, -x + y);
    graph.add_edge(mid, (i - 1) * 5 + 5, z, -x - y);
    graph.add_edge((i - 1) * 5 + 2, p0, z, 0);
    graph.add_edge((i - 1) * 5 + 3, p1, z, 0);
    graph.add_edge((i - 1) * 5 + 4, p2, z, 0);
    graph.add_edge((i - 1) * 5 + 5, p3, z, 0);
  }
  for (int i = n + 1, x, y, z; i <= 2 * n; ++i) {
    cin >> x >> y >> z;
    int mid = (i - 1) * 5 + 1;
    graph.add_edge(mid, t, z, 0);
    graph.add_edge((i - 1) * 5 + 2, mid, z, x + y);
    graph.add_edge((i - 1) * 5 + 3, mid, z, x - y);
    graph.add_edge((i - 1) * 5 + 4, mid, z, -x + y);
    graph.add_edge((i - 1) * 5 + 5, mid, z, -x - y);
    graph.add_edge(p3, (i - 1) * 5 + 2, z, 0);
    graph.add_edge(p2, (i - 1) * 5 + 3, z, 0);
    graph.add_edge(p1, (i - 1) * 5 + 4, z, 0);
    graph.add_edge(p0, (i - 1) * 5 + 5, z, 0);
  }
  cout << -graph.min_cost_max_flow().second << '\n';
  return 0;
}
