#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

template<typename T>
int mul(T x) {
  return x;
}

template<typename T, typename... U>
int mul(T x, U... y) {
  return (long long) x * mul(y...) % mod;
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

int n, m, fac[N], inv_fac[N];

int binom(int n, int m) {
  return n < 0 || m < 0 || n < m ? 0 : mul(fac[n], mul(inv_fac[m], inv_fac[n - m]));
}

void binom_init(int n) {
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
  scanf("%d%d%*d%*d", &n, &m);
  binom_init(max(n, m));
  int answer = 0;
  for (int i = 1; i < n; ++i) {
    add(answer, mul(binom(m - 1, i - 1), binom(n - 2, i - 1), fac[i - 1], qpow(m, n - 1 - i), i == n - 1 ? 1 : mul(i + 1, qpow(n, n - i - 2))));
  }
  printf("%d\n", answer);
  return 0;
}
