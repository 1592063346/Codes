#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 19;
const long double pi = acos(-1);

int n, mod, inv[N], rev[N];

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

template<typename T>
int mul(T x) {
  return x;
}

template<typename T, typename... U>
int mul(T x, U... y) {
  return (long long) x * mul(y...) % mod;
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

struct complex_t {
  long double x, y;

  complex_t() {
    x = 0;
    y = 0;
  }
  complex_t(long double x, long double y): x(x), y(y) {}

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
  for (int i = 0; i < 1 << len; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  x.resize(1 << len);
  y.resize(1 << len);
  vector<complex_t> a, b, c, d;
  a.resize(1 << len);
  b.resize(1 << len);
  c.resize(1 << len);
  d.resize(1 << len);
  int base = 1 << 15;
  for (int i = 0; i < 1 << len; ++i) {
    a[i].x = x[i] >> 15;
    b[i].x = x[i] & (base - 1);
    c[i].x = y[i] >> 15;
    d[i].x = y[i] & (base - 1);
  }
  dft(a);
  dft(b);
  dft(c);
  dft(d);
  vector<complex_t> e, f, g;
  e.resize(1 << len);
  f.resize(1 << len);
  g.resize(1 << len);
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

vector<int> pinv(vector<int> x) {
  int n = x.size(), m = n + 1 >> 1;
  if (n == 1) {
    return vector<int>(1, qpow(x[0], mod - 2));
  } else {
    vector<int> y = pinv(vector<int>(x.begin(), x.begin() + m)), z = y;
    y = pmul(y, y);
    y.resize(n);
    y = pmul(y, x);
    z.resize(n);
    vector<int> result;
    for (int i = 0; i < n; ++i) {
      result.push_back(((2 * z[i] - y[i]) % mod + mod) % mod);
    }
    return result;
  }
}

vector<int> pder(vector<int> x) {
  int n = x.size();
  vector<int> result(n - 1);
  for (int i = 0; i + 1 < n; ++i) {
    result[i] = mul(i + 1, x[i + 1]);
  }
  return result;
}

vector<int> pint(vector<int> x) {
  int n = x.size();
  vector<int> result(n + 1);
  for (int i = 0; i < n; ++i) {
    result[i + 1] = mul(x[i], inv[i + 1]);
  }
  return result;
}

vector<int> pln(vector<int> x) {
  return pint(pmul(pder(x), pinv(x)));
}

int main() {
  scanf("%d%d", &n, &mod);
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = mul(mod - mod / i, inv[mod % i]);
  }
  vector<int> f(n + 1, 1), answer;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &f[i]);
  }
  f = pln(f);
  for (int i = 1; i <= n; ++i) {
    if (f[i]) {
      answer.push_back(i);
    }
    for (int j = i + i; j <= n; j += i) {
      sub(f[j], mul(f[i], i, inv[j]));
    }
  }
  printf("%d\n", answer.size());
  for (int i = 0; i < answer.size(); ++i) {
    printf("%d%c", answer[i], " \n"[i + 1 == answer.size()]);
  }
  return 0;
}
