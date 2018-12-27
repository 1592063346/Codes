#include<bits/stdc++.h>

using namespace std;

#define rg register

typedef long long ll;

int t, a, b, k;

int main() {
  scanf("%d", &t);
  for (rg int i = 1; i <= t; ++i) {
    scanf("%d%d%d", &a, &b, &k);
    ll p = 1ll * a * (k / 2) - 1ll * b * (k / 2) + (k & 1) * a;
    printf("%I64d\n", p);
  }
  return 0;
}
