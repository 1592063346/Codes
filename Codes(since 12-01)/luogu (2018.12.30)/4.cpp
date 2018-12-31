#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10, mod = 998244353, G = 3;

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

int m = 100000, fac[N], invfac[N], poly_a[N], poly_b[N], rev[N], f[N], g[N], powg[N][2];

void ntt(int* c, int n, int type) {
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(c[i], c[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    int x = powg[i][type == 1];
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

void solve(int l, int r) {
  if (l == r) {
    if (l == 0) {
      g[0] = 1;
      f[0] = 0;
    } else {
      g[l] = mul(g[l], fac[l]);
      f[l] = mul(f[l], fac[l]);
      add(f[l], g[l]);
    }
  } else {
    int mid = l + r >> 1;
    solve(l, mid);
    int len = 0;
    for (; (1 << len) <= mid + r - l * 2; ++len);
    int n = 1 << len;
    fill(poly_a, poly_a + n, 0);
    fill(poly_b, poly_b + n, 0);
    for (int i = 0; i < n; ++i) {
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
    }
    for (int i = 1; i <= r - l; ++i) {
      poly_b[i - 1] = invfac[i];
    }
    ntt(poly_b, n, 1);
    for (int i = l; i <= mid; ++i) {
      poly_a[i - l] = mul(g[i], invfac[i]);
    }
    ntt(poly_a, n, 1);
    for (int i = 0; i < n; ++i) {
      poly_a[i] = mul(poly_a[i], poly_b[i]);
    }
    ntt(poly_a, n, -1);
    for (int i = mid + 1; i <= r; ++i) {
      add(g[i], poly_a[i - l - 1]);
    }
    fill(poly_a, poly_a + n, 0);
    for (int i = l; i <= mid; ++i) {
      poly_a[i - l] = mul(f[i], invfac[i]);
    }
    ntt(poly_a, n, 1);
    for (int i = 0; i < n; ++i) {
      poly_a[i] = mul(poly_a[i], poly_b[i]);
    }
    ntt(poly_a, n, -1);
    for (int i = mid + 1; i <= r; ++i) {
      add(f[i], poly_a[i - l - 1]);
    }
    solve(mid + 1, r);
  }
}

int main() {
  for (int i = 1; i <= (m << 1); i <<= 1) {
    powg[i][0] = qpow(G, mod - 1 - (mod - 1) / (i << 1));
    powg[i][1] = qpow(G, (mod - 1) / (i << 1));
  }
  fac[0] = invfac[0] = 1;
  for (int i = 1; i <= m; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  invfac[m] = qpow(fac[m], mod - 2);
  for (int i = m - 1; i; --i) {
    invfac[i] = mul(invfac[i + 1], i + 1);
  }
  solve(0, m);
  int tt, a;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d", &a);
    printf("%d\n", mul(f[a], qpow(g[a], mod - 2)));
  }
  return 0;
}
