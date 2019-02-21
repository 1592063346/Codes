#include<bits/stdc++.h>

using namespace std;

const int N = 1e2 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, m, father[N], degree[N], binom[N][N], size[N], f[N][N], g[N];
vector<int> graph[N];
bool went[N];

int find(int x) {
  return father[x] == x ? x : father[x] = find(father[x]);
}

void init_binom(int n) {
  binom[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      binom[i][j] = (binom[i - 1][j] + (j ? binom[i - 1][j - 1] : 0)) % mod;
    }
  }
}

void dfs(int u) {
  f[u][0] = 1;
  for (auto v : graph[u]) {
    dfs(v);
    memset(g, 0, sizeof g);
    for (int i = 0; i <= size[u]; ++i) {
      for (int j = 1; j <= size[v]; ++j) {
        for (int k = max(i, j); k <= size[u] + size[v]; ++k) {
          if (j - k + i >= 0) {
            add(g[k], mul(mul(f[u][i], f[v][j]), mul(binom[k][i], binom[i][j - k + i])));
          }
        }
      }
    }
    memcpy(f[u], g, sizeof g);
    size[u] += size[v];
  }
  ++size[u];
  for (int i = size[u]; i; --i) {
    f[u][i] = f[u][i - 1];
  }
  f[u][0] = 0;
}

int main() {
  scanf("%d%d", &n, &m);
  init_binom(n + 1);
  for (int i = 1; i <= n; ++i) {
    father[i] = i;
  }
  vector<pair<int, int>> edges;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    char type[3];
    scanf("%d%s%d", &u, type, &v);
    if (*type == '=') {
      father[find(u)] = find(v);
    } else {
      edges.emplace_back(u, v);
    }
  }
  for (auto e : edges) {
    graph[find(e.first)].push_back(find(e.second));
    ++degree[find(e.second)];
  }
  for (int i = 1; i <= n; ++i) {
    if (!degree[find(i)]) {
      ++degree[find(i)];
      graph[0].push_back(find(i));
    }
  }
  queue<int> que;
  que.push(0);
  while (!que.empty()) {
    int x = que.front();
    went[x] = true;
    que.pop();
    for (auto v : graph[x]) {
      if (!--degree[v]) {
        que.push(v);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (!went[find(i)]) {
      return puts("0"), 0;
    }
  }
  dfs(0);
  int answer = 0;
  for (int i = 1; i <= size[0]; ++i) {
    add(answer, f[0][i]);
  }
  printf("%d\n", answer);
  return 0;
}
