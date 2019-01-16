#include<bits/stdc++.h>

using namespace std;

int n, k, mod;

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

int fac(int x) {
  int result = 1;
  for (int i = 1; i <= x; ++i) {
    result = mul(result, i);
  }
  return result;
}

int binom(int n, int m) {
  return mul(fac(n), mul(qpow(fac(m), mod - 2), qpow(fac(n - m), mod - 2)));
}

int solve(int n, int m) {
  return mul(qpow(n, m - 1), qpow(m, n - 1));
}

int main() {
  scanf("%d%d%d", &n, &k, &mod);
  printf("%d\n", mul(solve(k, n - k), binom(n - 1, k - 1)));
  return 0;
}
