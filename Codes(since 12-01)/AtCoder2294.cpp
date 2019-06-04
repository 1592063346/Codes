#include<bits/stdc++.h>

using namespace std;

const int N = 2345, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int n, m, k, dp[N << 1][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  dp[0][0] = 1;
  int answer = 0;
  for (int i = 1; i <= (n + m - 1) / (k - 1); ++i) {
    for (int j = 0; j <= m; ++j) {
      for (int l = 1; l <= min(j, k - 1); ++l) {
        add(dp[i][j], dp[i - 1][j - l]);
      }
      if (j % (k - 1) == m % (k - 1) && (k - 1) * i - j < n && ((k - 1) * i - j) % (k - 1) == (n - 1) % (k - 1)) {
        add(answer, dp[i][j]);
      }
      add(dp[i][j], dp[i - 1][j]);
    }
  }
  cout << answer << '\n';
  return 0;
}
