#include<bits/stdc++.h>

using namespace std;

const int N = 1005, mod = 1e9 + 7;

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

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

int tx, ty, mx, my, r, g, k, limit, fac[N * N << 1], invfac[N * N << 1], a[N], ways[N][N];

int binom(int n, int m) {
  if (n < m || n < 0 || m < 0) {
    return 0;
  } else {
    return mul(fac[n], mul(invfac[m], invfac[n - m]));
  }
}

int solve(int times, int tx, int mx) {
  int result = 0;
  for (int i = 0; i <= times; ++i) {
    if (tx - i * (mx + 1) + times - 1 < times - 1) {
      break;
    }
    if (i & 1) {
      sub(result, mul(binom(times, i), binom(tx - i * (mx + 1) + times - 1, times - 1)));
    } else {
      add(result, mul(binom(times, i), binom(tx - i * (mx + 1) + times - 1, times - 1)));
    }
  }
  return result;
}

int solve(int times, int tx, int ty, int mx, int my) {
  int result = 0;
  for (int i = 0; i <= times; ++i) {
    if (times - i & 1) {
      sub(result, mul(binom(times, i), mul(solve(i, tx, mx), solve(i, ty, my))));
    } else {
      add(result, mul(binom(times, i), mul(solve(i, tx, mx), solve(i, ty, my))));
    }
  }
  return result;
}

int solve(int x) {
  int result = 0;
  for (int i = 0; i <= limit; ++i) {
    if (tx - i * g < 0 || ty - i * g < 0) {
      break;
    }
    add(result, mul(ways[x][i], mul(binom(r, x), solve(r - x, tx - i * g, ty - i * g, mx, my))));
  }
  return result;
}

int main() {
  scanf("%d%d%d%d%d%d%d", &tx, &ty, &mx, &my, &r, &g, &k);
  limit = min(tx, ty) / g;
  int up = 2e6;
  fac[0] = invfac[0] = 1;
  for (int i = 1; i <= up; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  invfac[up] = qpow(fac[up], mod - 2);
  for (int i = up - 1; i; --i) {
    invfac[i] = mul(invfac[i + 1], i + 1);
  }
  for (int i = 1; i <= k; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a + 1, a + 1 + k);
  k = unique(a + 1, a + 1 + k) - a - 1;
  ways[0][0] = 1;
  for (int i = 1; i <= limit; ++i) {
    for (int j = 1; j <= k; ++j) {
      for (int k = 0; k + a[j] / g <= limit; ++k) {
        add(ways[i][k + a[j] / g], ways[i - 1][k]);
      }
    }
  }
  int answer = 0;
  for (int i = 0; i <= r && i <= limit; ++i) {
    if (i & 1) {
      sub(answer, solve(i));
    } else {
      add(answer, solve(i));
    }
  }
  printf("%d\n", answer);
  return 0;
}
