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

int n, k, answer, rev[N], fac[N], ifac[N], inv[N], size[N], value[N], sum[N];
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

vector<int> padd(vector<int> x, vector<int> y) {
  for (int i = 0; i < x.size(); ++i) {
    add(x[i], y[i]);
  }
  return x;
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

int binom(int x, int y) {
  return mul(fac[x], mul(ifac[y], ifac[x - y]));
}

pair<vector<int>, vector<int>> solve(int l, int r, vector<int>& sub, vector<int>& ways) {
  if (l == r) {
    vector<int> x(2), y(1);
    x[0] = 1;
    x[1] = sub[l];
    y[0] = ways[l];
    return make_pair(x, y);
  } else {
    int mid = l + r >> 1;
    pair<vector<int>, vector<int>> ll = solve(l, mid, sub, ways);
    pair<vector<int>, vector<int>> rr = solve(mid + 1, r, sub, ways);
    return make_pair(pmul(ll.first, rr.first), padd(pmul(ll.first, rr.second), pmul(ll.second, rr.first)));
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
    foo.push_back(n - size[x]);
    bar.push_back(0);
    pair<vector<int>, vector<int>> result = solve(0, foo.size() - 1, foo, bar);
    for (int i = 1; i < result.first.size(); ++i) {
      sub(result.first[i], mul(n - size[x], result.first[i - 1]));
    }
    for (int i = 0; i < min((int) result.first.size(), k + 1); ++i) {
      add(value[x], mul(mul(result.first[i], fac[i]), binom(k, i)));
    }
    for (int i = 0; i < min((int) result.second.size(), k + 1); ++i) {
      add(answer, mul(mul(result.second[i], fac[i]), binom(k, i)));
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
