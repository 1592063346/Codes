#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int main() {
  int tt, n, m;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d", &n, &m);
    int p = (long long) (n - 1) * (m - 1) % (mod - 1), v = 2, result = 1;
    for (; p; p >>= 1, v = (long long) v * v % mod) {
      if (p & 1) {
        result = (long long) result * v % mod;
      }
    }
    printf("%d\n", result);
  }
  return 0;
}
