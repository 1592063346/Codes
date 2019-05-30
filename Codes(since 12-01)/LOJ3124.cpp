#include<bits/stdc++.h>

using namespace std;

const int N = 1234, mod = 998244353;

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

int n, p[N][4], size[N], dp[N][N * 3], new_dp[N * 3];
vector<pair<int, bool>> adj[N];

void dfs(int x, int f) {
  dp[x][0] = 1;
  for (auto e : adj[x]) {
    int y = e.first;
    if (y != f) {
      dfs(y, x);
      memset(new_dp, 0, sizeof new_dp);
      for (int i = 0; i <= size[x] * 3; ++i) {
        for (int j = 0; j <= size[y] * 3; ++j) {
          int foo = mul(dp[x][i], dp[y][j]);
          if (e.second == true) {
            add(new_dp[i + j], foo);
          } else {
            sub(new_dp[i + j], foo);
            add(new_dp[i], foo);
          }
        }
      }
      size[x] += size[y];
      memcpy(dp[x], new_dp, sizeof new_dp);
    }
  }
  memset(new_dp, 0, sizeof new_dp);
  for (int i = 0; i <= size[x] * 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      add(new_dp[i + j], mul(dp[x][i], mul(p[x][j], mul(j, qpow(i + j, mod - 2)))));
    }
  }
  ++size[x];
  memcpy(dp[x], new_dp, sizeof new_dp);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1, a, b, c; i <= n; ++i) {
    cin >> a >> b >> c;
    int s = qpow(a + b + c, mod - 2);
    p[i][1] = mul(a, s);
    p[i][2] = mul(b, s);
    p[i][3] = mul(c, s);
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].emplace_back(y, true);
    adj[y].emplace_back(x, false);
  }
  dfs(1, 0);
  int answer = 0;
  for (int i = 0; i <= n * 3; ++i) {
    add(answer, dp[1][i]);
  }
  cout << answer << '\n';
  return 0;
}
