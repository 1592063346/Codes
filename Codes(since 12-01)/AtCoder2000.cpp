#include<bits/stdc++.h>

using namespace std;

const int N = 2345, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, k, fac[N * N], ifac[N * N], inv[N * N], dp[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  if (k == 1) {
    cout << 1 << '\n';
    return 0;
  }
  fac[0] = ifac[0] = inv[1] = 1;
  for (int i = 1; i <= n * k; ++i) {
    if (i > 1) {
      inv[i] = mul(mod - mod / i, inv[mod % i]);
    }
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  auto binom = [&] (int n, int m) {
    return n < 0 || m < 0 || n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m]));
  };
  dp[0][0] = 1;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (i + 1 <= n && i + 1 >= j) {
        add(dp[i + 1][j], dp[i][j]);
      }
      if (j + 1 <= n && i >= j + 1) {
        add(dp[i][j + 1], mul(dp[i][j], mul(n - j, binom(n * k - i - j * (k - 1) - 1, k - 2))));
      }
    }
  }
  cout << dp[n][n] << '\n';
  return 0;
}
