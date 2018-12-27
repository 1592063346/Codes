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
  int answer = 0;
  for (int i = 0; i <= k; ++i) {
    if (k - i & 1) {
      sub(answer, mul(binom(k, i), mul(i, qpow(i - 1, n - 1))));
    } else {
      add(answer, mul(binom(k, i), mul(i, qpow(i - 1, n - 1))));
    }
  }
  printf("%d\n", answer);
  return 0;
}
