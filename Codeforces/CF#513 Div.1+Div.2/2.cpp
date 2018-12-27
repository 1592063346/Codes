#include<bits/stdc++.h>

using namespace std;

long long n;

inline int f(long long v) {
  int result = 0;
  for (; v; result += v % 10, v /= 10);
  return result;
}

int main() {
  scanf("%I64d", &n);
  long long i = 9;
  for (; i <= n; i = i * 10 + 9);
  i = (i - 9) / 10;
  printf("%d\n", f(i) + f(n - i));
  return 0;
}
