#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m, k, degree[N], visit[N], ans[N];
vector<pair<int, int> > graph[N];
pair<int, int> edge[N];

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    ++degree[u];
    ++degree[v];
    graph[u].emplace_back(v, i);
    graph[v].emplace_back(u, i);
    edge[i] = pair<int, int> (u, v);
  }
  int nodes = n;
  queue<int> Q;
  for (int i = 1; i <= n; ++i) {
    if (degree[i] < k) {
      --nodes;
      Q.push(i);
    }
  }
  for (int i = m; i; --i) {
    while (!Q.empty()) {
      int x = Q.front();
      Q.pop();
      for (auto v : graph[x]) {
        if (!visit[v.second]) {
          visit[v.second] = 1;
          if (--degree[v.first] == k - 1) {
            --nodes;
            Q.push(v.first);
          }
        }
      }
    }
    ans[i] = nodes;
    if (!visit[i]) {
      visit[i] = 1;
      if (--degree[edge[i].first] == k - 1) {
        --nodes;
        Q.push(edge[i].first);
      }
      if (--degree[edge[i].second] == k - 1) {
        --nodes;
        Q.push(edge[i].second);
      }
    }
  }
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
