#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, value[N];

class tree_t {
 public:
  vector<int> adj[N];
  int father[20][N], depth[N];

  void add(int x, int y) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  void dfs(int x, int f) {
    father[0][x] = f;
    for (int i = 1; i < 17; ++i) {
      father[i][x] = father[i - 1][father[i - 1][x]];
    }
    for (auto y : adj[x]) {
      if (y != f) {
        depth[y] = depth[x] + 1;
        dfs(y, x);
      }
    }
  }

  void init() {
    dfs(1, 0);
  }

  int get_lca(int x, int y) {
    if (depth[x] < depth[y]) {
      swap(x, y);
    }
    for (int i = 16; ~i; --i) {
      if (depth[x] - (1 << i) >= depth[y]) {
        x = father[i][x];
      }
    }
    if (x == y) {
      return x;
    }
    for (int i = 16; ~i; --i) {
      if (father[i][x] != father[i][y]) {
        x = father[i][x];
        y = father[i][y];
      }
    }
    return father[0][x];
  }
} a, b;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    a.add(x, y);
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    b.add(x, y);
  }
  a.init();
  b.init();
  int foo = n << 1, bar = 0;
  auto solve = [&] (tree_t a, tree_t b) {
    memset(value, 0, sizeof value);
    for (int i = 1; i <= n; ++i) {
      for (auto j : b.adj[i]) {
        if (i < j) {
          int lca = a.get_lca(i, j);
          ++value[i];
          ++value[j];
          --value[lca];
          --value[lca];
        }
      }
    }
    function<void (int)> dfs = [&] (int x) {
      for (auto y : a.adj[x]) {
        if (y != a.father[0][x]) {
          dfs(y);
          if (1 + value[y] < foo) {
            foo = 1 + value[y];
            bar = 1;
          } else if (1 + value[y] == foo) {
            ++bar;
          }
          value[x] += value[y];
        }
      }
    };
    dfs(1);
  };
  solve(a, b);
  if (foo != 2) {
    solve(b, a);
  }
  cout << foo << ' ' << bar << '\n';
  return 0;
}
