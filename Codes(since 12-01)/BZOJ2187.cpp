#include<bits/stdc++.h>

using namespace std;

void f(long long a, long long b, long long c, long long d, long long& x, long long& y) {
  long long gab = __gcd(a, b);
  long long gcd = __gcd(c, d);
  a /= gab;
  b /= gab;
  c /= gcd;
  d /= gcd;
  if (!a) {
    x = 1;
    y = d / c + 1;
  } else if (a / b + 1 <= (c - 1) / d) {
    x = a / b + 1;
    y = 1;
  } else if (a < b && c <= d) {
    f(d, c, b, a, y, x);
  } else {
    long long part = a / b;
    f(a % b, b, c - d * part, d, x, y);
    x += y * part;
  }
}

int main() {
  long long a, b, c, d;
  while (scanf("%lld%lld%lld%lld", &a, &b, &c, &d) == 4) {
    long long x, y;
    f(a, b, c, d, x, y);
    printf("%lld/%lld\n", x, y);
  }
  return 0;
}
