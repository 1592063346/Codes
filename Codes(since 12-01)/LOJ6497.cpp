#include<bits/stdc++.h>

using namespace std;

const int N = 2e5, mod = 998244353;

int n, p, a[N], fac[N], inv_fac[N], f[2][2][2][2], pow_2[N];

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

int binom(int n, int m) {
  return mul(fac[n], mul(inv_fac[m], inv_fac[n - m]));
}

void binom_init() {
  fac[0] = 1;
  inv_fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  inv_fac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    inv_fac[i] = mul(inv_fac[i + 1], i + 1);
  }
}

int main() {
  scanf("%d%d", &n, &p);
  binom_init();
  pow_2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pow_2[i] = (pow_2[i - 1] << 1) % mod;
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  f[0][0][0][0] = 1;
  for (int i = 0; i < n; ++i) {
    memset(f[i + 1 & 1], 0, sizeof f[i + 1 & 1]);
    for (int opt = 0; opt < 2; ++opt) {
      for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 2; ++k) {
          int g = f[i & 1][opt][j][k];
          if (a[i + 1] != 1) {
            if (!k) {
              add(f[i + 1 & 1][!opt][min(j + 1, 1)][k], mul(g, pow_2[i]));
            } else {
              add(f[i + 1 & 1][opt][j][k], mul(g, pow_2[i - 1]));
              add(f[i + 1 & 1][!opt][min(j + 1, 1)][k], mul(g, pow_2[i - 1]));
            }
          }
          if (a[i + 1] != 0) {
            if (!j) {
              add(f[i + 1 & 1][!opt][j][min(k + 1, 1)], mul(g, pow_2[i]));
            } else {
              add(f[i + 1 & 1][opt][j][k], mul(g, pow_2[i - 1]));
              add(f[i + 1 & 1][!opt][j][min(k + 1, 1)], mul(g, pow_2[i - 1]));
            }
          }
        }
      }
    }
  }
  int answer = 0;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      add(answer, f[n & 1][p][i][j]);
    }
  }
  printf("%d\n", answer);
  return 0;
}
