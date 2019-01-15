#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, a[N], num[N], diff[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    num[i] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    diff[i] = a[i] + 1;
  }
  for (int i = n, maxv = 0; i; --i) {
    --maxv;
    maxv = max(maxv, diff[i]);
    num[i] = max(num[i], maxv);
  }
  for (int i = 1; i <= n; ++i) {
    num[i] = max(num[i], num[i - 1]);
  }
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    answer += num[i] - 1 - a[i];
  }
  printf("%lld\n", answer);
  return 0;
}
