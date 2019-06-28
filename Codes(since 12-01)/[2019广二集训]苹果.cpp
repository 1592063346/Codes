#include<bits/stdc++.h>

using namespace std;

const int N = 123456, mod = 998244353;

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

int n, m, pre[20][N], ways[20], dp[N][2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    pre[1][i] = 1;
  }
  for (int i = 2; i < 20; ++i) {
    for (int j = 1; j <= m; ++j) {
      for (int k = j + j; k <= m; k += j) {
        add(pre[i][j], pre[i - 1][k]);
      }
      add(ways[i], pre[i][j]);
    }
  }
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int op = 0; op < 2; ++op) {
      dp[i][op] = mul(dp[i - 1][op], m);
      for (int j = 2; j < min(i + 1, 20); ++j) {
        add(dp[i][op], mul(dp[i - j][op ^ (j - 1 & 1)], ways[j]));
      }
    }
  }
  cout << ((dp[n][0] - dp[n][1] + mod) % mod) << '\n';
  return 0;
}
