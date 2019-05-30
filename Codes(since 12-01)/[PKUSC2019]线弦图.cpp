#include<bits/stdc++.h>

using namespace std;

const int N = 234567, mod = 998244353, root = 3;

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

int n, ways[N], dp[N][2], rev[N << 2];
vector<int> adj[N], nodes;

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

vector<int> divide(int l, int r) {
  if (l == r) {
    int x = nodes[l];
    vector<int> poly(2);
    poly[0] = dp[x][1];
    poly[1] = dp[x][0];
    return poly;
  } else {
    int mid = l + r >> 1;
    return pmul(divide(l, mid), divide(mid + 1, r));
  }
}

void dfs(int x, int f) {
  vector<int> nodes;
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
      nodes.push_back(y);
    }
  }
  vector<int> result(1, 1);
  if (nodes.size()) {
    ::nodes = nodes;
    result = divide(0, nodes.size() - 1);
  }
  for (int i = 0; i <= nodes.size(); ++i) {
    add(dp[x][0], mul(result[i], ways[i]));
  }
  for (int i = 1; i <= nodes.size(); ++i) {
    add(dp[x][1], mul(result[i], mul(ways[i - 1], i)));
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  ways[0] = ways[1] = 1;
  for (int i = 2; i <= n; ++i) {
    ways[i] = (ways[i - 1] + mul(ways[i - 2], i - 1)) % mod;
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(1, 0);
  cout << dp[1][0] << '\n';
  return 0;
}
