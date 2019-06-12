#include<bits/stdc++.h>

using namespace std;

const int N = 432, inf = 1e9;
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

int n, m, x[N], y[N], a[N], b[N], l[N], r[N];
long long w[N];
string t[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> x[i] >> y[i] >> w[i];
  }
  cin >> m;
  for (int i = 1; i <= m; ++i) {
    cin >> t[i] >> a[i] >> b[i];
  }
  long long answer = 0;
  auto solve = [&] (int take) {
    for (int i = 1; i <= take; ++i) {
      l[i] = l[take + i] = 1;
      r[i] = r[take + i] = 100;
    }
    for (int i = 1; i <= m; ++i) {
      if (b[i] < take) {
        if (t[i] == "L") {
          l[b[i] + 1] = a[i] + 1;
        }
        if (t[i] == "R") {
          r[take - b[i]] = a[i] - 1;
        }
        if (t[i] == "D") {
          l[b[i] + 1 + take] = a[i] + 1;
        }
        if (t[i] == "U") {
          r[take - b[i] + take] = a[i] - 1;
        }
      }
    }
    for (int i = 2; i <= take; ++i) {
      l[i] = max(l[i], l[i - 1]);
      l[take + i] = max(l[take + i], l[take + i - 1]);
    }
    for (int i = take - 1; i; --i) {
      r[i] = min(r[i], r[i + 1]);
      r[take + i] = min(r[take + i], r[take + i + 1]);
    }
    int s = 0, t = 200 + take * 2 + 1;
    flow_t graph(t + 1, s, t);
    for (int i = 1; i <= take; ++i) {
      if (l[i] > r[i] || l[take + i] > r[take + i]) {
        return 0ll;
      }
      graph.add_edge(s, 200 + i, 1, 0);
      graph.add_edge(200 + take + i, t, 1, 0);
      for (int j = l[i]; j <= r[i]; ++j) {
        graph.add_edge(200 + i, j, 1, 0);
      }
      for (int j = l[take + i]; j <= r[take + i]; ++j) {
        graph.add_edge(100 + j, 200 + take + i, 1, 0);
      }
    }
    for (int i = 1; i <= n; ++i) {
      graph.add_edge(x[i], 100 + y[i], 1, -w[i]);
    }
    return -graph.min_cost_max_flow().second;
  };
  for (int take = 1; take <= n; ++take) {
    answer = max(answer, solve(take));
  }
  cout << answer << '\n';
  return 0;
}
