#include<bits/stdc++.h>

using namespace std;

int tt;
long long c1, c2, e1, e2, mod;

void exgcd(long long a, long long b, long long& d, long long& x, long long& y) {
  if (!b) {
    x = 1;
    y = 0;
    d = a;
  } else {
    exgcd(b, a % b, d, y, x);
    y -= x * (a / b);
  }
}

long long mul(long long x, long long y) {
  long long result = 0;
  for (; y; y >>= 1, x = (x + x) % mod) {
    if (y & 1) {
      result = (result + x) % mod;
    }
  }
  return result;
}

long long qpow(long long v, long long p) {
  long long result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%lld%lld%lld%lld%lld", &c1, &c2, &e1, &e2, &mod);
    long long s, t, d;
    exgcd(e1, e2, d, s, t);
    if (s < 0) {
      s = -s;
      long long a, b;
      exgcd(c1, mod, d, a, b);
      c1 = (a % mod + mod) % mod;
    }
    if (t < 0) {
      t = -t;
      long long a, b;
      exgcd(c2, mod, d, a, b);
      c2 = (a % mod + mod) % mod;
    }
    printf("%lld\n", mul(qpow(c1, s), qpow(c2, t)));
  }
  return 0;
} 
