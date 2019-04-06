#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10, mod = 998244353, root = 3;

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

int n, y, opt, f[N][2], rev[N];
vector<int> adj[N];

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
  int size = 1 << len;
  for (int i = 0; i < size; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  x.resize(size);
  y.resize(size);
  dft(x);
  dft(y);
  for (int i = 0; i < size; ++i) {
    x[i] = mul(x[i], y[i]);
  }
  dft(x, true);
  return vector<int>(x.begin(), x.begin() + n);
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
    y[i] = mul(inv[i], x[i - 1]);
  }
  return y;
}

vector<int> pln(vector<int> x) {
  int n = x.size();
  vector<int> y = pint(pmul(pder(x), pinv(x)));
  return vector<int>(y.begin(), y.begin() + n);
}

vector<int> pexp(vector<int> x) {
  int n = x.size(), m = n + 1 >> 1;
  if (n == 1) {
    return vector<int>(1, 1);
  } else {
    vector<int> y = pexp(vector<int>(x.begin(), x.begin() + m)), z = y;
    y.resize(n);
    y = pln(y);
    for (int i = 0; i < n; ++i) {
      sub(x[i], y[i]);
    }
    add(x[0], 1);
    x = pmul(x, z);
    return vector<int>(x.begin(), x.begin() + n);
  }
}

int main() {
  scanf("%d%d%d", &n, &y, &opt);
  if (y == 1) {
    printf("%d\n", qpow(qpow(n, n - 2), opt));
  } else if (opt == 0) {
    map<pair<int, int>, bool> edges;
    int answer = n;
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      edges[{u, v}] = edges[{v, u}] = true;
    }
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      if (edges[{u, v}]) {
        --answer;
      }
    }
    printf("%d\n", qpow(y, answer));
  } else if (opt == 1) {
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    int z = qpow(y, mod - 2), coef = mul(qpow(z - 1, mod - 2), n);
    function<void (int, int)> dp = [&] (int u, int p) {
      f[u][0] = f[u][1] = 1;
      for (auto v : adj[u]) {
        if (v != p) {
          dp(v, u);
          int f0 = 0, f1 = 0;
          add(f0, mul(f[u][0], f[v][0]));
          add(f0, mul(f[u][0], f[v][1], coef));
          add(f1, mul(f[u][1], f[v][0]));
          add(f1, mul(f[u][0], f[v][1]));
          add(f1, mul(f[u][1], f[v][1], coef));
          f[u][0] = f0;
          f[u][1] = f1;
        }
      }
    };
    dp(1, 0);
    int answer = mul(qpow(y, n), qpow(z - 1, n - 1), qpow(n, mod - 2), f[1][1]);
    printf("%d\n", answer);
  } else {
    vector<int> g(n + 1);
    int z = qpow(y, mod - 2), coef = mul(n, n, qpow(z - 1, mod - 2)), fac = 1;
    for (int i = 1; i <= n; ++i) {
      fac = mul(fac, i);
      g[i] = mul(coef, qpow(i, i), qpow(fac, mod - 2));
    }
    g = pexp(g);
    int answer = mul(qpow(y, n), qpow(z - 1, n), fac, qpow(qpow(n, 4), mod - 2), g[n]);
    printf("%d\n", answer);
  }
  return 0;
}
