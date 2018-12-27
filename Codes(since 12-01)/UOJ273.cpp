#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353;

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

int fac(int n) {
  int result = 1;
  for (int i = 2; i <= n; ++i) {
    result = mul(result, i);
  }
  return result;
}

int main() {
  int n, m = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    m += x;
  }
  printf("%d\n", mul(fac(m), qpow(m + 1 - n, mod - 2)));
  return 0;
}
