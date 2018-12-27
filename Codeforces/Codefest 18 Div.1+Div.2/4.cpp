#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, visit[N], bfs[N], value[N];
vector<int> graph[N], arr;

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &bfs[i]);
    value[bfs[i]] = i;
  }
  queue<int> Q;
  Q.push(1);
  while (!Q.empty()) {
    int x = Q.front();
    arr.push_back(x);
    visit[x] = 1;
    Q.pop();
    vector<int> go;
    for (auto v : graph[x]) {
      if (!visit[v]) {
        go.push_back(v);
      }
    }
    sort(go.begin(), go.end(), [] (const int& a, const int& b) {
      return value[a] < value[b];
    });
    for (auto v : go) {
      Q.push(v);
    }
  }
  bool same = true;
  for (int i = 0; i < n; ++i) {
    if (arr[i] ^ bfs[i + 1]) {
      same = false;
    }
  }
  puts(same ? "yes" : "no");
  return 0;
}
