#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;

int n, k, f[505][N], fac[N], invfac[N];

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
  return n < m ? 0 : mul(fac[n], mul(invfac[m], invfac[n - m]));
}

void binom_init(int n) {
  fac[0] = invfac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  invfac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    invfac[i] = mul(invfac[i + 1], i + 1);
  }
}

int main() {
  scanf("%d%d", &n, &k);
  binom_init(k + n - 1);
  int l = 1, r = n;
  while (l != r) {
    int mid = l + r >> 1;
    if ((long long) mid * (mid + 1) / 2 >= k) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  f[0][0] = 1;
  for (int i = 1; i <= l; ++i) {
    for (int j = i; j <= k; ++j) {
      f[i][j] = (f[i][j - i] + f[i - 1][j - i]) % mod;
      if (j > n) {
        sub(f[i][j], f[i - 1][j - n - 1]);
      }
    }
  }
  int answer = 0;
  for (int i = 0; i <= l; ++i) {
    int result = 0;
    for (int j = 0; j <= k; ++j) {
      add(result, mul(f[i][j], binom(k - j + n - 1, k - j)));
    }
    if (i & 1) {
      sub(answer, result);
    } else {
      add(answer, result);
    }
  }
  printf("%d\n", answer);
  return 0;
}
