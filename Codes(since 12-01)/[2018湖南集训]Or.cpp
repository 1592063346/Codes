#include<bits/stdc++.h>

using namespace std;

const int N = 123456, mod = 998244353, root = 3;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
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

int n, k, rev[N], fac[N], ifac[N], inv[N];

int binom(int x, int y) {
  return mul(fac[x], mul(ifac[y], ifac[x - y]));
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
  for (int i = 0; i < (1 << len); ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  x.resize(1 << len);
  y.resize(1 << len);
  dft(x);
  dft(y);
  for (int i = 0; i < (1 << len); ++i) {
    x[i] = mul(x[i], y[i]);
  }
  dft(x, true);
  x.resize(n);
  return x;
}

vector<int> solve(int n) {
  int m = n >> 1;
  if (n == 1) {
    vector<int> x(k + 1);
    for (int i = 1; i <= k; ++i) {
      x[i] = ifac[i];
    }
    return x;
  } else {
    int coef = qpow(2, m);
    vector<int> x = solve(n >> 1), y = x;
    for (int i = 1; i < y.size(); ++i) {
      y[i] = mul(y[i], qpow(coef, i));
    }
    x = pmul(x, y);
    x.resize(k + 1);
    if (n & 1) {
      for (int i = 1; i < x.size(); ++i) {
        x[i] = mul(x[i], qpow(2, i));
      }
      vector<int> z(k + 1);
      for (int i = 1; i <= k; ++i) {
        z[i] = ifac[i];
      }
      x = pmul(x, z);
      x.resize(k + 1);
    }
    return x;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  fac[0] = ifac[0] = fac[1] = ifac[1] = inv[1] = 1;
  for (int i = 2; i <= k; ++i) {
    inv[i] = mul(mod - mod / i, inv[mod % i]);
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  vector<int> result = solve(n);
  int answer = 0;
  for (int i = n; i <= k; ++i) {
    add(answer, mul(binom(k, i), mul(result[i], fac[i])));
  }
  cout << answer << '\n';
  return 0;
}
