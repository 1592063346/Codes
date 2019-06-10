#include<bits/stdc++.h>

using namespace std;

const int N = 12345;

int tt, n, m, degree[N], foo[N], p[N];
vector<int> adj[N];
bool used[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> tt;
  while (tt--) {
    auto print = [&] (vector<int> x) {
      cout << x.size();
      for (auto p : x) {
        cout << ' ' << p;
      }
      cout << '\n';
    };
    cin >> n >> m;
    memset(degree, 0, sizeof degree);
    memset(used, false, sizeof used);
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
    }
    for (int i = 1, x, y; i <= m; ++i) {
      cin >> x >> y;
      adj[x].push_back(y);
      adj[y].push_back(x);
      ++degree[x];
      ++degree[y];
    }
    auto check = [&] (int value) {
      memcpy(foo, degree, sizeof degree);
      queue<int> q;
      for (int i = 1; i <= n; ++i) {
        if (foo[i] < value) {
          foo[i] = 0;
          q.push(i);
        }
      }
      while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto y : adj[x]) {
          if (--foo[y] == value - 1) {
            foo[y] = 0;
            q.push(y);
          }
        }
      }
      vector<int> nodes;
      for (int i = 1; i <= n; ++i) {
        if (foo[i] >= value) {
          nodes.push_back(i);
        }
      }
      return nodes;
    };
    int l = 1, r = n;
    while (l != r) {
      int mid = (l + r >> 1) + 1;
      if (check(mid).size()) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    print(check(l));
    vector<int> best;
    for (int i = 1; i <= n; ++i) {
      p[i] = i;
    }
    sort(p + 1, p + 1 + n, [&] (const int& x, const int& y) {
      return degree[x] < degree[y];
    });
    for (int i = 1; i <= n; ++i) {
      int x = p[i];
      if (!used[x]) {
        used[x] = true;
        best.push_back(x);
        for (auto y : adj[x]) {
          used[y] = true;
        }
      }
    }
    print(best);
    if (n / (l + 1) > best.size() || n / (best.size() + 1) > l) {
      cerr << "wrong: " << l << ' ' << best.size() << ' ' << n << '\n';
    } else {
      cerr << "ok." << '\n';
    }
  }
  return 0;
}
