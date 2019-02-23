#include<bits/stdc++.h>

using namespace std;

const int N = 2e2 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

int n, m, pow_2[N], dfn[N], size[N], father[N], dfn_cnt, w[N], f[N][N][N], s1[N][N][N], s2[N][N][N];
vector<int> graph[N];
bool ban[N][N], counted[N];

void dfs(int u, int p) {
  dfn[u] = ++dfn_cnt;
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v != p) {
      if (!dfn[v]) {
        father[v] = u;
        dfs(v, u);
        size[u] += size[v];
      } else if (dfn[v] < dfn[u]) {
        for (int x = u; x != v; x = father[x]) {
          ban[x][father[x]] = true;
          ban[father[x]][x] = true;
        }
        ban[u][v] = true;
        ban[v][u] = true;
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  pow_2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pow_2[i] = (pow_2[i - 1] << 1) % mod;
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs(1, 0);
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    for (auto j : graph[i]) {
      if (!ban[i][j] && dfn[i] < dfn[j]) {
        add(answer, mul(pow_2[size[j]] - 1, pow_2[n - size[j]] - 1));
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (!counted[i]) {
      vector<int> points(1, i);
      counted[i] = true;
      for (int x = i;;) {
        bool found = false;
        for (auto y : graph[x]) {
          if (ban[x][y] && !counted[y]) {
            counted[y] = true;
            points.push_back(y);
            found = true;
            x = y;
            break;
          }
        }
        if (!found) {
          break;
        }
      }
      for (auto x : points) {
        w[x] = 1;
        for (auto y : graph[x]) {
          if (!ban[x][y]) {
            w[x] += dfn[y] > dfn[x] ? size[y] : n - size[x];
          }
        }
      }
      for (int i = 0; i < points.size(); ++i) {
        memset(f[i], 0, sizeof f[i]);
        memset(s1[i], 0, sizeof s1[i]);
        memset(s2[i], 0, sizeof s2[i]);
        f[i][i][0] = pow_2[w[points[i]]] - 1;
        s1[i][i][0] = f[i][i][0];
        for (int j = 1; j <= points.size(); ++j) {
          s1[i][i][j] = s1[i][i][0];
        }
      }
      for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
          for (int k = 1; k <= points.size(); ++k) {
            if (k <= j - i) {
              int ways = ((s1[i][j - k][k] + s2[i][j - 1][k] - s2[i][j - k][k]) % mod + mod) % mod;
              f[i][j][k] = mul(pow_2[w[points[j]]] - 1, ways);
            }
            s1[i][j][k] = (s1[i][j][k - 1] + f[i][j][k]) % mod;
            s2[i][j][k] = (s2[i][j - 1][k] + f[i][j][k]) % mod;
          }
        }
      }
      for (int i = 0; i < points.size(); ++i) {
        for (int j = i; j < points.size(); ++j) {
          for (int k = 0; k <= j - i; ++k) {
            add(answer, mul(min((int) points.size() - k, j - i), f[i][j][k]));
          }
        }
      }
    }
  }
  printf("%d\n", mul(answer, qpow(pow_2[n], mod - 2)));
  return 0;
}
