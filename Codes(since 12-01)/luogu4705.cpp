#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10, mod = 998244353, root = 3;

int n, m, t, rev[N], fac[N], inv_fac[N];
vector<int> tmp;

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

vector<int> pder(vector<int> x) {
  int n = x.size();
  vector<int> y(n - 1);
  for (int i = 0; i + 1 < n; ++i) {
    y[i] = mul(i + 1, x[i + 1]);
  }
  return y;
}

vector<int> pint(vector<int> x) {
  int n = x.size();
  vector<int> y(n + 1), inv(n + 1, 1);
  for (int i = 2; i <= n; ++i) {
    inv[i] = mul(mod - mod / i, inv[mod % i]);
  }
  for (int i = 1; i <= n; ++i) {
    y[i] = mul(x[i - 1], inv[i]);
  }
  return y;
}

vector<int> pln(vector<int> x) {
  int n = x.size();
  vector<int> y = pint(pmul(pder(x), pinv(x)));
  y.resize(n);
  return y;
}

vector<int> solve(int l, int r) {
  if (l == r) {
    vector<int> x(2);
    x[0] = 1;
    x[1] = (mod - tmp[l]) % mod;
    return x;
  } else {
    int mid = l + r >> 1;
    return pmul(solve(l, mid), solve(mid + 1, r));
  }
}

int main() {
  scanf("%d%d", &n, &m);
  vector<int> a(n + 1), b(m + 1);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &b[i]);
  }
  scanf("%d", &t);
  int tt = max(t, max(n, m));
  fac[0] = 1;
  inv_fac[0] = 1;
  for (int i = 1; i <= tt; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  inv_fac[tt] = qpow(fac[tt], mod - 2);
  for (int i = tt - 1; i; --i) {
    inv_fac[i] = mul(inv_fac[i + 1], i + 1);
  }
  a.resize(tt + 1);
  b.resize(tt + 1);
  tmp = a;
  vector<int> aa = solve(1, tt);
  tmp = b;
  vector<int> bb = solve(1, tt);
  aa = pder(pln(aa));
  bb = pder(pln(bb));
  aa.resize(tt + 1);
  bb.resize(tt + 1);
  for (int i = tt; i; --i) {
    aa[i] = (mod - aa[i - 1]) % mod;
  }
  for (int i = tt; i; --i) {
    bb[i] = (mod - bb[i - 1]) % mod;
  }
  aa[0] = n;
  bb[0] = m;
  for (int i = 0; i <= tt; ++i) {
    aa[i] = mul(aa[i], inv_fac[i]);
  }
  for (int i = 0; i <= tt; ++i) {
    bb[i] = mul(bb[i], inv_fac[i]);
  }
  vector<int> result = pmul(aa, bb);
  int inv = qpow((long long) n * m % mod, mod - 2);
  for (int i = 1; i <= t; ++i) {
    printf("%d\n", mul(mul(result[i], fac[i]), inv));
  }
  return 0;
}
