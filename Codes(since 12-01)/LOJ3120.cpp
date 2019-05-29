#include<bits/stdc++.h>

using namespace std;

const int N = 123456, mod = 998244353, root = 3;

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

int d, n, m, fac[N], ifac[N], inv[N], rev[N << 2];

int binom(int x, int y) {
  return x < 0 || y < 0 || x < y ? 0 : mul(fac[x], mul(ifac[y], ifac[x - y]));
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

int f0(int x) {
  return !x ? 1 : ((n - 2 * m & 1) ? (mod - binom(x - 1, n - 2 * m)) % mod : binom(x - 1, n - 2 * m));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> d >> n >> m;
  fac[0] = ifac[0] = inv[1] = 1;
  for (int i = 1; i <= d; ++i) {
    if (i > 1) {
      inv[i] = mul(mod - mod / i, inv[mod % i]);
    }
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  vector<int> a(d + 1), b(d + 1);
  for (int i = 0; i <= d; ++i) {
    a[i] = mul(mul(f0(d - i), qpow(2, i)), ifac[i]);
    b[i] = (i & 1) ? (mod - ifac[i]) % mod : ifac[i];
  }
  a = pmul(a, b);
  int answer = 0;
  for (int i = 0; i <= d; ++i) {
    a[i] = mul(a[i], fac[i]);
    add(answer, mul(binom(d, i), mul(qpow((2 * i - d + mod) % mod, n), a[i])));
  }
  cout << mul(answer, qpow(mod + 1 >> 1, d)) << '\n'; 
  return 0;
}
