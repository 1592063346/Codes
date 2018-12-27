#include<bits/stdc++.h>

using namespace std;

#define rg register

const int N = 3e5 + 10, mod = 998244353;

inline void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

inline void mul(int& x, int y) {
  x = 1ll * x * y % mod;
}

inline int qpow(int v, int p) {
  int res = 1;
  for (; p; p >>= 1, mul(v, v)) {
    if (p & 1) {
      mul(res, v);
    }
  }
  return res;
}

struct Edge {
  Edge* next;
  int to;
  Edge () {}
  Edge (Edge* next, int to): next(next), to(to) {}
} *first[N], pool[N << 1], *pis = pool;

inline void add_edge(int u, int v) {
  first[u] = new (pis++) Edge (first[u], v);
  first[v] = new (pis++) Edge (first[v], u);
}

int n, f[N][3];

inline void dfs(int u, int pa) {
  f[u][1] = f[u][2] = 1;
  for (Edge* now = first[u]; now; now = now->next) {
    if (now->to ^ pa) {
      dfs(now->to, u);
      mul(f[u][1], (f[now->to][0] + f[now->to][1]) % mod);
      mul(f[u][2], (2ll * f[now->to][0] + f[now->to][1]) % mod);
    }
  }
  for (Edge* now = first[u]; now; now = now->next) {
    if (now->to ^ pa) {
      add(f[u][0], 1ll * f[now->to][2] * f[u][2] % mod * qpow((2ll * f[now->to][0] + f[now->to][1]) % mod, mod - 2) % mod);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (rg int i = 1; i < n; ++i) {
    int u, v; scanf("%d%d", &u, &v);
    add_edge(u, v);
  }
  dfs(1, 0);
  printf("%d\n", (f[1][0] + f[1][1]) % mod);
  return 0;
}
