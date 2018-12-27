#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10, inf = 0x3f3f3f3f;

int n, a[N], dp[N][N], min_dp[N];

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int up(int x) {
  return (x - 1) / 2 + 1;
}

int main() {
  scanf("%d", &n);
  int k = up(n);
  a[0] = inf;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    min_dp[i] = inf;
    for (int j = 1; j <= n; ++j) {
      dp[i][j] = inf;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (i - 3 > 0) {
      for (int j = 1; j <= up(i - 3); ++j) {
        cmin(min_dp[j], dp[i - 3][j]);
      }
    }
    int left = i == 1 ? 0 : max(0, a[i - 1] - a[i] + 1);
    int right = i == n ? 0 : max(0, a[i + 1] - a[i] + 1);
    for (int j = 1; j <= up(i); ++j) {
      cmin(dp[i][j], min_dp[j - 1] + left + right);
      if (i > 2 && j > 1) {
        cmin(dp[i][j], dp[i - 2][j - 1] + max(0, min(a[i - 2] - 1, a[i - 1]) - a[i] + 1) + right);
      }
    }
  }
  for (int j = 1; j <= up(n); ++j) {
    int answer = inf;
    for (int i = 1; i <= n; ++i) {
      cmin(answer, dp[i][j]);
    }
    printf("%d%c", answer, " \n"[j == up(n)]);
  }
  return 0;
}
