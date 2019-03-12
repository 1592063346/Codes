#include<bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10, mod = 998244353;

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

int n, k, m, x, y, q, f[N][N], s[N][N], sum_f[N], pow_q[N], inv_pow_q[N], h[N], a[N], mod_f[N], inv_f, g[N], v[N], result[N];

int sum_dp(int x, int y);
int dp(int x, int y);

int sum_dp(int x, int y) {
  if (!y) {
    return 1;
  }
  if (x * y > k) {
    return 0;
  }
  if (~s[x][y]) {
    return s[x][y];
  }
  s[x][y] = 0;
  for (int i = x; i * y <= k; ++i) {
    add(s[x][y], mul(dp(i, y), pow_q[i * y]));
  }
  return s[x][y];
}

int dp(int x, int y) {
  if (!y) {
    return 1;
  }
  if (x * y > k) {
    return 0;
  }
  if (~f[x][y]) {
    return f[x][y];
  }
  f[x][y] = 0;
  for (int p = 1; p <= y; ++p) {
    int p1 = !(p - 1) ? 1 : mul(sum_dp(x + 1, p - 1), inv_pow_q[(p - 1) * x]);
    int p2 = !(y - p) ? 1 : mul(sum_dp(x, y - p), inv_pow_q[(y - p) * x]);
    add(f[x][y], mul((1 - q + mod) % mod, mul(p1, p2)));
  }
  return f[x][y];
}

void pmul(int* x, int* y) {
  memset(result, 0, sizeof result);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      add(result[i + j], mul(x[i], y[j]));
    }
  }
  for (int i = (m << 1) - 2; i >= m; --i) {
    int p = mul(result[i], inv_f);
    for (int j = 0; j <= m; ++j) {
      sub(result[i - j], mul(mod_f[m - j], p));
    }
  }
  for (int i = 0; i < m; ++i) {
    x[i] = result[i];
  }
}

int solve() {
  memset(f, -1, sizeof f);
  memset(s, -1, sizeof s);
  h[0] = 1;
  a[1] = (1 - q + mod) % mod;
  for (int i = 1; i <= k; ++i) {
    h[i] = sum_dp(1, i);
    a[i + 1] = mul(h[i], (1 - q + mod) % mod);
    for (int j = 1; j <= i; ++j) {
      add(h[i], mul(a[j], h[i - j]));
    }
  }
  m = k + 1;
  if (n < m) {
    return h[n];
  } else {
    int p = n - m;
    for (int i = m; i < m << 1; ++i) {
      h[i] = 0;
      for (int j = 1; j <= m; ++j) {
        add(h[i], mul(a[j], h[i - j]));
      }
    }
    copy(h + m, h + (m << 1), h);
    for (int i = 1; i <= m; ++i) {
      mod_f[m - i] = m & 1 ? a[i] : (mod - a[i]) % mod;
    }
    mod_f[m] = m & 1 ? mod - 1 : 1;
    inv_f = qpow(mod_f[m], mod - 2);
    memset(g, 0, sizeof g);
    memset(v, 0, sizeof v);
    g[0] = 1;
    v[1] = 1;
    for (; p; p >>= 1, pmul(v, v)) {
      if (p & 1) {
        pmul(g, v);
      }
    }
    int answer = 0;
    for (int i = 0; i < m; ++i) {
      add(answer, mul(g[i], h[i]));
    }
    return answer;
  }
}

int main() {
  scanf("%d%d%d%d", &n, &k, &x, &y);
  q = mul(x, qpow(y, mod - 2));
  pow_q[0] = 1;
  inv_pow_q[0] = 1;
  for (int i = 1, inv = qpow(q, mod - 2); i <= k; ++i) {
    pow_q[i] = mul(pow_q[i - 1], q);
    inv_pow_q[i] = mul(inv_pow_q[i - 1], inv);
  }
  int answer = solve();
  --k;
  sub(answer, solve());
  printf("%d\n", answer);
  return 0;
}
