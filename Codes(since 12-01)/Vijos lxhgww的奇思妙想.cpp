#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

int n, q, len[N], depth[N], heavy[N], top[N], father[19][N], hbit[N];
vector<int> adj[N], up[N], down[N];

void dfs1(int u, int p) {
  for (int i = 1; (1 << i) <= n; ++i) {
    father[i][u] = father[i - 1][father[i - 1][u]];
  }
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v != p) {
      father[0][v] = u;
      depth[v] = depth[u] + 1;
      dfs1(v, u);
      if (len[v] > len[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
  len[u] = len[heavy[u]] + 1;
}

void dfs2(int u, int t) {
  top[u] = t;
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v != father[0][u]) {
      dfs2(v, v == heavy[u] ? t : v);
    }
  }
  if (top[u] == u) {
    for (int x = u, y = u, j = 0; j < len[u]; ++j, x = father[0][x], y = heavy[y]) {
      up[u].push_back(x);
      down[u].push_back(y);
    }
  }
}

int get_anc(int x, int k) {
  if (!k) {
    return x;
  } else {
    x = father[hbit[k]][x];
    k -= 1 << hbit[k];
    if (!x) {
      return 0;
    } else {
      if (depth[x] - depth[top[x]] >= k) {
        return down[top[x]][depth[x] - depth[top[x]] - k];
      } else {
        return up[top[x]][k - depth[x] + depth[top[x]]];
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; (1 << i) <= n; ++i) {
    hbit[1 << i] = i;
  }
  for (int i = 1; i <= n; ++i) {
    if (!hbit[i]) {
      hbit[i] = hbit[i - (i & -i)];
    }
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  up[0].resize(n);
  scanf("%d", &q);
  int last_answer = 0;
  while (q--) {
    int x, k;
    scanf("%d%d", &x, &k);
    x ^= last_answer;
    k ^= last_answer;
    printf("%d\n", last_answer = get_anc(x, k));
  }
  return 0;
}
