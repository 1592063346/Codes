#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 998244353, root = 3;

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

int n, k, a[N], b[N], rev[N];

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
    vector<int> result(n);
    for (int i = 0; i < n; ++i) {
      result[i] = ((2 * z[i] - y[i]) % mod + mod) % mod;
    }
    return result;
  }
}

vector<int> pdiv(vector<int> x, vector<int> y) {
  int n = x.size(), m = y.size();
  if (n < m) {
    return vector<int>();
  }
  reverse(x.begin(), x.end());
  reverse(y.begin(), y.end());
  y.resize(n - m + 1);
  y = pmul(x, pinv(y));
  y.resize(n - m + 1);
  reverse(y.begin(), y.end());
  return y;
}

vector<int> pmod(vector<int> x, vector<int> y) {
  int n = x.size(), m = y.size();
  if (n < m) {
    return x;
  }
  vector<int> z = pmul(y, pdiv(x, y));
  for (int i = 0; i + 1 < m; ++i) {
    z[i] = (x[i] - z[i] + mod) % mod;
  }
  z.resize(m - 1);
  return z;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= k; ++i) {
    scanf("%d", &b[i]);
    b[i] = (b[i] % mod + mod) % mod;
  }
  for (int i = 0; i < k; ++i) {
    scanf("%d", &a[i]);
    a[i] = (a[i] % mod + mod) % mod;
  }
  if (n < k) {
    return a[n];
  }
  vector<int> f(k + 1);
  f[k] = n & 1 ? mod - 1 : 1;
  for (int i = 1; i <= k; ++i) {
    f[k - i] = n & 1 ? b[i] : (mod - b[i]) % mod;
  }
  vector<int> v(2), result(1);
  result[0] = 1;
  v[1] = 1;
  for (; n; n >>= 1, v = pmod(pmul(v, v), f)) {
    if (n & 1) {
      result = pmod(pmul(result, v), f);
    }
  }
  int answer = 0;
  for (int i = 0; i < k; ++i) {
    add(answer, mul(result[i], a[i]));
  }
  printf("%d\n", answer);
  return 0;
}
