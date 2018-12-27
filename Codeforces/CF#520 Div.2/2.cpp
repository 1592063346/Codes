#include<bits/stdc++.h>

using namespace std;

#define rg register

template<typename T> inline bool checkMin(T& a, const T& b) {
  return a > b ? a = b, true : false;
}

template<typename T> inline bool checkMax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}

int n;

int main() {
  scanf("%d", &n);
  if (n == 1) {
    return puts("1 0"), 0;
  }
  int res = 0, final = 1, ans = 0, minp = 1e9;
  for (rg int j = 2, old_n = n; j <= old_n; ++j) {
    if (n % j == 0) {
      int r = 0;
      for (; n % j == 0; n /= j, ++r);
      checkMax(res, r);
      checkMin(minp, r);
      final *= j;
    }
  }
  int p = 1;
  for (; p < res; p <<= 1, ++ans);
  if (res ^ minp || p ^ res) {
    ++ans;
  }
  printf("%d %d\n", final, ans);
  return 0;
}
