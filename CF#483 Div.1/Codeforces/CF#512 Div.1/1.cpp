#include<bits/stdc++.h>

using namespace std;

long long n, m, k;

int main() {
  scanf("%I64d%I64d%I64d", &n, &m, &k);
  if (2 * n * m % k) {
    puts("no");
  } else {
    bool found = false;
    long long x, y = 0, z = 0, w, d = 2 * n * m / k;
    for (long long i = max(1ll, d / max(n, m)); i * i <= d && i <= max(n, m); ++i) {
      if (d % i == 0) {
        long long j = d / i;
        if (i <= n && j <= m) {
          found = true;
          x = i;
          w = j;
          break;
        } else if (i <= m && j <= n) {
          found = true;
          x = j;
          w = i;
          break;
        }
      }
    }
    if (found) {
      printf("yes\n0 0\n%I64d %I64d\n%I64d %I64d\n", x, y, z, w);
    } else {
      puts("no");
    }
  }
  return 0;
}
