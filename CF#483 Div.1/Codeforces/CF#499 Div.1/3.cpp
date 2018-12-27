#include<bits/stdc++.h>

using namespace std;

const int N = 2e5;

int n, k;

int main() {
  scanf("%d%d", &n, &k);
  int gcd = k;
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    gcd = __gcd(gcd, x);
  }
  printf("%d\n", k / gcd);
  for (int i = 0; i < k; i += gcd) {
    printf("%d%c", i, " \n"[i + gcd >= k]);
  }
  return 0;
}
