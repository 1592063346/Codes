#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

void cmax(long long& x, long long y) {
  if (x < y) {
    x = y;
  }
}

int n, w[N];
long long f[N], answer;
vector<pair<int, int>> graph[N];

void dfs(int u, int father) {
  f[u] = w[u];
  for (auto e : graph[u]) {
    if (e.first != father) {
      dfs(e.first, u);
      cmax(answer, f[u] - e.second + f[e.first]);
      cmax(f[u], w[u] - e.second + f[e.first]);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &w[i]);
    cmax(answer, w[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    graph[u].emplace_back(v, c);
    graph[v].emplace_back(u, c);
  }
  dfs(1, 0);
  printf("%lld\n", answer);
  return 0;
}
