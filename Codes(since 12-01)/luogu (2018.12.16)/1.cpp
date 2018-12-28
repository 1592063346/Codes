#include<bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

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

int n;
long long k;

int main() {
  scanf("%d%*lld%lld", &n, &k);
  int inv2 = qpow(2, mod - 2);
  printf("%d\n", mul(n, qpow(inv2, k % (mod - 1))));
  return 0;
}
