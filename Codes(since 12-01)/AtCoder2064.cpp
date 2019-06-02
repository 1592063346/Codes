#include<bits/stdc++.h>

using namespace std;

const int N = 567890, mod = 924844033, root = 5;

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

int n, size[N], rev[N], fac[N], ifac[N], inv[N];
vector<int> adj[N];

int binom(int n, int m) {
  return n < 0 || m < 0 || n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m]));
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = mul(mod - mod / i, inv[mod % i]);
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  vector<int> f(n + 1), g(n + 1);
  for (int i = 0; i <= n; ++i) {
    g[i] = ifac[i];
  }
  function<void (int, int)> dfs = [&] (int x, int z) {
    size[x] = 1;
    for (auto y : adj[x]) {
      if (y != z) {
        dfs(y, x);
        ++f[size[y]];
        ++f[n - size[y]];
        size[x] += size[y];
      }
    }
  };
  dfs(1, 0);
  for (int i = 0; i <= n; ++i) {
    f[i] = mul(f[i], fac[i]);
  }
  reverse(f.begin(), f.end());
  f = pmul(f, g);
  for (int i = 1; i <= n; ++i) {
    int answer = mul(n, binom(n, i));
    sub(answer, mul(ifac[i], f[n - i]));
    cout << answer << '\n';
  }
  return 0;
}
