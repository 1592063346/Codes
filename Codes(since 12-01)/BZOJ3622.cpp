#include<bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10, mod = 1e9 + 9;

int n, k, fac[N], invfac[N], a[N], b[N], f[N][N];

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

int binom(int n, int m) {
  return mul(fac[n], mul(invfac[m], invfac[n - m]));
}

int main() {
  scanf("%d%d", &n, &k);
  if (n + k & 1) {
    return puts("0"), 0;
  }
  k = n + k >> 1;
  fac[0] = invfac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  invfac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    invfac[i] = mul(invfac[i + 1], i + 1);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &b[i]);
  }
  sort(a + 1, a + 1 + n);
  sort(b + 1, b + 1 + n);
  f[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    int find = lower_bound(b + 1, b + 1 + n, a[i]) - b - 1;
    for (int j = 0; j <= i; ++j) {
      f[i][j] = f[i - 1][j];
      if (j > 0 && find - j + 1 > 0) {
        add(f[i][j], mul(find - j + 1, f[i - 1][j - 1]));
      }
    }
  }
  int answer = 0;
  for (int i = k; i <= n; ++i) {
    if (i - k & 1) {
      sub(answer, mul(binom(i, k), mul(f[n][i], fac[n - i])));
    } else {
      add(answer, mul(binom(i, k), mul(f[n][i], fac[n - i])));
    }
  }
  printf("%d\n", answer);
  return 0;
}
