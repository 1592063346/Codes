#include<bits/stdc++.h>

using namespace std;

#define rg register

const int N = 1e5 + 10, mod = 998244353;

int n, a[N], f[N][205][2], pre[205][2], suf[205][2];

int main() {
  scanf("%d", &n);
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (rg int i = 1; i <= 200; ++i) {
    f[1][i][0] = (!~a[1] || (i == a[1])) ? 1 : 0;
  }
  for (rg int i = 1; i <= 200; ++i) {
    pre[i][0] = (pre[i - 1][0] + f[1][i][0]) % mod;
    pre[i][1] = (pre[i - 1][1] + f[1][i][1]) % mod;
  }
  for (rg int i = 200; i; --i) {
    suf[i][0] = (suf[i + 1][0] + f[1][i][0]) % mod;
    suf[i][1] = (suf[i + 1][1] + f[1][i][1]) % mod;
  }
  for (rg int i = 2; i <= n; ++i) {
    for (rg int j = 1; j <= 200; ++j) {
      f[i][j][0] = (pre[j - 1][0] + pre[j - 1][1]) % mod;
      f[i][j][1] = (f[i - 1][j][0] + suf[j][1]) % mod;
    }
    if (~a[i]) {
      for (rg int j = 1; j <= 200; ++j) {
        if (j ^ a[i]) {
          f[i][j][0] = f[i][j][1] = 0;
        }
      }
    }
    for (rg int j = 1; j <= 200; ++j) {
      pre[j][0] = (pre[j - 1][0] + f[i][j][0]) % mod;
      pre[j][1] = (pre[j - 1][1] + f[i][j][1]) % mod;
    }
    for (rg int j = 200; j; --j) {
      suf[j][0] = (suf[j + 1][0] + f[i][j][0]) % mod;
      suf[j][1] = (suf[j + 1][1] + f[i][j][1]) % mod;
    }
  }
  printf("%d\n", pre[200][1]);
  return 0;
}
