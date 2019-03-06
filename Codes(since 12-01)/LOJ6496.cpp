#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10, mod = 998244353, G = 3;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

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

int n, m, t, a[N], rev[N], degree[N], dfn[N], low[N], dfn_cnt, poly_cnt, f[N][3], g[N][2];
vector<int> pstack, poly[N], graph[N], v_graph[N];

void dft(vector<int>& buffer, int n, int opt) {
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(buffer[i], buffer[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    int x = qpow(G, opt == 1 ? (mod - 1) / (i << 1) : mod - 1 - (mod - 1) / (i << 1));
    for (int j = 0; j < n; j += i << 1) {
      int y = 1;
      for (int k = 0; k < i; ++k, y = mul(y, x)) {
        int p = buffer[j + k], q = mul(y, buffer[i + j + k]);
        buffer[j + k] = (p + q) % mod;
        buffer[i + j + k] = (p - q + mod) % mod;
      }
    }
  }
  if (opt == -1) {
    int inv = qpow(n, mod - 2);
    for (int i = 0; i < n; ++i) {
      buffer[i] = mul(buffer[i], inv);
    }
  }
}

vector<int> pmul(vector<int> a, vector<int> b) {
  int n = a.size(), m = b.size(), len = 0;
  for (; (1 << len) <= n + m - 2; ++len);
  for (int i = 0; i < 1 << len; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  a.resize(1 << len);
  b.resize(1 << len);
  dft(a, 1 << len, 1);
  dft(b, 1 << len, 1);
  for (int i = 0; i < 1 << len; ++i) {
    a[i] = mul(a[i], b[i]);
  }
  dft(a, 1 << len, -1);
  vector<int> result;
  for (int i = 0; i <= n + m - 2; ++i) {
    result.push_back(a[i]);
  }
  return result;
}

vector<int> solve(int l, int r) {
  if (l == r) {
    return poly[l];
  } else {
    int mid = l + r >> 1;
    return pmul(solve(l, mid), solve(mid + 1, r));
  }
}

void tarjan(int u, int p) {
  dfn[u] = low[u] = ++dfn_cnt;
  pstack.push_back(u);
  bool to_p = false;
  for (auto v : graph[u]) {
    if (v != p || to_p) {
      if (!dfn[v]) {
        tarjan(v, u);
        cmin(low[u], low[v]);
        if (low[v] == dfn[u]) {
          v_graph[u].push_back(++t);
          while (1) {
            int x = pstack.back();
            pstack.pop_back();
            v_graph[t].push_back(x);
            if (x == v) {
              break;
            }
          }
        } else if (low[v] > dfn[u]) {
          v_graph[u].push_back(v);
          pstack.pop_back();
        }
      } else {
        cmin(low[u], dfn[v]);
      }
    } else {
      to_p = true;
    }
  }
}

void dfs(int u) {
  for (auto v : v_graph[u]) {
    dfs(v);
  }
  if (u <= n) {
    if (!v_graph[u].size()) {
      for (int i = 0; i < 3; ++i) {
        f[u][i] = a[u] >= i;
      }
    } else {
      poly_cnt = 0;
      for (auto v : v_graph[u]) {
        poly[poly_cnt].clear();
        if (v <= n) {
          poly[poly_cnt].push_back(f[v][1]);
          poly[poly_cnt].push_back(f[v][0]);
        } else {
          poly[poly_cnt].push_back(f[v][2]);
          poly[poly_cnt].push_back(f[v][1]);
          poly[poly_cnt].push_back(f[v][0]);
        }
        ++poly_cnt;
      }
      vector<int> result = solve(0, poly_cnt - 1);
      result.resize(a[u] + 1);
      for (int i = 1; i <= a[u]; ++i) {
        add(result[i], result[i - 1]);
      }
      for (int i = 0; i < 3; ++i) {
        f[u][i] = a[u] >= i ? result[a[u] - i] : 0;
      }
    }
  } else {
    vector<int> nodes;
    for (auto v : v_graph[u]) {
      nodes.push_back(v);
    }
    for (int opt = 0; opt < 2; ++opt) {
      g[0][opt] = 1;
      g[0][!opt] = 0;
      for (int j = 0; j < nodes.size(); ++j) {
        g[j + 1][0] = (mul(g[j][0], f[nodes[j]][1]) + mul(g[j][1], f[nodes[j]][2])) % mod;
        g[j + 1][1] = (mul(g[j][0], f[nodes[j]][0]) + mul(g[j][1], f[nodes[j]][1])) % mod;
      }
      add(f[u][0 + opt], g[nodes.size()][1]);
      add(f[u][1 + opt], g[nodes.size()][0]);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  t = n;
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    ++degree[u];
    ++degree[v];
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    cmin(a[i], degree[i]);
  }
  tarjan(1, 0);
  dfs(1);
  printf("%d\n", f[1][0]);
  return 0;
}
