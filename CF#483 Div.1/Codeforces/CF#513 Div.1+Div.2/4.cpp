#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, a[N], b[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &a[i], &b[i]);
  }
  sort(a + 1, a + 1 + n);
  sort(b + 1, b + 1 + n);
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += max(a[i], b[i]);
  }
  printf("%I64d\n", ans + n);
  return 0;
}
