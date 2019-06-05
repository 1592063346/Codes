#include<bits/stdc++.h>

using namespace std;

const int N = 3456;

int n, a[N];
vector<int> adj[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  vector<int> answer;
  for (int i = 1; i <= n; ++i) {
    function<bool (int, int)> dfs = [&] (int x, int f) {
      for (auto y : adj[x]) {
        if (y != f) {
          if (a[y] < a[x] && !dfs(y, x)) {
            return true;
          }
        }
      }
      return false;
    };
    if (dfs(i, 0)) {
      answer.push_back(i);
    }
  }
  for (int i = 0; i < answer.size(); ++i) {
    cout << answer[i] << " \n"[i + 1 == answer.size()];
  }
  return 0;
}
