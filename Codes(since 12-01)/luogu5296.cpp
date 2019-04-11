#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int n, k;

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

typedef vector<int> poly_t;

poly_t psub(poly_t x, poly_t y) {
  int n = max(x.size(), y.size());
  x.resize(n);
  y.resize(n);
  for (int i = 0; i < n; ++i) {
    sub(x[i], y[i]);
  }
  return x;
}

poly_t pmul(poly_t x, poly_t y) {
  int n = x.size(), m = y.size();
  poly_t z(n + m - 1);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      add(z[i + j], mul(x[i], y[j]));
    }
  }
  z.resize(k + 1);
  return z;
}

poly_t pinv(poly_t x) {
  int n = x.size(), m = n + 1 >> 1;
  if (n == 1) {
    return poly_t(1, qpow(x[0], mod - 2));
  } else {
    poly_t y = pinv(poly_t(x.begin(), x.begin() + m)), z = y;
    y = pmul(y, y);
    y.resize(n);
    y = pmul(y, x);
    z.resize(n);
    poly_t result(n);
    for (int i = 0; i < n; ++i) {
      result[i] = ((2 * z[i] - y[i]) % mod + mod) % mod;
    }
    return result;
  }
}

int main() {
  scanf("%d%d", &n, &k);
  vector<vector<int>> a(n, vector<int>(n));
  vector<vector<poly_t>> f(n, vector<poly_t>(n, poly_t(k + 1)));
  vector<int> fac(k + 1, 1), ifac(k + 1, 1);
  for (int i = 1; i <= k; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  ifac[k] = qpow(fac[k], mod - 2);
  for (int i = k - 1; i >= 1; --i) {
    ifac[i] = mul(ifac[i + 1], i + 1);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      int w = 1;
      for (int t = 0; t <= k; ++t, w = mul(w, a[i][j])) {
        f[i][j][t] = f[j][i][t] = (mod - mul(w, ifac[t])) % mod;
        add(f[i][i][t], mul(w, ifac[t]));
        add(f[j][j][t], mul(w, ifac[t]));
      }
    }
  }
  poly_t result = poly_t(k + 1, 0);
  result[0] = 1;
  for (int i = 1; i < n; ++i) {
    if (!f[i][i][0]) {
      int p = i;
      for (int j = i + 1; j < n; ++j) {
        if (f[j][i][0]) {
          p = j;
        }
      }
      if (p != i) {
        for (int j = i; j < n; ++j) {
          swap(f[i][j], f[p][j]);
        }
      } else {
        return puts("0"), 0;
      }
      for (auto& x : result) {
        x = (mod - x) % mod;
      }
    }
    for (int j = i + 1; j < n; ++j) {
      poly_t coef = pmul(f[j][i], pinv(f[i][i]));
      for (int l = i; l < n; ++l) {
        f[j][l] = psub(f[j][l], pmul(coef, f[i][l]));
      }
    }
    result = pmul(result, f[i][i]);
  }
  printf("%d\n", mul(result[k], fac[k]));
  return 0;
}
