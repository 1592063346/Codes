#include<bits/stdc++.h>

using namespace std;

#define rg register
#define pb push_back

const int N = 1e5 + 10;

int n, k, degree[N], total[N];
set<int> G[N];

int main() {
  scanf("%d%d", &n, &k);
  if (n == 1) {
    return puts(!k ? "Yes" : "No"), 0;
  }
  for (rg int i = 1; i < n; ++i) {
    int u, v; scanf("%d%d", &u, &v);
    G[u].insert(v);
    G[v].insert(u);
    ++degree[u], ++degree[v];
  }
  int nodes = n;
  for (rg int i = 1;; ++i) {
    memset(total, 0, sizeof total);
    vector<int> s;
    for (rg int j = 1; j <= n; ++j) {
      if (degree[j] == 1) {
        --nodes;
        int v = *G[j].begin();
        ++total[v];
        G[v].erase(j);
        G[j].erase(v);
        --degree[j];
        s.pb(v);
      }
    }
    for (auto v : s) {
      --degree[v];
    }
    for (rg int j = 1; j <= n; ++j) {
      if (total[j] > 0 && total[j] < 3) {
        return puts("No"), 0;
      }
    }
    if (nodes == 1) {
      return puts(i == k ? "Yes" : "No"), 0;
    }
  }
  return 0;
}
