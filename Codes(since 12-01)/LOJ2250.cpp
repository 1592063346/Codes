#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10, mod = 998244353;

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

int tt, n, m, fac[N], invfac[N], dfn[N], dfn_cnt, father[N], f[N], g[N];
bool not_cactus, visit[N];
vector<int> graph[N];
map<pair<int, int>, bool> ban_edge;

int binom(int n, int m) {
  return mul(fac[n], mul(invfac[m], invfac[n - m]));
}

void init(int n) {
  fac[0] = 1;
  invfac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  invfac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    invfac[i] = mul(invfac[i + 1], i + 1);
  }
  g[0] = 1;
  g[2] = 1;
  for (int i = 4; i <= n; i += 2) {
    g[i] = (g[i - 2] + mul(g[i - 4], mul(i - 2, i - 3))) % mod;
  }
}

void dfs(int u, int p) {
  dfn[u] = ++dfn_cnt;
  for (auto v : graph[u]) {
    if (v != p) {
      if (!dfn[v]) {
        father[v] = u;
        dfs(v, u);
      } else if (dfn[v] < dfn[u]) {
        for (int x = u; x != v; x = father[x]) {
          if (ban_edge.count(pair<int, int>(min(x, father[x]), max(x, father[x])))) {
            not_cactus = true;
            return;
          } else {
            ban_edge[pair<int, int>(min(x, father[x]), max(x, father[x]))] = true;
          }
        }
        if (ban_edge.count(pair<int, int>(min(u, v), max(u, v)))) {
          not_cactus = true;
          return;
        } else {
          ban_edge[pair<int, int>(min(u, v), max(u, v))] = true;
        }
      }
    }
    if (not_cactus) {
      return;
    }
  }
}

void dp(int u, bool is_root) {
  visit[u] = true;
  f[u] = 1;
  int size = 0;
  for (auto v : graph[u]) {
    if (!ban_edge[pair<int, int>(min(u, v), max(u, v))] && !visit[v]) {
      dp(v, false);
      f[u] = mul(f[u], f[v]);
      ++size;
    }
  }
  int coef = is_root ? 1 : size + 1;
  for (int i = 1; i <= (size >> 1); ++i) {
    add(coef, mul(mul(binom(size, i << 1), g[i << 1]), is_root ? 1 : size - (i << 1) + 1));
  }
  f[u] = mul(f[u], coef);
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d", &n, &m);
    init(n);
    for (int i = 1; i <= n; ++i) {
      graph[i].clear();
      father[i] = 0;
      dfn[i] = 0;
    }
    for (int i = 1; i <= m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      graph[u].push_back(v);
      graph[v].push_back(u);
    }
    not_cactus = false;
    ban_edge.clear();
    dfn_cnt = 0;
    dfs(1, 0);
    if (not_cactus) {
      puts("0");
      continue;
    }
    for (int i = 1; i <= n; ++i) {
      visit[i] = false;
    }
    int answer = 1;
    for (int i = 1; i <= n; ++i) {
      if (!visit[i]) {
        dp(i, true);
        answer = mul(answer, f[i]);
      }
    }
    printf("%d\n", answer);
  }
  return 0;
}
