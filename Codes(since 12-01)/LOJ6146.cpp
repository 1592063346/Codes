#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 17, mod = 998244353, root = 3;

int n, m, t, x, rev[N], a[N];

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
        int p = buffer[j + k], q = mul(buffer[i + j + k], y);
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

vector<int> padd(vector<int> x, vector<int> y) {
  int n = x.size();
  for (int i = 0; i < n; ++i) {
    add(x[i], y[i]);
  }
  return x;
}

vector<int> pmul(vector<int> x, vector<int> y) {
  int n = x.size(), m = y.size(), l = 0;
  for (; (1 << l) < n + m - 1; ++l);
  int size = 1 << l;
  for (int i = 0; i < size; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << l - 1);
  }
  x.resize(size);
  y.resize(size);
  dft(x);
  dft(y);
  for (int i = 0; i < size; ++i) {
    x[i] = mul(x[i], y[i]);
  }
  dft(x, true);
  for (int i = n; i < n + m - 1; ++i) {
    add(x[i - n], x[i]);
  }
  x.resize(n);
  return x;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> t >> x;
  for (int i = 0; i < m; ++i) {
    cin >> a[i];
  }
  int l = 0;
  for (; (1 << l) < n; ++l);
  for (int i = 0; i < n; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << l - 1);
  }
  vector<int> result(n);
  int omega = qpow(root, (mod - 1) / x);
  for (int i = 0, j = 1; i < x; ++i, j = mul(j, omega)) {
    vector<int> foo(n);
    for (int k = 0; k < m; ++k) {
      add(foo[a[k]], j);
    }
    add(foo[0], 1);
    dft(foo);
    for (int k = 0; k < n; ++k) {
      foo[k] = qpow(foo[k], t);
    }
    dft(foo, true);
    result = padd(result, foo);
  }
  int y = qpow(x, mod - 2);
  for (int i = 0; i < n; ++i) {
    cout << mul(result[i], y) << " \n"[i + 1 == n];
  }
  return 0;
}
