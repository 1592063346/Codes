#include<bits/stdc++.h>

using namespace std;

const int N = 1234567, sqrtN = 1000, mod = 998244353;

int tt, n, k, q, sq, fac[N], ifac[N], sp[5][sqrtN], qx[5], qy[5], pow_value[11][N], up[N];
vector<int> primes, poly[sqrtN];

class my_array {
 public:
  int a[sqrtN + 10 << 1];

  int& operator [] (int x) {
    return x <= sq ? a[x] : a[sq + n / x];
  }
};

my_array f[5];

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

int binom(int n, int m) {
  return n < 0 || m < 0 || n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m]));
}

void sieve(int n) {
  primes.clear();
  vector<bool> is_prime(n + 1, true);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      int now = primes.size();
      for (int j = 0; j < q; ++j) {
        int x = (pow_value[qx[j]][i] - pow_value[qx[j]][i - 1] + mod) % mod;
        sp[j][now] = (sp[j][now - 1] + x) % mod;
      }
    }
    for (auto x : primes) {
      if (i * x > n) {
        break;
      }
      is_prime[i * x] = false;
      if (i % x == 0) {
        break;
      }
    }
  }
}

void min_25_sieve() {
  vector<int> values;
  for (int i = 1; i <= n; i = n / (n / i) + 1) {
    values.push_back(n / i);
  }
  for (auto x : values) {
    for (int i = 0; i < q; ++i) {
      f[i][x] = pow_value[qx[i]][x] - 1;
    }
  }
  for (auto p : primes) {
    for (auto x : values) {
      if (x < p * p) {
        break;
      }
      int y = x / p;
      for (int i = 0; i < q; ++i) {
        int z = (pow_value[qx[i]][p] - pow_value[qx[i]][p - 1] + mod) % mod;
        sub(f[i][x], mul(f[i][y] - f[i][p - 1] + mod, z));
      }
    }
  }
}

int solve(int n, int x) {
  if (n <= 1 || (x <= primes.size() && primes[x - 1] > n)) {
    return 0;
  }
  int result = 0;
  for (int i = 0; i < q; ++i) {
    add(result, mul(f[i][n] - sp[i][x - 1] + mod, qy[i]));
  }
  for (int i = x; i <= primes.size(); ++i) {
    int p = primes[i - 1], y = p;
    if (y * p > n) {
      break;
    }
    for (int j = 1; y * p <= n; ++j, y *= p) {
      add(result, mul(poly[p][j], solve(n / y, i + 1)));
      add(result, poly[p][j + 1]);
    }
  }
  return result;
}

vector<int> pmul(vector<int> x, vector<int> y) {
  vector<int> result(x.size());
  for (int i = 0; i < x.size(); ++i) {
    for (int j = 0; i + j < x.size(); ++j) {
      add(result[i + j], mul(x[i], y[j]));
    }
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  ifac[N - 1] = qpow(fac[N - 1], mod - 2);
  for (int i = N - 2; i; --i) {
    ifac[i] = mul(ifac[i + 1], i + 1);
  }
  for (int x = 0; x <= 9; ++x) {
    for (int i = 1; i < N; ++i) {
      pow_value[x][i] = (pow_value[x][i - 1] + qpow(i, x)) % mod;
    }
  }
  cin >> tt;
  while (tt--) {
    cin >> n >> k >> q;
    for (int i = 0; i < q; ++i) {
      cin >> qx[i] >> qy[i];
    }
    sq = sqrt(n);
    sieve(sq);
    for (auto x : primes) {
      up[x] = 0;
      int y = 1;
      while (y * x <= n) {
        y *= x;
        ++up[x];
      }
      poly[x] = vector<int>(up[x] + 1, 0);
      poly[x][0] = 1;
      for (int i = 0; i < q; ++i) {
        vector<int> t(up[x] + 1);
        for (int j = 0, r = 1; j <= up[x]; ++j, r = mul(r, x)) {
          t[j] = mul(binom(j + qy[i] - 1, j), qpow(r, qx[i]));
        }
        poly[x] = pmul(poly[x], t);
      }
    }
    min_25_sieve();
    cout << (solve(n, 1) + 1) % mod << '\n';
  }
  return 0;
}
