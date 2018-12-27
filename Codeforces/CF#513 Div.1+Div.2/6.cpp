#include<bits/stdc++.h>

using namespace std;

const int N = 55;

int n, size[N];
vector<int> graph[N];
double f[N][N], binom[N][N];

inline void dfs(int u, int pa) {
  vector<double> g(n), tmp(n);
  memset(f[u], 0, sizeof f[u]);
  f[u][0] = 1;
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v ^ pa) {
      dfs(v, u);
      for (int i = 0; i <= size[v]; ++i) {
        g[i] = (size[v] - i) * f[v][i];
        for (int j = 0; j < i; ++j) {
          g[i] += 0.5 * f[v][j];
        }
      }
      for (int i = 0; i < n; ++i) {
        tmp[i] = f[u][i];
      }
      memset(f[u], 0, sizeof f[u]);
      for (int i = 0; i < size[u]; ++i) {
        for (int j = 0; j <= size[v]; ++j) {
          f[u][i + j] += tmp[i] * g[j] * binom[i + j][i] * binom[size[u] + size[v] - 1 - i - j][size[v] - j];
        }
      }
      size[u] += size[v];
    }
  }
}

int main() {
  scanf("%d", &n);
  double fac = 1;
  binom[0][0] = 1;
  for (int i = 1; i < n; ++i) {
    fac *= i;
    binom[i][0] = binom[i - 1][0];
    for (int j = 1; j <= i; ++j) {
      binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
    }
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    dfs(i, 0);
    printf("%.10lf\n", f[i][n - 1] / fac);
  }
  return 0;
}
