#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10, inf = 0x3f3f3f3f;

int n, m, d[N], from[N];
vector<int> graph[N];

void bfs(int s, int ban) {
  queue<int> que;
  que.push(s);
  d[s] = 0;
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (auto y : graph[x]) {
      if (y != ban && d[y] > d[x] + 1) {
        d[y] = d[x] + 1;
        from[y] = x;
        que.push(y);
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  memset(d, 0x3f, sizeof d);
  bfs(1, 0);
  if (d[n] <= 4) {
    vector<int> answer;
    for (int u = n; u; u = from[u]) {
      answer.push_back(u);
    }
    printf("%d\n", d[n]);
    for (int i = answer.size() - 1; ~i; --i) {
      printf("%d ", answer[i]);
    }
    return 0;
  }
  int p = 0;
  for (int i = 1; i <= n; ++i) {
    if (d[i] == 2) {
      p = i;
    }
  }
  if (p) {
    puts("4");
    printf("1 %d %d 1 %d\n", from[p], p, n);
    return 0;
  }
  vector<pair<int, int>> go;
  for (auto x : graph[1]) {
    go.emplace_back(graph[x].size(), x);
  }
  sort(go.begin(), go.end());
  memset(d, 0x3f, sizeof d);
  for (auto p : go) {
    if (d[p.second] == inf) {
      bfs(p.second, 1);
    } else if (d[p.second] == 2) {
      puts("5");
      printf("1 %d %d %d %d %d\n", from[from[p.second]], from[p.second], p.second, from[from[p.second]], n);
      return 0;
    }
  }
  return puts("-1"), 0;
}
