#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, m, degree[N];
vector<int> adj[N];
bool visit[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
    ++degree[x];
    ++degree[y];
  }
  for (int i = 1; i <= n; ++i) {
    if (degree[i] & 1) {
      cout << "No" << '\n';
      exit(0);
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (degree[i] >= 6) {
      cout << "Yes" << '\n';
      exit(0);
    }
  }
  int total = 0;
  for (int i = 1; i <= n; ++i) {
    if (degree[i] >= 4) {
      ++total;
    }
  }
  if (total >= 3) {
    cout << "Yes" << '\n';
    exit(0);
  } else if (total == 2) {
    int foo = -1, bar = -1;
    for (int i = 1; i <= n; ++i) {
      if (degree[i] >= 4) {
        if (!~foo) {
          foo = i;
        } else {
          bar = i;
        }
      }
    }
    int t = 0;
    function<void (int)> dfs = [&] (int x) {
      visit[x] = true;
      if (x == bar) {
        ++t;
        return;
      }
      for (auto y : adj[x]) {
        if (!visit[y] || y == bar) {
          dfs(y);
        }
      }
    };
    dfs(foo);
    if (t != 4) {
      cout << "Yes" << '\n';
      exit(0);
    }
  }
  cout << "No" << '\n';
  return 0;
}
