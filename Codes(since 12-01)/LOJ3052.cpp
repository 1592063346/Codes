#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, a[N];
vector<int> adj[N];
multiset<int> rest[N];

void dfs(int u) {
  for (auto v : adj[u]) {
    dfs(v);
    if (rest[v].size() > rest[u].size()) {
      swap(rest[u], rest[v]);
    }
    vector<int> values;
    while (rest[v].size()) {
      int x = *rest[u].rbegin();
      int y = *rest[v].rbegin();
      rest[u].erase(rest[u].find(x));
      rest[v].erase(rest[v].find(y));
      values.push_back(max(x, y));
    }
    for (auto v : values) {
      rest[u].insert(v);
    }
  }
  rest[u].insert(a[u]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 2; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    adj[x].push_back(i);
  }
  dfs(1);
  long long answer = 0;
  for (auto v : rest[1]) {
    answer += v;
  }
  printf("%lld\n", answer);
  return 0;
}
