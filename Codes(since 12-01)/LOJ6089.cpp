#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 23333333;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, f[330][N], g[330][N], s[N], sumg[N];

int main() {
  scanf("%d", &n);
  int m = min(n, (int) sqrt(n) + 1);
  f[0][0] = 1;
  g[0][0] = 1;
  for (int i = 1; i < m; ++i) {
    memset(s, 0, sizeof s);
    for (int j = 0; j <= n; ++j) {
      add(s[j % i], f[i - 1][j]);
      if (j - (i + 1) * i >= 0) {
        sub(s[j % i], f[i - 1][j - (i + 1) * i]);
      }
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
