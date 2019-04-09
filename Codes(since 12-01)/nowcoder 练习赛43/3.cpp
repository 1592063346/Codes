#include<bits/stdc++.h>

using namespace std;

class edge_t {
 public:
  int u, v, x;

  edge_t() {
  }

  edge_t(int u, int v, int x): u(u), v(v), x(x) {
  }

  bool operator < (const edge_t& a) const {
    return x < a.x;
  }
};

const int M = 1234;

vector<pair<int, int>> bottle[M];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m, k;
  long long r;
  cin >> n >> m >> k >> r;
  vector<int> t(n), f(n + 1), s(n + 1);
  vector<bool> finished(n);
  vector<edge_t> edges;
  for (int i = 0; i < n; ++i) {
    cin >> t[i];
  }
  for (int i = 0, x; i < k; ++i) {
    cin >> x;
    --x;
    finished[x] = true;
  }
  for (int i = 0; i < n; ++i) {
    bottle[finished[i] ? 0 : t[i]].emplace_back(i, n);
  }
  for (int i = 0, x, y, h; i < m; ++i) {
    cin >> x >> y >> h;
    --x;
    --y;
    bottle[h].emplace_back(x, y);
  }

  function<int (int)> find = [&] (int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
  };

  for (int i = 0; i < M; ++i) {
    for (auto p : bottle[i]) {
      edges.emplace_back(p.first, p.second, i);
    }
  }
  for (int i = 0; i <= n; ++i) {
    f[i] = i;
    s[i] = 1;
  }
  int answer = 0, block = n;
  for (auto e : edges) {
    int x, y;
    if ((x = find(e.u)) != (y = find(e.v))) {
      if (s[x] > s[y]) {
        swap(x, y);
      }
      f[x] = y;
      s[y] += s[x];
      answer += e.x;
      if (answer > r) {
        break;
      }
      if (--block == 0) {
        break;
      }
    }
  }
  cerr << answer << '\n';
  cout << (answer <= r ? "Yes" : "No") << '\n';
  return 0;
}
