#include<bits/stdc++.h>

using namespace std;

int n;
long long p, q, k;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%I64d%I64d%I64d", &p, &q, &k);
    long long t = __gcd(p, q);
    p /= t;
    q /= t;
    while (1) {
      t = __gcd(q, k);
      if (t == 1) {
        break;
      } else {
        while (q % t == 0) {
          q /= t;
        }
      }
    }
    puts(q == 1 ? "Finite" : "Infinite");
  }
  return 0;
}
