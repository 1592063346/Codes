#include<bits/stdc++.h>

using namespace std;

const int N = 4e2 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, l[N], r[N], h[N], t, number[N][N], f[N][N], g[N][N], answer2[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &l[i], &r[i]);
    r[i] += l[i];
    h[++t] = l[i];
    h[++t] = r[i];
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  for (int i = 1; i <= n; ++i) {
    l[i] = lower_bound(h + 1, h + 1 + t, l[i]) - h;
    r[i] = lower_bound(h + 1, h + 1 + t, r[i]) - h;
  }
  for (int len = 1; len < t; ++len) {
    for (int i = 1; i + len <= t; ++i) {
      int j = i + len;
      number[i][j] = number[i + 1][j];
      for (int k = 1; k <= n; ++k) {
        if (l[k] == i && r[k] <= j) {
          ++number[i][j];
        }
      }
    }
  }
  memset(f, 0xc0, sizeof f);
  memset(g, 0xc0, sizeof g);
  f[0][0] = 0;
  g[t + 1][0] = 0;
  for (int i = 1; i <= t; ++i) {
    for (int j = 0; j <= n; ++j) {
      f[i][j] = f[i - 1][j];
      for (int k = 1; k < i; ++k) {
        cmax(f[i][j], f[k][j] + number[k][i]);
        if (j >= number[k][i]) {
          cmax(f[i][j], f[k][j - number[k][i]]);
        }
      }
    }
  }
  for (int i = t; i >= 1; --i) {
    for (int j = 0; j <= n; ++j) {
      g[i][j] = g[i + 1][j];
      for (int k = t; k > i; --k) {
        cmax(g[i][j], g[k][j] + number[i][k]);
        if (j >= number[i][k]) {
          cmax(g[i][j], g[k][j - number[i][k]]);
        }
      }
    }
  }
  int answer = 0;
  for (int i = 0; i <= n; ++i) {
    cmax(answer, min(i, f[t][i]));
  }
  printf("%d\n", answer);
  for (int i = 1; i <= t; ++i) {
    for (int j = i + 1; j <= t; ++j) {
      int result = 0;
      for (int x = 0; x <= number[1][i]; ++x) {
        for (int y = 0; y <= number[j][t]; ++y) {
          cmax(result, min(x + y + number[i][j], f[i][x] + g[j][y]));
        }
      }
      for (int k = 1; k <= n; ++k) {
        if (l[k] >= i && r[k] <= j) {
          cmax(answer2[k], result);
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    printf("%d\n", answer2[i]);
  }
  return 0;
}
