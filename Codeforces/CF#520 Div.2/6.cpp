#include<bits/stdc++.h>

using namespace std;

#define rg register
#define pb push_back

template<typename T> inline bool checkMin(T& a, const T& b) {
  return a > b ? a = b, true : false;
}

const int N = 3e5 + 10;

int n, m, f[N], degree[N];
vector<int> G1[N], G2[N], G[N];

inline void add(int u, int v) {
  G1[u].pb(v);
  G2[v].pb(u);
}

inline void toposort() {
  queue<int> Q;
  for (rg int i = 1; i <= n; ++i) {
    for (auto v : G[i]) {
      ++degree[v];
    }
  }
  int all = n;
  for (rg int i = 1; i <= n; ++i) {
    if (!degree[i]) {
      Q.push(i), --all;
    }
  }
  while (!Q.empty()) {
    int x = Q.front(); Q.pop();
    if (Q.empty()) {
      f[x] += all;
    } else if (Q.size() == 1) {
      int y = Q.front();
      bool tag = true;
      for (auto v : G[y]) {
        tag &= degree[v] > 1;
      }
      f[x] += all * tag;
    }
    for (auto v : G[x]) {
      if (!--degree[v]) {
        Q.push(v), --all;
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (rg int i = 1; i <= m; ++i) {
    int u, v; scanf("%d%d", &u, &v);
    add(u, v);
  }
  for (rg int i = 1; i <= n; ++i) {
    G[i] = G1[i];
  }
  toposort();
  for (rg int i = 1; i <= n; ++i) {
    G[i] = G2[i];
  }
  toposort();
  int ans = 0;
  for (rg int i = 1; i <= n; ++i) {
    if (f[i] + 1 >= n - 1) {
      ++ans;
    }
  }
  printf("%d\n", ans);
  return 0;
}
