#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;

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

int n, k, fac[N], invfac[N];

int binom(int n, int m) {
  return mul(fac[n], mul(invfac[m], invfac[n - m]));
}

int stirling(int n, int m) {
  int result = 0;
  for (int i = 0; i <= m; ++i) {
    if (i & 1) {
      sub(result, mul(binom(m, i), qpow(m - i, n)));
    } else {
      add(result, mul(binom(m, i), qpow(m - i, n)));
    }
  }
  return mul(result, invfac[m]);
}

int main() {
  scanf("%d%d", &n, &k);
  fac[0] = invfac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  invfac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    invfac[i] = mul(invfac[i + 1], i + 1);
  }
  int p = (stirling(n, k) + mul(n - 1, stirling(n - 1, k))) % mod;
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    add(answer, mul(x, p));
  }
  printf("%d\n", answer);
  return 0;
}
