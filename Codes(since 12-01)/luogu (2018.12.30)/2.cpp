#include<bits/stdc++.h>

using namespace std;

const int mod = 19491001;

int fac[mod], invfac[mod];

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = (long long)v * v % mod) {
    if (p & 1) {
      result = (long long)result * v % mod;
    }
  }
  return result;
}

int main() {
  fac[0] = invfac[0] = 1;
  for (int i = 1; i < mod; ++i) {
    fac[i] = (long long)fac[i - 1] * i % mod;
  }
  invfac[mod - 1] = qpow(fac[mod - 1], mod - 2);
  for (int i = mod - 2; i; --i) {
    invfac[i] = (long long)invfac[i + 1] * (i + 1) % mod;
  }
  function<int(int, int)> binom = [&] (int n, int m) {
    assert(n < mod && m < mod);
    return n < m ? 0 : (long long)fac[n] * invfac[m] % mod * invfac[n - m] % mod;
  };
  function<int(long long, long long)> lucas = [&] (long long n, long long m) {
    return n < mod ? binom(n, m) : (long long)binom(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
  };
  int tt;
  long long a, b;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%lld%lld", &a, &b);
    printf("%d\n", lucas(a + b, b));
  }
  return 0;
}
