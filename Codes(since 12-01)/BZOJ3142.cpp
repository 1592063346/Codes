#include<bits/stdc++.h>

using namespace std;

long long n;
int k, m, mod;

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

int diff(int l, int r) {
  return ((long long) (l + r) * (r - l + 1) >> 1) % mod;
}

int main() {
  scanf("%lld%d%d%d", &n, &k, &m, &mod);
  n %= mod;
  printf("%d\n", (mul(n, qpow(m, k - 1)) - mul(k - 1, mul(diff(1, m), qpow(m, k - 2))) + mod) % mod);
  return 0;
}
