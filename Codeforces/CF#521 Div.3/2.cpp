#include<bits/stdc++.h>

using namespace std;

#define rg register

const int N = 1e2 + 10;

int n, a[N];

int main() {
  scanf("%d", &n);
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  int ans = 0;
  for (rg int i = 1, last; i <= n; ++i) {
    if (a[i - 1] == 1 && a[i] == 0 && a[i + 1] == 1) {
      if (last == i - 2) {
        last = 0;
      } else {
        last = i, ++ans;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
