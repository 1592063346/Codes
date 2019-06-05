#include<bits/stdc++.h>

using namespace std;

const int N = 2345;

int n, a[N], b[N], degree[N];
vector<int> adj[N], new_adj[N];
bool visit[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      if (__gcd(a[i], a[j]) != 1) {
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    }
  }
  function<void (int)> dfs = [&] (int x) {
    visit[x] = true;
    for (auto y : adj[x]) {
      if (!visit[y]) {
        new_adj[x].push_back(y);
        ++degree[y];
        dfs(y);
      }
    }
  };
  for (int i = 1; i <= n; ++i) {
    if (!visit[i]) {
      dfs(i);
    }
  }
  int t = 0;
  priority_queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (!degree[i]) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int x = q.top();
    q.pop();
    b[++t] = a[x];
    for (auto y : new_adj[x]) {
      if (--degree[y] == 0) {
        q.push(y);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    cout << b[i] << " \n"[i == n];
  }
  return 0;
}
