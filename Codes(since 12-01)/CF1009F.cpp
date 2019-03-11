#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, len[N], heavy[N], tmp[N], *f[N], *arr = tmp, answer[N];
vector<int> adj[N];

void dfs1(int u, int p) {
  for (auto v : adj[u]) {
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
  f[u][0] = 1;
  if (heavy[u]) {
    f[heavy[u]] = f[u] + 1;
    dfs2(heavy[u], u);
    answer[u] = answer[heavy[u]] + 1;
  }
  for (auto v : adj[u]) {
    if (v != p && v != heavy[u]) {
      f[v] = arr;
      arr += len[v];
      dfs2(v, u);
      for (int j = 1; j <= len[v]; ++j) {
        f[u][j] += f[v][j - 1];
        if (f[u][j] > f[u][answer[u]] || (f[u][j] == f[u][answer[u]] && j < answer[u])) {
          answer[u] = j;
        }
      }
    }
  }
  if (f[u][answer[u]] == 1) {
    answer[u] = 0;
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
  f[1] = arr;
  arr += len[1];
  dfs2(1, 0);
  for (int i = 1; i <= n; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
