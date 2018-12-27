#include<bits/stdc++.h>

using namespace std;

int t, n, r;

int f(double x, int a, int b, int c, int n) {
  if (!n) {
    return 0;
  } else {
    int g = __gcd(a, __gcd(b, c));
    a /= g;
    b /= g;
    c /= g;
    int k = (a * x + b) / c;
    b -= k * c;
    int m = (a * x + b) / c * n;
    return (long long) k * n * (n + 1) / 2 + (long long) n * m - f(x, a * c, -b * c, a * a * r - b * b, m);
  }
}

int main() {
  scanf("%d", &t);
  for (int kase = 1; kase <= t; ++kase) {
    scanf("%d%d", &n, &r);
    double x = sqrt(r);
    int ceilx = x;
    if (ceilx * ceilx == r) {
      printf("%d\n", ceilx & 1 ? n & 1 ? -1 : 0 : n);
    } else {
      printf("%d\n", n - 2 * f(x, 1, 0, 1, n) + 4 * f(x, 1, 0, 2, n));
    }
  }
  return 0;
}
