#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 998244353, G = 3;

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

int n, size[N], heavy[N], pa[N], poly_a[N << 1], poly_b[N << 1], rev[N << 1], len;
long long x;

void ntt(int* c, int n, int type) {
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(c[i], c[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    int x = qpow(G, type == 1 ? (mod - 1) / (i << 1) : mod - 1 - (mod - 1) / (i << 1));
    for (int j = 0; j < n; j += i << 1) {
      int y = 1;
      for (int k = 0; k < i; ++k, y = mul(y, x)) {
        int p = c[j + k], q = mul(y, c[i + j + k]);
        c[j + k] = (p + q) % mod;
        c[i + j + k] = (p - q + mod) % mod;
      }
    }
  }
  if (type == -1) {
    int inv = qpow(n, mod - 2);
    for (int i = 0; i < n; ++i) {
      c[i] = mul(c[i], inv);
    }
  }
}

vector<int> pmul(vector<int>& a, vector<int>& b) {
  int x = a.size() - 1;
  int y = b.size() - 1;
  for (len = 0; (1 << len) <= x + y; ++len);
  int n = 1 << len;
  for (int i = 0; i < n; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  for (int i = 0; i < n; ++i) {
    poly_a[i] = poly_b[i] = 0;
    if (i <= x) {
      poly_a[i] = a[i];
    }
    if (i <= y) {
      poly_b[i] = b[i];
    }
  }
  ntt(poly_a, n, 1);
  ntt(poly_b, n, 1);
  for (int i = 0; i < n; ++i) {
    poly_a[i] = mul(poly_a[i], poly_b[i]);
  }
  ntt(poly_a, n, -1);
  vector<int> newpoly;
  for (int i = 0; i <= x + y; ++i) {
    newpoly.push_back(poly_a[i]);
  }
  return newpoly;
}

vector<int> padd(vector<int>& a, vector<int>& b) {
  vector<int> newpoly;
  for (int i = 0; i < max(a.size(), b.size()); ++i) {
    newpoly.push_back(((i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0)) % mod);
  }
  return newpoly;
}

vector<int> poly[N], nodes, graph[N];

pair<vector<int>, vector<int>> solve(int l, int r) {
  if (l == r) {
    int u = nodes[l];
    return make_pair(poly[u], poly[u]);
  } else {
    int mid = l + r >> 1;
    pair<vector<int>, vector<int>> pl = solve(l, mid);
    pair<vector<int>, vector<int>> pr = solve(mid + 1, r);
    vector<int> diff = pmul(pl.first, pr.second);
    return make_pair(pmul(pl.first, pr.first), padd(pl.second, diff));
  }
}

void dfs1(int u, int pa) {
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v != pa) {
      ::pa[v] = u;
      dfs1(v, u);
      size[u] += size[v];
      if (size[v] > size[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
}

void dfs2(int u, int t) {
  for (auto v : graph[u]) {
    if (v != pa[u] && v != heavy[u]) {
      dfs2(v, v);
    }
  }
  if (heavy[u]) {
    dfs2(heavy[u], t);
  }
  poly[u] = {0, 1};
  if (u == t) {
    nodes.clear();
    for (int x = u; x; x = heavy[x]) {
      for (auto v : graph[x]) {
        if (v != pa[x] && v != heavy[x]) {
          poly[x] = pmul(poly[x], poly[v]);
        }
      }
      nodes.push_back(x);
    }
    poly[u] = solve(0, nodes.size() - 1).second;
    ++poly[u][0];
  }
}

int main() {
  scanf("%d%I64d", &n, &x);
  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  int px = x % mod, binom = 1, answer = 0;
  for (int i = 1; i <= n; ++i) {
    add(answer, mul(poly[1][i], binom));
    binom = mul(mul(binom, qpow(i, mod - 2)), (px + i) % mod);
  }
  printf("%d\n", answer);
  return 0;
}
