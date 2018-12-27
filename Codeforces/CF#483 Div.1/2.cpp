#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

int n, q, l, r, a[N], f[N][N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    f[i][i] = a[i];
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j + i - 1 <= n; ++j) {
      f[j][j + i - 1] = f[j][j + i - 2] ^ f[j + 1][j + i - 1];
    }
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j + i - 1 <= n; ++j) {
      f[j][j + i - 1] = max(f[j][j + i - 1], max(f[j][j + i - 2], f[j + 1][j + i - 1]));
    }
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d", &l, &r);
    printf("%d\n", f[l][r]);
  }
  return 0;
}
