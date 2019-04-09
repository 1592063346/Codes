#include<bits/stdc++.h>

using namespace std;

const int inf = 123456789;
const long long llinf = 1e15;

class edge_t {
 public:
  int to, cap, flow;

  edge_t() {
  }

  edge_t(int to, int cap, int flow): to(to), cap(cap), flow(flow) {
  }
};

class maxflow_t {
 public:
  int n, s, t;
  vector<vector<int>> adj;
  vector<edge_t> edges;
  vector<int> d, cur;

  maxflow_t(int n, int s, int t): n(n), s(s), t(t) {
    adj.resize(n);
    d.resize(n);
    cur.resize(n);
  }

  void add_edge(int from, int to, int cap) {
    edges.emplace_back(to, cap, 0);
    edges.emplace_back(from, 0, 0);
    int z = edges.size();
    adj[from].push_back(z - 2);
    adj[to].push_back(z - 1);
  }

  bool bfs() {
    fill(d.begin(), d.end(), -1);
    fill(cur.begin(), cur.end(), 0);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (auto y : adj[x]) {
        if (edges[y].flow < edges[y].cap && !~d[edges[y].to]) {
          d[edges[y].to] = d[x] + 1;
          q.push(edges[y].to);
        }
      }
    }
    return ~d[t];
  }

  int dfs(int x, int y) {
    if (x == t || !y) {
      return y;
    }
    int flow = 0;
    for (int& i = cur[x]; i < adj[x].size(); ++i) {
      int j = adj[x][i], f;
      if (d[x] + 1 == d[edges[j].to] && (f = dfs(edges[j].to, min(edges[j].cap - edges[j].flow, y))) > 0) {
        edges[j].flow += f;
        edges[j ^ 1].flow -= f;
        flow += f;
        y -= f;
        if (!y) {
          break;
        }
      }
    }
    return flow;
  }

  int maxflow() {
    int result = 0;
    while (bfs()) {
      result += dfs(s, inf);
    }
    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m, all = 0;
  cin >> n >> m;
  vector<int> v(n), w(n);
  vector<vector<long long>> dist(n, vector<long long>(n, llinf));
  for (int i = 0; i < n; ++i) {
    cin >> v[i] >> w[i];
    all += v[i];
  }

  auto cmin = [&] (long long& x, long long y) {
    return x > y ? x = y, true : false;
  };

  for (int i = 0, x, y, z; i < m; ++i) {
    cin >> x >> y >> z;
    --x;
    --y;
    cmin(dist[x][y], (long long) z);
    cmin(dist[y][x], (long long) z);
  }
  for (int i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cmin(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  auto solve = [&] (long long x) {
    maxflow_t flow((n << 1) + 2, n << 1, n << 1 | 1);
    for (int i = 0; i < n; ++i) {
      flow.add_edge(n << 1, i << 1, v[i]);
      flow.add_edge(i << 1 | 1, n << 1 | 1, w[i]);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][j] <= x) {
          flow.add_edge(i << 1, j << 1 | 1, inf);
        }
      }
    }
    return flow.maxflow() == all;
  };

  long long l = 0, r = 2e12;
  while (l != r) {
    long long mid = l + r >> 1;
    if (solve(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << (!solve(l) ? -1 : l) << '\n';
  return 0;
}
