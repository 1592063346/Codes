#include<bits/stdc++.h>

using namespace std;

const int N = 8e4 + 10, mod = 998244353, G = 3;

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

int n, m, rev[N << 1], a[N], heavy[N], size[N], dfn[N], dfn_cnt, id[N], all;
vector<int> adj[N], poly[N][2];

struct poly_t {
  vector<int> a00, a01, a10, a11;

  poly_t() {}
  poly_t(vector<int> a00, vector<int> a01, vector<int> a10, vector<int> a11): a00(a00), a01(a01), a10(a10), a11(a11) {}
};

void dft(vector<int>& buffer, bool inv = false) {
  int n = buffer.size();
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(buffer[i], buffer[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    int x = qpow(G, !inv ? (mod - 1) / (i << 1) : mod - 1 - (mod - 1) / (i << 1));
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

vector<int> padd(vector<int> x, vector<int> y) {
  int a = max(x.size(), y.size());
  x.resize(a);
  y.resize(a);
  for (int i = 0; i < a; ++i) {
    x[i] = (x[i] + y[i]) % mod;
  }
  return x;
}

vector<int> pmul(vector<int> x, vector<int> y) {
  int a = x.size() + y.size() - 1, len = 0;
  for (; (1 << len) <= a; ++len);
  for (int i = 0; i < (1 << len); ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  x.resize(1 << len);
  y.resize(1 << len);
  dft(x);
  dft(y);
  for (int i = 0; i < (1 << len); ++i) {
    x[i] = mul(x[i], y[i]);
  }
  dft(x, true);
  x.resize(a);
  return x;
}

poly_t pmul(poly_t a, poly_t b) {
  vector<int> a00 = padd(padd(pmul(a.a00, b.a00), pmul(a.a00, b.a10)), pmul(a.a01, b.a00));
  vector<int> a01 = padd(padd(pmul(a.a00, b.a01), pmul(a.a00, b.a11)), pmul(a.a01, b.a01));
  vector<int> a10 = padd(padd(pmul(a.a10, b.a00), pmul(a.a10, b.a10)), pmul(a.a11, b.a00));
  vector<int> a11 = padd(padd(pmul(a.a10, b.a01), pmul(a.a10, b.a11)), pmul(a.a11, b.a01));
  return poly_t(a00, a01, a10, a11);
}

pair<vector<int>, vector<int>> merge(int l, int r) {
  if (l == r) {
    return {padd(poly[id[l]][0], poly[id[l]][1]), poly[id[l]][0]};
  } else {
    int mid = l + r >> 1;
    pair<vector<int>, vector<int>> x = merge(l, mid);
    pair<vector<int>, vector<int>> y = merge(mid + 1, r);
    return {pmul(x.first, y.first), pmul(x.second, y.second)};
  }
}

poly_t solve(int l, int r) {
  if (l == r) {
    return poly_t(poly[id[l]][0], vector<int>(1, 0), vector<int>(1, 0), poly[id[l]][1]);
  } else {
    int mid = l + r >> 1;
    return pmul(solve(l, mid), solve(mid + 1, r));
  }
}

void dfs1(int u, int p) {
  size[u] = 1;
  for (auto v : adj[u]) {
    if (v != p) {
      dfs1(v, u);
      size[u] += size[v];
      if (size[v] > size[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
}

void dfs2(int u, int p, int t) {
  poly[u][0] = vector<int>(1, 1);
  poly[u][1] = vector<int>(2, 0);
  poly[u][1][1] = a[u];
  for (auto v : adj[u]) {
    if (v != p && v != heavy[u]) {
      dfs2(v, u, v);
    }
  }
  all = 0;
  for (auto v : adj[u]) {
    if (v != p && v != heavy[u]) {
      id[++all] = v;
    }
  }
  if (all) {
    pair<vector<int>, vector<int>> result = merge(1, all);
    poly[u][0] = pmul(poly[u][0], result.first);
    poly[u][1] = pmul(poly[u][1], result.second);
  }
  if (heavy[u]) {
    dfs2(heavy[u], u, t);
  }
  if (u == t) {
    all = 0;
    for (int x = u; x; x = heavy[x]) {
      id[++all] = x;
    }
    poly_t final = solve(1, all);
    poly[u][0] = padd(final.a00, final.a01);
    poly[u][1] = padd(final.a10, final.a11);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs1(1, 0);
  dfs2(1, 0, 1);
  int answer = 0;
  if (poly[1][0].size() > m) {
    add(answer, poly[1][0][m]);
  }
  if (poly[1][1].size() > m) {
    add(answer, poly[1][1][m]);
  }
  printf("%d\n", answer);
  return 0;
}
