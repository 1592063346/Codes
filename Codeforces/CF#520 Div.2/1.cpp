#include<bits/stdc++.h>

using namespace std;

#define rg register

template<typename T> inline bool checkMax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}

const int N = 1e2 + 10;

int n, a[N];

int main() {
  scanf("%d", &n);
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  a[0] = 0, a[n + 1] = 1001;
  int ans = 0, res = 0;
  for (rg int i = 1; i <= n; ++i) {
    if (a[i - 1] + 1 == a[i] && a[i + 1] - 1 == a[i]) {
      checkMax(ans, ++res);
    } else {
      res = 0;
    }
  }
  printf("%d\n", ans);
  return 0;
}
