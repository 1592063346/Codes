#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 998244353;

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

int n, m, a[N], fac[N], inv_fac[N], rev[N * 3], father[20][N], dfn[N], depth[N], subn[N], sube[N], s[N], t[N], dfn_cnt;
vector<int> adj[N], nodes[N];

void fac_init() {
  fac[0] = inv_fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  inv_fac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    inv_fac[i] = mul(inv_fac[i + 1], i + 1);
  }
}

void dft(vector<int>& buffer, bool inv = false) {
  int n = buffer.size();
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(buffer[i], buffer[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    int x = qpow(3, !inv ? (mod - 1) / (i << 1) : mod - 1 - (mod - 1) / (i << 1));
    for (int j = 0; j < n; j += i << 1) {
      int y = 1;
      for (int k = 0; k < i; ++k, y = mul(y, x)) {
        int p = buffer[j + k], q = mul(y, buffer[i + j + k]);
        buffer[j + k] = (p + q) % mod;
        buffer[i + j + k] = (p - q + mod) % mod;
      }
    }
  }
  if (inv) {
    int x = qpow(n, mod - 2);
    for (int i = 0; i < n; ++i) {
      buffer[i] = mul(buffer[i], x);
    }
  }
}

vector<int> pmul(vector<int> x, vector<int> y) {
  int s = x.size() + y.size() - 1, len = 0;
  for (; (1 << len) <= s; ++len);
  for (int i = 0; i < (1 << len); ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  assert((1 << len) < N * 3);
  x.resize(1 << len);
  y.resize(1 << len);
  dft(x);
  dft(y);
  for (int i = 0; i < (1 << len); ++i) {
    x[i] = mul(x[i], y[i]);
  }
  dft(x, true);
  x.resize(s);
  return x;
}

void dfs1(int u) {
  dfn[u] = ++dfn_cnt;
  for (int i = 1; (1 << i) <= n; ++i) {
    father[i][u] = father[i - 1][father[i - 1][u]];
  }
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    father[0][v] = u;
    depth[v] = depth[u] + 1;
    dfs1(v);
  }
}

int get_lca(int u, int v) {
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  for (int i = 17; ~i; --i) {
    if (depth[u] - (1 << i) >= depth[v]) {
      u = father[i][u];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 17; ~i; --i) {
    if (father[i][u] != father[i][v]) {
      u = father[i][u];
      v = father[i][v];
    }
  }
  return father[0][u];
}

void dfs2(int u) {
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    dfs2(v);
    subn[u] += subn[v];
    sube[u] += sube[v];
  }
  ++s[subn[u]];
  if (u != 1) {
    ++t[sube[u]];
  }
}

bool cmp(const int& x, const int& y) {
  return dfn[x] < dfn[y];
}

vector<int> solve(int* arr) {
  vector<int> x, y;
  for (int i = 0; i <= n; ++i) {
    x.push_back(mul(arr[i], fac[i]));
    y.push_back(inv_fac[n - i]);
  }
  return pmul(x, y);
}

int main() {
  scanf("%d%d", &n, &m);
  fac_init();
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    nodes[a[i]].push_back(i);
  }
  for (int i = 2; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    adj[x].push_back(i);
  }
  dfs1(1);
  for (int i = 1; i <= n; ++i) {
    if (nodes[i].size()) {
      sort(nodes[i].begin(), nodes[i].end(), cmp);
      for (int j = 0; j < nodes[i].size(); ++j) {
        int u = nodes[i][j];
        ++subn[u];
        ++sube[u];
        if (j + 1 < nodes[i].size()) {
          int v = nodes[i][j + 1], lca = get_lca(u, v);
          --subn[lca];
          --sube[lca];
        }
      }
      int root = get_lca(nodes[i][0], nodes[i].back());
      --sube[root];
      if (root != 1) {
        --subn[father[0][root]];
      }
    }
  }
  dfs2(1);
  vector<int> node = solve(s);
  vector<int> edge = solve(t);
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", mul((node[i + n] - edge[i + n] + mod) % mod, inv_fac[i]));
  }
  return 0;
}
