#include<bits/stdc++.h>

using namespace std;

long long n, k;

int main() {
  scanf("%I64d%I64d", &n, &k);
  if (n + n < k) {
    return puts("0"), 0;
  }
  long long l = max(1ll, k - n);
  long long r = k >> 1;
  printf("%I64d\n", r - l + 1 - (r * 2 == k));
  return 0;
}
