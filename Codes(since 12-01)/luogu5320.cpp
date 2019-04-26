#include<bits/stdc++.h>

using namespace std;

const int N = 567, mod = 998244353;

int add(int x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
  return x;
}

int sub(int x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
  return x;
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

template<int base>
struct my_complex {
  int x, y;

  my_complex() {
  }

  my_complex(int x, int y): x(x), y(y) {
  }

  my_complex operator + (my_complex a) {
    return my_complex(add(x, a.x), add(y, a.y));
  }

  my_complex operator - (my_complex a) {
    return my_complex(sub(x, a.x), sub(y, a.y));
  }

  my_complex operator * (long long a) {
    a %= mod;
    return my_complex(mul(x, a), mul(y, a));
  }

  my_complex operator * (my_complex a) {
    return my_complex(add(mul(x, a.x), mul(base, mul(y, a.y))), add(mul(x, a.y), mul(y, a.x)));
  }

  my_complex inv() {
    int coef = sub(mul(x, x), mul(base, mul(y, y)));
    return my_complex(mul(x, qpow(coef, mod - 2)), mul(y, qpow(sub(0, coef), mod - 2)));
  }

  my_complex operator / (my_complex a) {
    return *this * a.inv();
  }

  my_complex operator += (my_complex a) {
    return *this = *this + a;
  }

  my_complex operator -= (my_complex a) {
    return *this = *this - a;
  }

  my_complex operator *= (long long a) {
    return *this = *this * a;
  }

  my_complex operator *= (my_complex a) {
    return *this = *this * a;
  }

  my_complex operator /= (my_complex a) {
    return *this = *this / a;
  }

  my_complex power(long long y) {
    my_complex x = *this, result(1, 0);
    for (; y; y >>= 1, x *= x) {
      if (y & 1) {
        result *= x;
      }
    }
    return result;
  }
};

int tt, m, fac[N], stirling[N][N], binom[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  fac[0] = stirling[0][0] = binom[0][0] = 1;
  for (int i = 1; i <= 501; ++i) {
    fac[i] = mul(fac[i - 1], i);
    binom[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      binom[i][j] = add(binom[i - 1][j], binom[i - 1][j - 1]);
      stirling[i][j] = add(stirling[i - 1][j - 1], mul(stirling[i - 1][j], i - 1));
    }
  }
  cin >> tt >> m;
  my_complex<5> c21, q21, c22, q22;
  my_complex<3> c31, q31, c32, q32;
  if (m == 2) {
    c21 = my_complex<5>(0, qpow(5, mod - 2));
    c22 = my_complex<5>(0, mod - qpow(5, mod - 2));
    q21 = my_complex<5>(mod + 1 >> 1, mod + 1 >> 1);
    q22 = my_complex<5>(mod + 1 >> 1, mod - (mod + 1 >> 1));
  } else {
    c31 = my_complex<3>(mod + 1 >> 1, qpow(6, mod - 2));
    c32 = my_complex<3>(mod + 1 >> 1, mod - qpow(6, mod - 2));
    q31 = my_complex<3>(2, 1);
    q32 = my_complex<3>(2, mod - 1);
  }
  while (tt--) {
    long long l, r;
    int k;
    cin >> l >> r >> k;
    long long len = r - l + 1;
    if (m == 2) {
      ++l;
      ++r;
    } else {
      ++l;
      l >>= 1;
      r >>= 1;
    }
    auto solve = [&] (long long n) {
      if (m == 2) {
        my_complex<5> result(0, 0);
        for (int j = 0; j <= k; ++j) {
          int coef = k - j & 1 ? (mod - stirling[k][j]) % mod : stirling[k][j];
          for (int d = 0; d <= j; ++d) {
            my_complex<5> coefp = c21.power(d) * c22.power(j - d) * binom[j][d];
            my_complex<5> a1 = q21.power(d) * q22.power(j - d);
            my_complex<5> q = a1;
            my_complex<5> s;
            if (q.x == 1 && q.y == 0) {
              s = q * n;
            } else {
              s = (a1 - a1 * q.power(n)) / (my_complex<5>(1, 0) - q);
            }
            result += s * coefp * coef;
          }
        }
        return mul(result.x, qpow(fac[k], mod - 2));
      } else {
        my_complex<3> result(0, 0);
        for (int j = 0; j <= k; ++j) {
          int coef = k - j & 1 ? (mod - stirling[k][j]) % mod : stirling[k][j];
          for (int d = 0; d <= j; ++d) {
            my_complex<3> coefp = c31.power(d) * c32.power(j - d) * binom[j][d];
            my_complex<3> a1 = q31.power(d) * q32.power(j - d);
            my_complex<3> q = a1;
            my_complex<3> s;
            if (q.x == 1 && q.y == 0) {
              s = q * n;
            } else {
              s = (a1 - a1 * q.power(n)) / (my_complex<3>(1, 0) - q);
            }
            result += s * coefp * coef;
          }
        }
        return mul(result.x, qpow(fac[k], mod - 2));
      }
    };
    cout << mul(sub(solve(r), solve(l - 1)), qpow(len % mod, mod - 2)) << '\n';
  }
  return 0;
}
