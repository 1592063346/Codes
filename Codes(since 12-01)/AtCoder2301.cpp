#include<bits/stdc++.h>

using namespace std;

const int N = 2345, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int n, k, dp[N][N][2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  dp[n + 1][0][0] = 1;
  for (int i = n + 1; i > 1; --i) {
    for (int j = n; ~j; --j) {
      add(dp[i][j][0], dp[i][j + 1][0]);
      for (int k = 0; k < 2; ++k) {
        add(dp[i - 1][j][0], dp[i][j][k]);
        add(dp[i - 1][j + 1][1], dp[i][j][k]);
      }
    }
  }
  int answer = dp[1][n - k][0];
  for (int i = 1; i <= n - k - 1; ++i) {
    answer = (answer << 1) % mod;
  }
  cout << answer << '\n';
  return 0;
}
