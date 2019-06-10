#include<bits/stdc++.h>

using namespace std;

const int N = 4567890, mod = 998244353, root = 3;

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

int inv(int x) {
  if (!x) {
    return 1;
  }
  int y = mod, a = 0, b = 1;
  while (x) {
    int t = y / x;
    y -= t * x;
    swap(x, y);
    a -= t * b;
    swap(a, b);
  }
  if (a < 0) {
    a += mod;
  }
  return a;
}

int n, m, f[N], binv[N], ifac[N], rev[N], value[N], pre[N], suf[N];

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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  int e = 3 * m + 1;
  binv[1] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i <= e; ++i) {
    binv[i] = mul(mod - mod / i, binv[mod % i]);
    ifac[i] = mul(ifac[i - 1], binv[i]);
  }
  for (int i = 0; i <= m; ++i) {
    cin >> f[i];
  }
  vector<int> foo(m + 1), bar(e + 1);
  for (int i = 0; i <= m; ++i) {
    foo[i] = mul(f[i], mul(ifac[i], ifac[m - i]));
    if (m - i & 1) {
      foo[i] = (mod - foo[i]) % mod;
    }
  }
  for (int i = 0; i <= e; ++i) {
    bar[i] = binv[i];
  }
  foo = pmul(foo, bar);
  for (int i = 0, j = 1; i <= e; j = mul(j, ++i)) {
    if (i <= m) {
      foo[i] = f[i];
    } else {
      foo[i] = mul(foo[i], mul(j, ifac[i - m - 1]));
    }
  }
  int last_binom = ifac[m], binom;
  for (int i = 0; i < m; ++i) {
    last_binom = mul(last_binom, n - i);
  }
  for (int i = 0; i <= e; ++i) {
    binom = mul(last_binom, mul(n - i - m, inv(n - i)));
    value[i] = mul(foo[i], (mul(last_binom, last_binom) - mul(binom, binom) + mod) % mod);
    last_binom = binom;
  }
  for (int i = 1; i <= e; ++i) {
    add(value[i], value[i - 1]);
  }
  --n;
  if (n <= e) {
    cout << value[n] << '\n';
  } else {
    pre[0] = n;
    suf[e] = n - e;
    for (int i = 1; i <= e; ++i) {
      pre[i] = mul(pre[i - 1], n - i);
    }
    for (int i = e - 1; ~i; --i) {
      suf[i] = mul(suf[i + 1], n - i);
    }
    int answer = 0;
    for (int i = 0; i <= e; ++i) {
      int x = value[i];
      if (i) {
        x = mul(x, pre[i - 1]);
      }
      if (i != e) {
        x = mul(x, suf[i + 1]);
      }
      x = mul(x, mul(ifac[i], ifac[e - i]));
      if (e - i & 1) {
        x = (mod - x) % mod;
      }
      add(answer, x);
    }
    cout << answer << '\n';
  }
  return 0;
}
