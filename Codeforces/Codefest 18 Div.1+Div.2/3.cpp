#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n;
char a[N], b[N];

int main() {
  scanf("%d%s%s", &n, a + 1, b + 1);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (a[i] ^ b[i]) {
      ++ans;
      if (i < n && a[i] ^ a[i + 1] && b[i] ^ b[i + 1]) {
        swap(a[i], a[i + 1]);
      } else {
        a[i] = b[i];
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
