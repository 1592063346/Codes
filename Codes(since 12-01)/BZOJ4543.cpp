#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, len[N], heavy[N], tmp_f[N], *f[N], *arr_f = tmp_f;
long long answer, tmp_g[N << 1], *g[N], *arr_g = tmp_g;
vector<int> adj[N];

void dfs1(int u, int p) {
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v != p) {
      dfs1(v, u);
      if (len[v] > len[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
  len[u] = len[heavy[u]] + 1;
}

void dfs2(int u, int p) {
  if (heavy[u]) {
    f[heavy[u]] = f[u] + 1;
    g[heavy[u]] = g[u] - 1;
    dfs2(heavy[u], u);
  }
  answer += g[u][0];
  f[u][0] = 1;
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v != p && v != heavy[u]) {
      f[v] = arr_f;
      arr_f += len[v];
      arr_g += len[v];
      g[v] = arr_g;
      arr_g += len[v];
      dfs2(v, u);
      for (int j = 0; j < len[v]; ++j) {
        answer += j ? f[u][j - 1] * g[v][j] : 0;
        answer += g[u][j + 1] * f[v][j];
      }
      for (int j = 0; j < len[v]; ++j) {
        g[u][j + 1] += (long long) f[u][j + 1] * f[v][j];
        if (j) {
          g[u][j - 1] += g[v][j];
        }
        f[u][j + 1] += f[v][j];
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs1(1, 0);
  f[1] = arr_f;
  arr_f += len[1];
  arr_g += len[1];
  g[1] = arr_g;
  arr_g += len[1];
  dfs2(1, 0);
  printf("%lld\n", answer);
  return 0;
}
