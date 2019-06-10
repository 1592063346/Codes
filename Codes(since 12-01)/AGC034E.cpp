#include<bits/stdc++.h>

using namespace std;

const int N = 2345;

int n, root, size[N], foo[N], bar[N];
vector<int> adj[N];
string s;

void dfs(int x, int f) {
  size[x] = s[x - 1] == '1';
  foo[x] = bar[x] = 0;
  int max_son = 0;
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
      size[x] += size[y];
      foo[x] += foo[y];
      if (foo[y] > foo[max_son]) {
        max_son = y;
      }
    }
  }
  bar[x] = max(0, bar[max_son] - foo[x] + foo[max_son]);
  if (x != root) {
    foo[x] += size[x];
    bar[x] += size[x];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> s;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  int answer = n * n;
  for (root = 1; root <= n; ++root) {
    dfs(root, 0);
    if (!bar[root] && !(foo[root] & 1)) {
      answer = min(answer, foo[root] >> 1);
    }
  }
  cout << (answer == n * n ? -1 : answer) << '\n';
  return 0;
}
