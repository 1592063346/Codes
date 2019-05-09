#include<bits/stdc++.h>

using namespace std;

const int N = 345678, mod = 998244353, root = 3;

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

int qpow(int x, int y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

int n, value, rev[N];

struct number_t {
  int foo, bar;

  number_t() {
  }

  number_t(int foo, int bar): foo(foo), bar(bar) {
  }

  number_t operator * (number_t a) {
    return number_t((mul(foo, a.foo) + mul(value, mul(bar, a.bar))) % mod, (mul(foo, a.bar) + mul(bar, a.foo)) % mod);
  }

  number_t power(int y) {
    number_t x = *this, result(1, 0);
    for (; y; y >>= 1, x = x * x) {
      if (y & 1) {
        result = result * x;
      }
    }
    return result;
  }
};

bool exist(int x) {
  return qpow(x, mod - 1 >> 1) == 1;
}

int find(int x) {
  int y = rand();
  while (exist((mul(y, y) - x + mod) % mod)) {
    y = rand();
  }
  value = (mul(y, y) - x + mod) % mod;
  int result = number_t(y, 1).power(mod + 1 >> 1).foo;
  return min(result, (mod - result) % mod);
}

void dft(vector<int>& buffer, bool inv = false) {
  int n = buffer.size();
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(buffer[i], buffer[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    int x = qpow(root, inv ? mod - 1 - (mod - 1) / (i << 1) : (mod - 1) / (i << 1));
    for (int j = 0; j < n; j += i << 1) {
      int y = 1;
      for (int k = 0; k < i; ++k, y = mul(y, x)) {
        int p = buffer[j + k], q = mul(y, buffer[i + j + k]);
        buffer[j + k] = (p + q) % mod;
        buffer[i + j + k] = (p - q + mod) % mod;
      }
    }
  }
  if (inv) {
    int x = qpow(n, mod - 2);
    for (int i = 0; i < n; ++i) {
      buffer[i] = mul(buffer[i], x);
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
  dft(x);
  dft(y);
  for (int i = 0; i < 1 << len; ++i) {
    x[i] = mul(x[i], y[i]);
  }
  dft(x, true);
  x.resize(n);
  return x;
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
    for (int i = 0; i < n; ++i) {
      add(z[i], z[i]);
      sub(z[i], y[i]);
    }
    return z;
  }
}

vector<int> psqrt(vector<int> x) {
  int n = x.size(), m = n + 1 >> 1;
  if (n == 1) {
    return vector<int>(1, find(x[0]));
  } else {
    vector<int> y = psqrt(vector<int>(x.begin(), x.begin() + m)), z = y;
    y = pmul(y, y);
    y.resize(n);
    for (int i = 0; i < n; ++i) {
      add(y[i], x[i]);
    }
    z.resize(n);
    for (int i = 0; i < n; ++i) {
      add(z[i], z[i]);
    }
    y = pmul(y, pinv(z));
    y.resize(n);
    return y;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  vector<int> f(n);
  for (int i = 0; i < n; ++i) {
    cin >> f[i];
  }
  f = psqrt(f);
  for (int i = 0; i < n; ++i) {
    cout << f[i] << " \n"[i + 1 == n];
  }
  return 0;
}
