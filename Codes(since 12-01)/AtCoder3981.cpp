#include<bits/stdc++.h>

using namespace std;

const int N = 16, mod = 1e9 + 7;

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

int n, m, a[N], size[1 << N], dp[N + 1][1 << N], fac[1 << N + 1], ifac[1 << N + 1], inv[1 << N + 1];

int binom(int n, int m) {
  return n < 0 || m < 0 || n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m]));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cin >> a[i];
  }
  reverse(a, a + m);
  int all = 1 << n;
  fac[0] = ifac[0] = inv[1] = 1;
  for (int i = 1; i <= all; ++i) {
    if (i > 1) {
      inv[i] = mul(mod - mod / i, inv[mod % i]);
    }
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  for (int i = 1; i < all; ++i) {
    size[i] = size[i - (i & -i)] + 1;
  }
  dp[0][0] = 1;
  for (int i = 1; i <= m; ++i) {
    int x = a[i - 1];
    for (int j = 0; j < all; ++j) {
      dp[i][j] = dp[i - 1][j];
      for (int k = 0; k < n; ++k) {
        if (j >> k & 1) {
          add(dp[i][j], mul(dp[i - 1][j ^ (1 << k)], binom(all - x + 1 - j + (1 << k) - 1, (1 << k) - 1)));
        }
      }
    }
  }
  int answer = 0;
  for (int i = 0; i < all; ++i) {
    int result = mul(dp[m][i], fac[all - 1 - i]);
    for (int j = 0; j < n; ++j) {
      if (i >> j & 1) {
        result = mul(result, fac[1 << j]);
      }
    }
    if (size[i] & 1) {
      sub(answer, result);
    } else {
      add(answer, result);
    }
  }
  cout << mul(all, answer) << '\n';
  return 0;
}
