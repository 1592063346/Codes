#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 11, mod = 998244353, G = 3;

int n, p, m, len, rev[N], powg[N][2], f[N][50], g[N][50], a[50][N], b[N];

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y, int md) {
  return (long long) x * y % md;
}

int qpow(int v, int p, int md) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v, md)) {
    if (p & 1) {
      result = mul(result, v, md);
    }
  }
  return result;
}

void ntt(int n, int* c, int type) {
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(c[i], c[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    int x = powg[i][type == 1];
    for (int j = 0; j < n; j += i << 1) {
      int y = 1;
      for (int k = 0; k < i; ++k, y = mul(y, x, mod)) {
        int p = c[j + k], q = mul(y, c[i + j + k], mod);
        c[j + k] = (p + q) % mod;
        c[i + j + k] = (p - q + mod) % mod;
      }
    }
  }
  if (type == -1) {
    int inv = qpow(n, mod - 2, mod);
    for (int i = 0; i < n; ++i) {
      c[i] = mul(c[i], inv, mod);
    }
  }
}

void qpow(int k, int n) {
  if (k == 1) {
    for (int i = 0; i < 10; ++i) {
      ++f[i][i % p];
    }
  } else {
    qpow(k >> 1, n);
    for (int i = 0; i <= m; ++i) {
      for (int j = 0; j < p; ++j) {
        g[i][j] = 0;
      }
    }
    for (int i = 0; i < p; ++i) {
      memset(a[i], 0, sizeof a[i]);
      for (int j = 0; j <= m; ++j) {
        a[i][j] = f[j][i];
      }
      ntt(n, a[i], 1);
    }
    for (int i = 0; i < p; ++i) {
      for (int j = 0; j < p; ++j) {
        int go = (mul(i, qpow(10, k >> 1, p), p) + j) % p;
        for (int t = 0; t < n; ++t) {
          b[t] = mul(a[i][t], a[j][t], mod);
        }
        ntt(n, b, -1);
        for (int t = 0; t <= m; ++t) {
          add(g[t][go], b[t]);
        }
      }
    }
    for (int i = 0; i <= m; ++i) {
      for (int j = 0; j < p; ++j) {
        f[i][j] = g[i][j];
      }
    }
    if (k & 1) {
      for (int i = 0; i <= m; ++i) {
        for (int j = 0; j < p; ++j) {
          g[i][j] = 0;
        }
      }
      for (int i = 0; i < 10; ++i) {
        for (int j = 0; j + i <= m; ++j) {
          for (int t = 0; t < p; ++t) {
            add(g[j + i][(t * 10 + i) % p], f[j][t]);
          }
        }
      }
      for (int i = 0; i <= m; ++i) {
        for (int j = 0; j < p; ++j) {
          f[i][j] = g[i][j];
        }
      }
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &p, &m);
  for (; (1 << len) <= (m << 1); ++len);
  int length = 1 << len;
  for (int i = 1; i < length; i <<= 1) {
    powg[i][1] = qpow(G, (mod - 1) / (i << 1), mod);
    powg[i][0] = qpow(G, mod - 1 - (mod - 1) / (i << 1), mod);
  }
  for (int i = 0; i < length; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  qpow(n, length);
  for (int i = 0; i <= m; ++i) {
    if (i) {
      add(f[i][0], f[i - 1][0]);
    }
    printf("%d%c", f[i][0], " \n"[i == m]);
  }
  return 0;
}
