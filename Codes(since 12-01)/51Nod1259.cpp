#include<bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, f[230][N], g[230][N], s[N], sumg[N];

int main() {
  scanf("%d", &n);
  int m = sqrt(n);
  f[0][0] = 1;
  g[0][0] = 1;
  for (int i = 1; i < m; ++i) {
    memset(s, 0, sizeof s);
    for (int j = 0; j <= n; ++j) {
      add(s[j % i], f[i - 1][j]);
      f[i][j] = s[j % i];
    }
  }
  sumg[0] = 1;
  for (int i = 1; i <= n / m; ++i) {
    for (int j = m; j <= n; ++j) {
      g[i][j] = (g[i][j - i] + g[i - 1][j - m]) % mod;
      add(sumg[j], g[i][j]);
    }
  }
  int answer = 0;
  for (int i = 0; i <= n; ++i) {
    add(answer, mul(f[m - 1][i], sumg[n - i]));
  }
  printf("%d\n", answer);
  return 0;
}
