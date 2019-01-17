#include<bits/stdc++.h>

using namespace std;

const int N = 5110, mod = 998244353;

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

int n, s, r, c[N][N];

void binom_init(int n) {
  c[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      c[i][j] = (c[i - 1][j] + (!j ? 0 : c[i - 1][j - 1])) % mod;
    }
  }
}

int binom(int n, int m) {
  return n < 0 || m < 0 || n < m ? 0 : c[n][m];
}

int solve(int k, int s, int up) {
  if (!k && !s) {
    return 1;
  }
  int result = 0;
  for (int i = 0; i <= k; ++i, s -= up) {
    if (i & 1) {
      sub(result, mul(binom(s + k - 1, s), binom(k, i)));
    } else {
      add(result, mul(binom(s + k - 1, s), binom(k, i)));
    }
  }
  return result;
}

int main() {
  scanf("%d%d%d", &n, &s, &r);
  if (n == 1) {
    return puts("1"), 0;
  }
  binom_init(n + s);
  int total = 0, win = 0;
  for (int i = r; i <= s; ++i) {
    add(total, binom(s - i + n - 2, s - i));
    for (int j = 0; j < n; ++j) {
      add(win, mul(mul(binom(n - 1, j), solve(n - j - 1, s - (j + 1) * i, i)), qpow(j + 1, mod - 2)));
    }
  }
  printf("%d\n", mul(win, qpow(total, mod - 2)));
  return 0;
}
