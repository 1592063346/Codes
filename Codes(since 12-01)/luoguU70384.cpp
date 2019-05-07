#include<bits/stdc++.h>

using namespace std;

const int N = 5678;

int n, m, belong[N];
bool lose[N], e[N];
vector<int> adj[N], arcadj[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> belong[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> e[i];
  }
  for (int i = 0, x, y; i < m; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    arcadj[y].push_back(x);
  }
  auto bfs = [&] (int side, vector<int> sources) {
    vector<int> degree(n, 0);
    vector<bool> ok(n, false);
    queue<int> q;
    for (auto x : sources) {
      ok[x] = true;
      q.push(x);
    }
    for (int i = 0; i < n; ++i) {
      for (auto j : adj[i]) {
        if (!lose[j]) {
          if (belong[i] == side) {
            degree[i] = 1;
          } else {
            ++degree[i];
          }
        }
      }
    }
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (auto y : arcadj[x]) {
        if (!lose[y] && !ok[y]) {
          if (--degree[y] == 0) {
            ok[y] = true;
            q.push(y);
          }
        }
      }
    }
    vector<int> result;
    for (int i = 0; i < n; ++i) {
      if (ok[i]) {
        result.push_back(i);
      }
    }
    return result;
  };
  while (1) {
    vector<int> rest, foo, bar;
    vector<bool> ok(n, false);
    for (int i = 0; i < n; ++i) {
      if (!lose[i]) {
        rest.push_back(i);
      }
    }
    if (!rest.size()) {
      break;
    }
    for (auto x : rest) {
      if (e[x]) {
        foo.push_back(x);
      }
    }
    foo = bfs(1, foo);
    if (foo.size() == rest.size()) {
      break;
    }
    for (auto x : foo) {
      ok[x] = true;
    }
    for (auto x : rest) {
      if (!ok[x]) {
        bar.push_back(x);
      }
    }
    bar = bfs(0, bar);
    for (auto x : bar) {
      lose[x] = true;
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << (!lose[i]) << " \n"[i + 1 == n];
  }
  return 0;
}
