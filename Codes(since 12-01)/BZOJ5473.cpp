#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10, mod = 1e9 + 7;

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

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

int n, m, answer, degree[N], dfn[N], len[N], tt;
vector<int> adj[N];

void dfs(int u, int p) {
  dfn[u] = ++tt;
  bool go = false;
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v != p || go) {
      if (!dfn[v]) {
        len[v] = len[u] + 1;
        dfs(v, u);
      } else if (dfn[v] < dfn[u]) {
        sub(answer, 1);
        add(answer, qpow(mod + 1 >> 1, len[u] - len[v] + 1));
      }
    } else {
      go = true;
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  answer = (1 + mul(m, mod + 1 >> 1)) % mod;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
    ++degree[u];
    ++degree[v];
  }
  for (int i = 1; i <= n; ++i) {
    sub(answer, qpow(mod + 1 >> 1, degree[i]));
  }
  dfs(1, 0);
  printf("%d\n", mul(answer, qpow(2, m)));
  return 0;
}
