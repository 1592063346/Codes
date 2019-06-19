#include<bits/stdc++.h>

using namespace std;

const int N = 401;

int n, mod, f[N][N], g[N][N], binom[N][N], foo[N * N], bar[N][N];

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int x, int y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> mod;
  foo[0] = binom[0][0] = 1;
  for (int i = 1; i <= n * n; ++i) {
    foo[i] = (foo[i - 1] << 1) % mod;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      binom[i][j] = (binom[i - 1][j] + (!j ? 0 : binom[i - 1][j - 1])) % mod;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      bar[i][j] = qpow(foo[i] - 1, j);
    }
  }
  f[1][1] = 1;
  for (int i = 2; i <= n; ++i) {
    for (int k = 1; k < i; ++k) {
      for (int w = 1; w + k <= i; ++w) {
        int ways = mul(binom[n - i + k][k], mul(foo[k * (k - 1) >> 1], bar[w][k]));
        add(f[i][k], mul(ways, f[i - k][w]));
        add(g[i][k], mul(mul(ways, f[i - k][w]), n - i + k));
        add(g[i][k], mul(ways, g[i - k][w]));
      }
    }
  }
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    add(answer, g[n][i]);
  }
  cout << mul(answer, qpow(n - 1, mod - 2)) << '\n';
  return 0;
}
