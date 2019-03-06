#include<bits/stdc++.h>

using namespace std;

const int N = 25, answer0[] = {0, 1, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6};

int n, mod, f[N][N], fac[N], inv_fac[N];

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
  scanf("%d%d", &n, &mod);
  binom_init();
  f[1][1] = 1;
  f[2][2] = 1;
  for (int i = 3; i <= n; ++i) {
    for (int j = 2; j <= i; ++j) {
      for (int x = 1; x < i; ++x) {
        for (int y = 1; y < j - 1; ++y) {
          add(f[i][j], mul(f[x][y], mul(f[i - x][j], binom(i - 2, x - 1))));
        }
        int sumf = 0;
        for (int y = 1; y <= j; ++y) {
          add(sumf, f[i - x][y]);
        }
        add(f[i][j], mul(f[x][j - 1], mul(sumf, binom(i - 2, x - 1))));
      }
    }
  }
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    add(answer, mul(i, f[n][i]));
  }
  answer = mul(answer, inv_fac[n - 1]);
  printf("%d\n%d\n", answer0[n], answer);
  return 0;
}
