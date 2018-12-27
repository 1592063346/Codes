#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, type[N], value[N], f[N][2];
vector<int> graph[N];
char cmd[5];

#define l graph[u][0]
#define r graph[u][1]

void dfs(int u) {
  for (auto v : graph[u]) {
    dfs(v);
  }
  switch (type[u]) {
    case 0:
      value[u] = value[l] & value[r];
      break;
    case 1:
      value[u] = value[l] | value[r];
      break;
    case 2:
      value[u] = value[l] ^ value[r];
      break;
    case 3:
      value[u] = !value[graph[u][0]];
      break;
    case 4:
      value[u] = value[u];
      break;
  }
}

void dfs(int u, int pa) {
  if (~pa) {
    if (type[pa] == 0) {
      int another = graph[pa][0] == u ? graph[pa][1] : graph[pa][0];
      f[u][0] = f[pa][0 & value[another]];
      f[u][1] = f[pa][1 & value[another]];
    }
    if (type[pa] == 1) {
      int another = graph[pa][0] == u ? graph[pa][1] : graph[pa][0];
      f[u][0] = f[pa][0 | value[another]];
      f[u][1] = f[pa][1 | value[another]];
    }
    if (type[pa] == 2) {
      int another = graph[pa][0] == u ? graph[pa][1] : graph[pa][0];
      f[u][0] = f[pa][0 ^ value[another]];
      f[u][1] = f[pa][1 ^ value[another]];
    }
    if (type[pa] == 3) {
      f[u][0] = f[pa][1];
      f[u][1] = f[pa][0];
    }
  } else {
    f[u][0] = 0;
    f[u][1] = 1;
  }
  for (auto v : graph[u]) {
    dfs(v, u);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int u, v;
    scanf("%s", cmd);
    switch (*cmd) {
      case 'A':
        type[i] = 0;
        scanf("%d%d", &u, &v);
        graph[i].push_back(u);
        graph[i].push_back(v);
        break;
      case 'O':
        type[i] = 1;
        scanf("%d%d", &u, &v);
        graph[i].push_back(u);
        graph[i].push_back(v);
        break;
      case 'X':
        type[i] = 2;
        scanf("%d%d", &u, &v);
        graph[i].push_back(u);
        graph[i].push_back(v);
        break;
      case 'N':
        type[i] = 3;
        scanf("%d", &u);
        graph[i].push_back(u);
        break;
      case 'I':
        type[i] = 4;
        scanf("%d", &value[i]);
        break;
    }
  }
  dfs(1);
  dfs(1, -1);
  for (int i = 1; i <= n; ++i) {
    if (type[i] == 4) {
      printf("%d", f[i][value[i] ^ 1]);
    }
  }
  return puts(""), 0;
}
