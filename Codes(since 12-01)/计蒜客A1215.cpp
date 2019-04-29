#include<bits/stdc++.h>

using namespace std;

const int N = 345;
const double inf = 1e9, eps = 1e-10;

struct edge_t {
  int to;
  double cap, flow;

  edge_t() {
  }

  edge_t(int to, double cap, double flow): to(to), cap(cap), flow(flow) {
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

  void add_edge(int from, int to, double cap) {
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
        if (edges[y].cap - edges[y].flow > eps && !~d[edges[y].to]) {
          d[edges[y].to] = d[x] + 1;
          q.push(edges[y].to);
        }
      }
    }
    return ~d[t];
  }

  double dfs(int x, double y) {
    if (x == t || y < eps) {
      return y;
    }
    double flow = 0;
    for (int& i = cur[x]; i < adj[x].size(); ++i) {
      int j = adj[x][i];
      double f;
      if (d[x] + 1 == d[edges[j].to] && (f = dfs(edges[j].to, min(edges[j].cap - edges[j].flow, y))) > eps) {
        edges[j].flow += f;
        edges[j ^ 1].flow -= f;
        flow += f;
        y -= f;
        if (y < eps) {
          break;
        }
      }
    }
    return flow;
  }

  double maxflow() {
    double result = 0;
    while (bfs()) {
      result += dfs(s, inf);
    }
    return result;
  }
};

int n, m, value[N][N], type[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.setf(ios::fixed);
  cin >> n >> m;
  for (int i = 0, x, y, z; i < m; ++i) {
    cin >> x >> y;
    --x;
    --y;
    cin >> value[x][y];
    value[y][x] = value[x][y];
  }
  for (int i = 0; i < n; ++i) {
    cin >> type[i];
  }
  auto check = [&] (double x) {
    int alle = n * (n - 1) >> 1, s = alle + n, t = alle + n + 1, foo = 0;
    maxflow_t graph(alle + n + 2, s, t);
    double result = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        double w = value[i][j] + 2 * x;
        result += w;
        graph.add_edge(s, foo, w);
        graph.add_edge(foo, alle + i, inf);
        graph.add_edge(foo, alle + j, inf);
        ++foo;
      }
    }
    for (int i = 0; i < n; ++i) {
      if (type[i]) {
        result -= (2 * n - 1) * x;
      } else {
        graph.add_edge(alle + i, t, (2 * n - 1) * x);
      }
    }
    return result - graph.maxflow() > eps;
  };
  double l = 0, r = 100;
  for (int tt = 0; tt < 25; ++tt) {
    double mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  cout << setprecision(4) << l << '\n';
  return 0;
}
