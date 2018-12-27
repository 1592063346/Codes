#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353, inv2 = 499122177;

int t;
long long a, b, c, d;

long long mul(long long x, long long y) {
  x %= mod;
  y %= mod;
  return x * y % mod;
}

long long f(long long a, long long b, long long c, long long n) {
  if (!a) {
    return mul(b / c, n + 1);
  } else if (a >= c || b >= c) {
    return ((mul(mul(mul(a / c, n), n + 1), inv2) + mul(b / c, n + 1)) % mod + f(a % c, b % c, c, n)) % mod;
  } else {
    __int128 m = ((__int128) a * n + b) / c;
    return n * m % mod - f(c, c - b - 1, a, m - 1);
  }
}

int main() {
  scanf("%d", &t);
  for (int kase = 1; kase <= t; ++kase) {
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    if (b * c == a * d) {
      puts("-1");
    } else {
      if (b * c < a * d) {
        swap(a, c);
        swap(b, d);
      }
      long long up = (b * c + b * d) / (b * c - a * d);
      printf("%lld\n", ((f(a, a, b, up - 1) - f(c, 0, d, up - 1) + up) % mod + mod) % mod);
    }
  }
  return 0;
}
