#include<bits/stdc++.h>

using namespace std;

long long a, b, c;

long long f(long long a, long long b, long long c, int n) {
  if (!a) {
    return (b / c) * (n + 1);
  } else if (a >= c || b >= c) {
    return (a / c) * n * (n + 1) / 2 + (b / c) * (n + 1) + f(a % c, b % c, c, n);
  } else {
    return (a * n + b) / c * n - f(c, c - b - 1, a, (a * n + b) / c - 1);
  }
}

int main() {
  scanf("%lld%lld%lld", &a, &b, &c);
  printf("%lld\n", f(b, c - b * (c / b), a, c / b) + c / b + 1);
  return 0;
}
