#include<bits/stdc++.h>

using namespace std;

const int N = 234567, M = 2345, mod = 1e9 + 7;

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

int n, a[N], b[N], dp[M << 1][M << 1], fac[M << 2], ifac[M << 2], inv[M << 2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  fac[0] = ifac[0] = inv[1] = 1;
  for (int i = 1; i < (M << 2); ++i) {
    if (i > 1) {
      inv[i] = mul(mod - mod / i, inv[mod % i]);
    }
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i] >> b[i];
    ++dp[M - a[i]][M - b[i]];
  }
  int limit = 2000;
  for (int i = -limit; i <= limit; ++i) {
    for (int j = -limit; j <= limit; ++j) {
      add(dp[i + 1 + M][j + M], dp[i + M][j + M]);
      add(dp[i + M][j + 1 + M], dp[i + M][j + M]);
    }
  }
  auto binom = [&] (int n, int m) {
    return mul(fac[n], mul(ifac[m], ifac[n - m]));
  };
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    add(answer, dp[a[i] + M][b[i] + M]);
    sub(answer, binom(a[i] + b[i] << 1, a[i] << 1));
  }
  cout << mul(answer, mod + 1 >> 1) << '\n';
  return 0;
}
