#include<bits/stdc++.h>

using namespace std;

const int mod = 65537, M = 6e3 + 10;

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

int s[mod], fac[mod], inv_fac[mod], pow_2[mod], f[M], inv_f, g[M], v[M], result[M], h[M];
long long n, m;

int binom(long long n, long long m) {
  if (n < m) {
    return 0;
  } else if (n < mod) {
    return mul(fac[n], mul(inv_fac[m], inv_fac[n - m]));
  } else {
    return mul(binom(n / mod, m / mod), binom(n % mod, m % mod));
  }
}

void init() {
  pow_2[0] = 1;
  fac[0] = 1;
  inv_fac[0] = 1;
  for (int i = 1; i < mod; ++i) {
    pow_2[i] = (pow_2[i - 1] << 1) % mod;
  }
  for (int i = 1; i < mod; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  inv_fac[mod - 1] = qpow(fac[mod - 1], mod - 2);
  for (int i = mod - 2; i; --i) {
    inv_fac[i] = mul(inv_fac[i + 1], i + 1);
  }
}

void pmul(int* x, int* y) {
  memset(result, 0, sizeof result);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      add(result[i + j], mul(x[i], y[j]));
    }
  }
  for (int i = (m << 1) - 2; i >= m; --i) {
    int p = mul(result[i], inv_f);
    for (int j = 0; j <= m; ++j) {
      sub(result[i - j], mul(f[m - j], p));
    }
  }
  for (int i = 0; i < m; ++i) {
    x[i] = result[i];
  }
}

int solve1(long long n) {
  if (n < 0) {
    return 0;
  }
  h[0] = 1;
  for (int i = 1; i < m; ++i) {
    h[i] = qpow(2, i - 1);
  }
  f[0] = m & 1 ? mod - 1 : 1;
  f[m] = m & 1 ? mod - 1 : 1;
  f[m - 1] = m & 1 ? 2 : mod - 2;
  inv_f = qpow(f[m], mod - 2);
  memset(g, 0, sizeof g);
  memset(v, 0, sizeof v);
  g[0] = 1;
  v[1] = 1;
  for (; n; n >>= 1, pmul(v, v)) {
    if (n & 1) {
      pmul(g, v);
    }
  }
  int answer = 0;
  for (int i = 0; i < m; ++i) {
    add(answer, mul(h[i], g[i]));
  }
  return answer;
}

int solve2(long long n) {
  if (n < 0) {
    return 0;
  }
  long long up = n / m;
  int answer = 0;
  for (int i = 0; i <= up; ++i) {
    if (i & 1) {
      sub(answer, mul(pow_2[(n - i * m) % (mod - 1)], binom(n - i * (m - 1), i)));
    } else {
      add(answer, mul(pow_2[(n - i * m) % (mod - 1)], binom(n - i * (m - 1), i)));
    }
  }
  return answer;
}

int main() {
  init();
  scanf("%lld%lld", &n, &m);
  ++m;
  if (m <= 3000) {
    printf("%d\n", solve1(n + 1));
  } else {
    printf("%d\n", (solve2(n) - solve2(n - m + 1) + mod) % mod);
  }
  return 0;
}
