#include<bits/stdc++.h>

using namespace std;

#define rg register

typedef long long ll;

int n;

int main() {
  scanf("%d", &n);
  ll ans = 0;
  for (rg int i = 2; i <= n; ++i) {
    int u = n / i;
    ans += 1ll * (2 + u) * (u - 2 + 1) >> 1;
  }
  printf("%I64d\n", ans << 2);
  return 0;
}
