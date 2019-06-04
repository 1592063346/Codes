#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, foo[N], key[N], answer;
vector<int> adj[N];

void dfs(int x, int f) {
  int bar = 0;
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
      bar |= foo[x] & foo[y];
      foo[x] |= foo[y];
    }
  }
  if (!foo[x]) {
    key[x] = 0;
    foo[x] = 1;
  } else {
    while ((1 << key[x]) <= bar || (foo[x] >> key[x] & 1)) {
      ++key[x];
    }
    for (int i = 0; i < key[x]; ++i) {
      foo[x] -= (foo[x] >> i & 1) << i;
    }
    foo[x] |= 1 << key[x];
    answer = max(answer, key[x]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(1, 0);
  cout << answer << '\n';
  return 0;
}
