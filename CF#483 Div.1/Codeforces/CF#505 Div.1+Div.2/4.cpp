#include<bits/stdc++.h>

using namespace std;

const int N = 710;

int n, a[N], g[N][N];
bool f[N][N][2];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      g[i][j] = __gcd(a[i], a[j]);
    }
  }
  for (int i = 1; i <= n + 1; ++i) {
    for (int j = 0; j < i; ++j) {
      f[i][j][0] = f[i][j][1] = true;
    }
  }
  bool answer = false;
  for (int len = 1; len <= n; ++len) {
    for (int i = 1; i + len - 1 <= n; ++i) {
      int l = i, r = i + len - 1;
      for (int k = l; k <= r; ++k) {
        if (l == 1 && r == n) {
          answer |= f[l][k - 1][1] & f[k + 1][r][0];
        }
        f[l][r][0] |= f[l][k - 1][1] & f[k + 1][r][0] & (g[k][l - 1] > 1);
        f[l][r][1] |= f[l][k - 1][1] & f[k + 1][r][0] & (g[k][r + 1] > 1);
      }
    }
  }
  puts(answer ? "Yes" : "No");
  return 0;
}
