#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 18;
const long double pi = acos(-1);

int n, k, l, x, y, mod, rev[N];

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int x, long long y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

struct complex_t {
  long double x, y;

  complex_t() {
    x = 0;
    y = 0;
  }

  complex_t(long double x, long double y): x(x), y(y) {
  }

  complex_t operator + (complex_t a) {
    return complex_t(x + a.x, y + a.y);
  }

  complex_t operator - (complex_t a) {
    return complex_t(x - a.x, y - a.y);
  }

  complex_t operator * (complex_t a) {
    return complex_t(x * a.x - y * a.y, x * a.y + y * a.x);
  }
};

void dft(vector<complex_t>& buffer, bool inv = false) {
  int n = buffer.size();
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(buffer[i], buffer[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    complex_t x(cos(pi / i), (inv ? -1 : 1) * sin(pi / i));
    for (int j = 0; j < n; j += i << 1) {
      complex_t y(1, 0);
      for (int k = 0; k < i; ++k, y = y * x) {
        complex_t p = buffer[j + k], q = y * buffer[i + j + k];
        buffer[j + k] = p + q;
        buffer[i + j + k] = p - q;
      }
    }
  }
  if (inv) {
    for (int i = 0; i < n; ++i) {
      buffer[i].x /= n;
    }
  }
}

vector<int> pmul(vector<int> x, vector<int> y) {
  int n = x.size() + y.size() - 1, len = 0;
  for (; (1 << len) < n; ++len);
  int size = 1 << len;
  for (int i = 0; i < size; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  x.resize(size);
  y.resize(size);
  vector<complex_t> a, b, c, d;
  a.resize(size);
  b.resize(size);
  c.resize(size);
  d.resize(size);
  int base = 1 << 15;
  for (int i = 0; i < size; ++i) {
    a[i].x = x[i] >> 15;
    b[i].x = x[i] & base - 1;
    c[i].x = y[i] >> 15;
    d[i].x = y[i] & base - 1;
  }
  dft(a);
  dft(b);
  dft(c);
  dft(d);
  vector<complex_t> e, f, g;
  e.resize(size);
  f.resize(size);
  g.resize(size);
  for (int i = 0; i < 1 << len; ++i) {
    e[i] = a[i] * c[i];
    f[i] = a[i] * d[i] + b[i] * c[i];
    g[i] = b[i] * d[i];
  }
  dft(e, true);
  dft(f, true);
  dft(g, true);
  vector<int> result;
  for (int i = 0; i < n; ++i) {
    long long ee = (long long) (e[i].x + 0.5) * base % mod * base % mod;
    long long ff = (long long) (f[i].x + 0.5) * base % mod;
    long long gg = g[i].x + 0.5;
    result.push_back(((ee + ff + gg) % mod + mod) % mod);
  }
  return result;
}

struct matrix_t {
  int a[3][3];

  matrix_t() {
    memset(a, 0, sizeof a);
  }

  int* operator [] (int x) {
    return a[x];
  }

  matrix_t operator + (matrix_t b) {
    matrix_t result;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        result[i][j] = (a[i][j] + b[i][j]) % mod;
      }
    }
    return result;
  }

  matrix_t operator * (int x) {
    matrix_t result;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        result[i][j] = mul(a[i][j], x);
      }
    }
    return result;
  }

  matrix_t operator * (matrix_t b) {
    matrix_t result;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          add(result[i][j], mul(a[i][k], b[k][j]));
        }
      }
    }
    return result;
  }
};

matrix_t qpow(matrix_t x, long long y) {
  matrix_t result;
  for (int i = 0; i < n; ++i) {
    result[i][i] = 1;
  }
  for (; y; y >>= 1, x = x * x) {
    if (y & 1) {
      result = result * x;
    }
  }
  return result;
}

int find_root(int x) {
  vector<int> factor;
  for (int i = 2; i * i <= x - 2; ++i) {
    if ((x - 1) % i == 0) {
      factor.push_back(i);
      if (i != (x - 1) / i) {
        factor.push_back((x - 1) / i);
      }
    }
  }
  for (int i = 2;; ++i) {
    bool ok = true;
    for (int j = 0; j < factor.size(); ++j) {
      if (qpow(i, factor[j]) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) {
      return i;
    }
  }
}

long long binom2(int x) {
  return (long long) x * (x - 1) >> 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k >> l >> x >> y >> mod;
  --x;
  --y;
  int root = find_root(mod), omega = qpow(root, (mod - 1) / k);
  matrix_t a, e;
  for (int i = 0; i < n; ++i) {
    e[i][i] = 1;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> a[i][j];
    }
  }
  vector<int> foo(k), bar(k << 1);
  for (int i = 0, j = 1; i < k; ++i, j = mul(j, omega)) {
    foo[i] = mul(qpow(a * j + e, l)[x][y], qpow(omega, binom2(i)));
  }
  for (int i = 0; i < (k << 1); ++i) {
    bar[i] = qpow(qpow(omega, binom2(i)), mod - 2);
  }
  reverse(foo.begin(), foo.end());
  foo = pmul(foo, bar);
  int coef = qpow(k, mod - 2);
  for (int i = 0; i < k; ++i) {
    cout << mul(coef, mul(qpow(omega, binom2(i)), foo[k + i - 1])) << '\n';
  }
  return 0;
}
