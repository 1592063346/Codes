#include<bits/stdc++.h>

using namespace std;

const int N = 5005, mod = 998244353;

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

int m, n, fac[N], ifac[N], inv[N], dp[N][N][2], foo[2][N], pre0[N][N], foopre0[N], size[N];
vector<int> adj[N];

int binom(int x, int y) {
  return x < y ? 0 : mul(fac[x], mul(ifac[y], ifac[x - y]));
}

void dfs(int x, int f) {
  memset(dp[x], 0, sizeof dp[x]);
  memset(pre0[x], 0, sizeof pre0[x]);
  dp[x][1][0] = dp[x][0][1] = 1;
  pre0[x][0] = 1;
  size[x] = 1;
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
      for (int i = 0; i < 2; ++i) {
        fill(foo[i], foo[i] + size[x] + size[y] + 1, 0);
      }
      fill(foopre0, foopre0 + size[x] + size[y] + 1, 0);
      for (int i = 0; i <= size[x]; ++i) {
        for (int j = 0; j <= size[y]; ++j) {
          add(foo[0][i + j], mul(dp[x][i][0], dp[y][j][0]));
          add(foo[0][i + j + 1], (mul(dp[x][i][1], dp[y][j][1]) << 1) % mod);
          add(foo[1][i + j], mul(dp[x][i][1], dp[y][j][0]));
          add(foo[1][i + j], mul(pre0[x][i], dp[y][j][1]));
          add(foopre0[i + j], mul(pre0[x][i], dp[y][j][0]));
        }
      }
      size[x] += size[y];
      for (int i = 0; i <= size[x]; ++i) {
        dp[x][i][0] = foo[0][i];
        dp[x][i][1] = foo[1][i];
        pre0[x][i] = foopre0[i];
      }
    }
  }
}

vector<int> pmul(vector<int> x, vector<int> y) {
  int n = x.size(), m = y.size();
  vector<int> result(n + m - 1);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      add(result[i + j], mul(x[i], y[j]));
    }
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  fac[0] = ifac[0] = inv[1] = 1;
  for (int i = 1; i < N; ++i) {
    if (i > 1) {
      inv[i] = mul(mod - mod / i, inv[mod % i]);
    }
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  cin >> m;
  vector<int> result(1, 1);
  for (int tt = 1, k; tt <= m; ++tt) {
    cin >> k;
    for (int i = 1; i <= k; ++i) {
      adj[i].clear();
    }
    for (int i = 1, x, y; i < k; ++i) {
      cin >> x >> y;
      adj[x].push_back(y);
      adj[y].push_back(x);
    }
    dfs(1, 0);
    vector<int> poly(k + 1);
    for (int i = 1; i <= k; ++i) {
      int coef = mul(dp[1][i][0], tt != 1 ? fac[i] : fac[i - 1]);
      for (int j = 0; j <= i; ++j) {
        if (tt != 1) {
          if (i - j & 1) {
            sub(poly[j], mul(coef, mul(binom(i - 1, i - j), ifac[j])));
          } else {
            add(poly[j], mul(coef, mul(binom(i - 1, i - j), ifac[j])));
          }
        } else {
          if (j >= 1) {
            if (i - j & 1) {
              sub(poly[j - 1], mul(coef, mul(binom(i - 1, i - j), ifac[j - 1])));
            } else {
              add(poly[j - 1], mul(coef, mul(binom(i - 1, i - j), ifac[j - 1])));
            }
          }
          if (j >= 2) {
            if (i - j & 1) {
              add(poly[j - 2], mul(coef, mul(binom(i - 1, i - j), ifac[j - 2])));
            } else {
              sub(poly[j - 2], mul(coef, mul(binom(i - 1, i - j), ifac[j - 2])));
            }
          }
        }
      }
    }
    result = pmul(result, poly);
  }
  int answer = 0;
  for (int i = 1; i < result.size(); ++i) {
    add(answer, mul(fac[i], result[i]));
  }
  cout << answer << '\n';
  return 0;
}
