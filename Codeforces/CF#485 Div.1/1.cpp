#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, k, s, d[N];
bool visit[N];
vector<int> graph[N], dist[N], sets[N];

int main() {
  scanf("%d%d%d%d", &n, &m, &k, &s);
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    sets[x].push_back(i);
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  for (int i = 1; i <= k; ++i) {
    memset(visit, false, sizeof visit);
    queue<int> que;
    for (auto v : sets[i]) {
      visit[v] = true;
      dist[v].push_back(d[v] = 0);
      que.push(v);
    }
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      for (auto v : graph[x]) {
        if (!visit[v]) {
          dist[v].push_back(d[v] = d[x] + 1);
          visit[v] = true;
          que.push(v);
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    sort(dist[i].begin(), dist[i].end());
    int answer = 0;
    for (int j = 0; j < s; ++j) {
      answer += dist[i][j];
    }
    printf("%d%c", answer, " \n"[i == n]);
  }
  return 0;
}
