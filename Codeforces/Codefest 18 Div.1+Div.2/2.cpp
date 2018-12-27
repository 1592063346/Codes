#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, s, a[N];

int main() {
  scanf("%d%d", &n, &s);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a + 1, a + 1 + n);
  long long ans = 0;
  int mid = n + 1 >> 1;
  for (int i = 1; i < mid; ++i) {
    if (a[i] > s) {
      ans += a[i] - s;
    }
  }
  for (int i = mid + 1; i <= n; ++i) {
    if (a[i] < s) {
      ans += s - a[i];
    }
  }
  ans += abs(a[mid] - s);
  printf("%I64d\n", ans);
  return 0;
}
