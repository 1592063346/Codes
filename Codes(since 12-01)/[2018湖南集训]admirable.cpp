#include<bits/stdc++.h>

using namespace std;

const int N = 345678, mod = 1e9 + 9;
const long double pi = acos(-1);

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

int n, k, answer, rev[N], fac[N], ifac[N], inv[N], size[N], value[N];
vector<int> adj[N];

struct complex_t {
  long double x, y;

  complex_t() {
    x = 0;
    y = 0;
  }
  complex_t(long double x, long double y): x(x), y(y) {}

  complex_t operator + (complex_t a) {
    return complex_t(x + a.x, y + a.y);
  }

  complex_t operator - (complex_t a) {
    return complex_t(x - a.x, y - a.y);
  }

  complex_t operator * (complex_t a) {
    return complex_t(x * a.x - y * a.y, x * a.y + y * a.x);
  }
};

void dft(vector<complex_t>& buffer, bool inv = false) {
  int n = buffer.size();
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(buffer[i], buffer[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    complex_t x(cos(pi / i), (inv ? -1 : 1) * sin(pi / i));
    for (int j = 0; j < n; j += i << 1) {
      complex_t y(1, 0);
      for (int k = 0; k < i; ++k, y = y * x) {
        complex_t p = buffer[j + k], q = y * buffer[i + j + k];
        buffer[j + k] = p + q;
        buffer[i + j + k] = p - q;
      }
    }
  }
  if (inv) {
    for (int i = 0; i < n; ++i) {
      buffer[i].x /= n;
    }
  }
}

vector<int> padd(vector<int> x, vector<int> y) {
  for (int i = 0; i < x.size(); ++i) {
    add(x[i], y[i]);
  }
  return x;
}

vector<int> pmul(vector<int> x, vector<int> y) {
  int n = x.size() + y.size() - 1, len = 0;
  for (; (1 << len) < n; ++len);
  for (int i = 0; i < 1 << len; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  x.resize(1 << len);
  y.resize(1 << len);
  vector<complex_t> a, b, c, d;
  a.resize(1 << len);
  b.resize(1 << len);
  c.resize(1 << len);
  d.resize(1 << len);
  int base = 1 << 15;
  for (int i = 0; i < 1 << len; ++i) {
    a[i].x = x[i] >> 15;
    b[i].x = x[i] & base - 1;
    c[i].x = y[i] >> 15;
    d[i].x = y[i] & base - 1;
  }
  dft(a);
  dft(b);
  dft(c);
  dft(d);
  vector<complex_t> e, f, g;
  e.resize(1 << len);
  f.resize(1 << len);
  g.resize(1 << len);
  for (int i = 0; i < 1 << len; ++i) {
    e[i] = a[i] * c[i];
    f[i] = a[i] * d[i] + b[i] * c[i];
    g[i] = b[i] * d[i];
  }
  dft(e, true);
  dft(f, true);
  dft(g, true);
  vector<int> result;
  for (int i = 0; i < n; ++i) {
    long long ee = (long long) (e[i].x + 0.5) * base % mod * base % mod;
    long long ff = (long long) (f[i].x + 0.5) * base % mod;
    long long gg = g[i].x + 0.5;
    result.push_back(((ee + ff + gg) % mod + mod) % mod);
  }
  return result;
}

int binom(int x, int y) {
  return mul(fac[x], mul(ifac[y], ifac[x - y]));
}

vector<int> solve(int l, int r, vector<int>& sub) {
  if (l == r) {
    vector<int> x(2);
    x[0] = 1;
    x[1] = sub[l];
    return x;
  } else {
    int mid = l + r >> 1;
    return pmul(solve(l, mid, sub), solve(mid + 1, r, sub));
  }
}

void dfs(int x, int f) {
  size[x] = 1;
  vector<int> foo, bar;
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
      size[x] += size[y];
      add(answer, mul(value[y], value[x]));
      add(value[x], value[y]);
      foo.push_back(size[y]);
      bar.push_back(value[y]);
    }
  }
  if (!foo.size()) {
    add(value[x], 1);
  } else {
    vector<int> result = solve(0, foo.size() - 1, foo);
    for (int i = 0; i < min(k + 1, (int) result.size()); ++i) {
      add(value[x], mul(result[i], mul(binom(k, i), fac[i])));
    }
    for (int i = result.size() - 1; i; --i) {
      add(result[i], mul(result[i - 1], n - size[x]));
    }
    map<int, int> ways;
    map<int, vector<int>> polys;
    for (int i = 0; i < foo.size(); ++i) {
      add(ways[foo[i]], bar[i]);
      if (!polys.count(foo[i])) {
        vector<int> t = result;
        for (int j = 1; j < result.size(); ++j) {
          sub(t[j], mul(t[j - 1], foo[i]));
        }
        polys[foo[i]] = t;
      }
    }
    for (auto p : ways) {
      int y = p.first, z = p.second;
      vector<int>& poly = polys[y];
      for (int i = 0; i < min(k + 1, (int) poly.size()); ++i) {
        add(answer, mul(mul(poly[i], z), mul(binom(k, i), fac[i])));
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  fac[0] = ifac[0] = inv[1] = fac[1] = ifac[1] = 1;
  for (int i = 2; i <= max(n, k); ++i) {
    inv[i] = mul(mod - mod / i, inv[mod % i]);
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(1, 0);
  cout << answer << '\n';
  return 0;
}
