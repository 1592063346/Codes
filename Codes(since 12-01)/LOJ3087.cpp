#include<bits/stdc++.h>

using namespace std;

const int N = 123456;
const long long llinf = 1e18;

bool cmin(long long& x, long long y) {
  if (x > y) {
    return x = y, true;
  } else {
    return false;
  }
}

int tt, n, m, k, pre[2][N];
vector<pair<int, int>> adj[2][N];
long long dist[2][N];
bool visit[N];

struct node_t {
  int u;
  long long d;

  node_t() {
  }

  node_t(int u, long long d): u(u), d(d) {
  }

  bool operator < (const node_t& a) const {
    return d > a.d;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> tt;
  while (tt--) {
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
      adj[0][i].clear();
      adj[1][i].clear();
    }
    for (int i = 0, x, y, z; i < m; ++i) {
      cin >> x >> y >> z;
      --x;
      --y;
      adj[0][x].emplace_back(y, z);
      adj[1][y].emplace_back(x, z);
    }
    vector<int> nodes(k);
    for (int i = 0; i < k; ++i) {
      cin >> nodes[i];
      --nodes[i];
    }
    for (int i = 0; i < 2; ++i) {
      fill(pre[i], pre[i] + n, 0);
      fill(dist[i], dist[i] + n, llinf);
      fill(visit, visit + n, false);
      priority_queue<node_t> dqueue;
      for (int j = 0; j < k; ++j) {
        int x = nodes[j];
        dist[i][x] = 0;
        pre[i][x] = x;
        dqueue.emplace(x, 0);
      }
      while (!dqueue.empty()) {
        int x = dqueue.top().u;
        dqueue.pop();
        if (!visit[x]) {
          visit[x] = true;
          for (auto e : adj[i][x]) {
            if (cmin(dist[i][e.first], dist[i][x] + e.second)) {
              pre[i][e.first] = pre[i][x];
              dqueue.emplace(e.first, dist[i][e.first]);
            }
          }
        }
      }
    }
    long long answer = llinf;
    for (int i = 0; i < n; ++i) {
      for (auto j : adj[0][i]) {
        if (pre[0][i] != pre[1][j.first]) {
          cmin(answer, dist[0][i] + j.second + dist[1][j.first]);
        }
      }
    }
    cout << answer << '\n';
  }
  return 0;
}
