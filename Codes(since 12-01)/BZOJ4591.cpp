#include<bits/stdc++.h>

using namespace std;

const int mod = 2333;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return x * y % mod;
}

int tt, binom[mod][mod], f[mod][mod];
long long n, m;

int lucas(long long n, long long m) {
  if (n < mod) {
    return n < m ? 0 : binom[n][m];
  } else {
    return mul(lucas(n / mod, m / mod), binom[n % mod][m % mod]);
  }
}

int solve(long long n, long long m) {
  if (m < 0) {
    return 0;
  }
  if (n < mod) {
    return f[n][min(n, m)];
  } else {
    return (mul(solve(n / mod, m / mod - 1), solve(n % mod, mod - 1)) + mul(lucas(n / mod, m / mod), solve(n % mod, m % mod))) % mod;
  }
}

int main() {
  binom[0][0] = 1;
  for (int i = 1; i < mod; ++i) {
    for (int j = 0; j <= i; ++j) {
      binom[i][j] = (binom[i - 1][j] + (j ? binom[i - 1][j - 1] : 0)) % mod;
    }
  }
  for (int i = 0; i < mod; ++i) {
    f[i][0] = 1;
    for (int j = 1; j < mod; ++j) {
      f[i][j] = (f[i][j - 1] + binom[i][j]) % mod;
    }
  }
  scanf("%d", &tt);
  while (tt--) {
    scanf("%lld%lld", &n, &m);
    printf("%d\n", solve(n, m));
  }
  return 0;
}
