#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, k, answer, a[N], d[N];
vector<int> adj[N];

void dfs(int x) {
  for (auto y : adj[x]) {
    dfs(y);
    d[x] = max(d[x], d[y] + 1);
  }
  if (x > 1 && d[x] == k - 1 && a[x] != 1) {
    ++answer;
    d[x] = -1;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k >> a[1];
  if (a[1] != 1) {
    ++answer;
  }
  for (int i = 2; i <= n; ++i) {
    cin >> a[i];
    adj[a[i]].push_back(i);
  }
  dfs(1);
  cout << answer << '\n';
  return 0;
}
