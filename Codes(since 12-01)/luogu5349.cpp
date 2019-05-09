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

int m, r, inv[N], fac[N], ifac[N], a[N], rev[N];

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
    vector<int> result;
    for (int i = 0; i < n; ++i) {
      result.push_back(((2 * z[i] - y[i]) % mod + mod) % mod);
    }
    return result;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> m >> r;
  ++m;
  fac[0] = ifac[0] = inv[1] = 1;
  for (int i = 1; i < m; ++i) {
    if (i > 1) {
      inv[i] = mul(mod - mod / i, inv[mod % i]);
    }
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  for (int i = 0; i < m; ++i) {
    cin >> a[i];
  }
  int x = qpow((1 - r + mod) % mod, mod - 2);
  vector<int> g(m);
  g[0] = mod - 1;
  for (int i = 1; i < m; ++i) {
    g[i] = mul(x, mul(r, ifac[i]));
  }
  g = pinv(g);
  for (int i = 0; i < m; ++i) {
    g[i] = mul(g[i], (mod - x) % mod);
  }
  int answer = 0;
  for (int i = 0; i < m; ++i) {
    add(answer, mul(a[i], mul(g[i], fac[i])));
  }
  cout << answer << '\n';
  return 0;
}
