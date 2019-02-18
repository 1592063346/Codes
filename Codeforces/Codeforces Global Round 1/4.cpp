#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, m, a[N], number[N], f[N][5][9];

int main() {
  scanf("%d%d", &n, &m);
  cmax(m, 3);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    ++number[a[i]];
  }
  int answer = 0, samep = 0;
  for (int i = 1; i <= m; ++i) {
    while (number[i] - 3 >= 6) {
      number[i] -= 3;
      ++samep;
    }
  }
  answer = samep;
  memset(f, 0xc0, sizeof f);
  f[2][0][0] = 0;
  for (int i = 3; i <= m; ++i) {
    for (int j = 0; j <= min(2, number[i]); ++j) {
      for (int k = j; k <= min(4, number[i - 1]); ++k) {
        for (int l = k - j; l + j <= number[i - 2]; ++l) {
          cmax(f[i][j][k], f[i - 1][k - j][l] + j + (number[i - 2] - l - j) / 3);
          cmax(answer, samep + f[i][j][k] + (number[i] - j) / 3 + (number[i - 1] - k) / 3);
        }
      }
    }
  }
  printf("%d\n", answer);
  return 0;
}
