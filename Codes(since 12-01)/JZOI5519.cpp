#include<bits/stdc++.h>

using namespace std;

const int N = 567890, mod = 998244353;

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

int n, a[N], g[N], h[N], degree[N];
pair<int, int> coef[N];
string color;
vector<int> adj[N];

void dfs(int x, int f) {
  a[x] = degree[x];
  coef[x] = pair<int, int>(degree[x], (color[x - 1] == '1') * degree[x]);
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
      sub(a[x], a[y]);
      sub(coef[x].first, coef[y].first);
      add(coef[x].second, coef[y].second);
    }
  }
  a[x] = qpow(a[x], mod - 2);
  coef[x].first = qpow(coef[x].first, mod - 2);
  coef[x].second = mul(coef[x].second, coef[x].first);
  if (degree[x] == 1) {
    coef[x] = pair<int, int>(0, color[x - 1] == '1');
    a[x] = 0;
  }
}

void dfs(int x, int f, int s) {
  if (f) {
    h[x] = degree[f];
    sub(h[x], h[f]);
    sub(h[x], s);
    add(h[x], a[x]);
    h[x] = qpow(h[x], mod - 2);
    g[x] = mul(g[f], h[x]);
  }
  s = 0;
  for (auto y : adj[x]) {
    if (y != f) {
      add(s, a[y]);
    }
  }
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x, s);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> color;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
    ++degree[x];
    ++degree[y];
  }
  dfs(1, 0);
  g[1] = 1;
  dfs(1, 0, 0);
  int answer = coef[1].second;
  cout << answer << '\n';
  for (int i = 1; i <= n; ++i) {
    if (color[i - 1] != '1') {
      add(answer, g[i]);
    }
  }
  cout << answer << '\n';
  return 0;
}
