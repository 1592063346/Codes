#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, K = 205, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, k, stirling[K][K], f[N][K], fac[N], g[K], result[K], size[N];
vector<int> adj[N];

void dfs(int u, int p) {
  f[u][0] = 1;
  for (auto v : adj[u]) {
    if (v != p) {
      dfs(v, u);
      for (int i = 0; i <= k; ++i) {
        g[i] = f[u][i];
      }
      for (int i = 0; i <= min(k, size[u]); ++i) {
        for (int j = 0; j <= min(k - i, size[v]); ++j) {
          add(f[u][i + j], mul(g[i], f[v][j]));
          add(f[u][i + j + 1], mul(g[i], f[v][j]));
          add(result[i + j], mul(g[i], f[v][j]));
          add(result[i + j + 1], mul(g[i], f[v][j]));
        }
      }
      for (int i = 0; i <= k; ++i) {
        add(f[u][i], f[v][i]);
        add(f[u][i + 1], f[v][i]);
      }
      size[u] += size[v];
    }
  }
  ++size[u];
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(1, 0);
  stirling[0][0] = fac[0] = 1;
  for (int i = 1; i <= k; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  for (int i = 1; i <= k; ++i) {
    for (int j = 1; j <= i; ++j) {
      stirling[i][j] = (stirling[i - 1][j - 1] + mul(stirling[i - 1][j], j)) % mod;
    }
  }
  int answer = 0;
  for (int i = 0; i <= k; ++i) {
    add(answer, mul(stirling[k][i], mul(fac[i], result[i])));
  }
  printf("%d\n", answer);
  return 0;
}
