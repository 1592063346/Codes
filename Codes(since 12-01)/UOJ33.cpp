#include<bits/stdc++.h>

using namespace std;

const int N = 234567, sqrt_n = 290;

int n, sq, tt, depth[N], maxd[N], heavy[N], foo[sqrt_n][sqrt_n], dfn[N], cnt[N];
long long answer[N], diff[N];
vector<int> adj[N], factor[N];

void dfs1(int x, int d) {
  ++diff[depth[x] = d];
  maxd[x] = -1;
  for (auto y : adj[x]) {
    dfs1(y, d + 1);
    if (maxd[y] > maxd[x]) {
      maxd[x] = maxd[y];
      heavy[x] = y;
    }
  }
  ++maxd[x];
}

void dfs2(int x) {
  dfn[x] = ++tt;
  if (heavy[x]) {
    dfs2(heavy[x]);
    for (auto y : adj[x]) {
      if (y != heavy[x]) {
        dfs2(y);
      }
    }
  }
}

int& number(int x, int y) {
  return cnt[dfn[x] + y];
}

void solve(int x, bool reset = false) {
  for (auto y : adj[x]) {
    if (y != heavy[x]) {
      solve(y, true);
    }
  }
  if (heavy[x]) {
    solve(heavy[x]);
  }
  ++number(x, 0);
  for (auto y : adj[x]) {
    if (y != heavy[x]) {
      vector<int> coef(maxd[y] + 2);
      for (int i = 0; i <= maxd[y]; ++i) {
        for (auto j : factor[i + 1]) {
          coef[j] += number(y, i);
        }
      }
      for (int i = 1; i <= maxd[y] + 1; ++i) {
        if (i < sqrt_n) {
          answer[i] += (long long) coef[i] * foo[i][depth[x] % i];
        } else {
          for (int j = i; j <= maxd[x]; j += i) {
            answer[i] += (long long) coef[i] * number(x, j);
          }
        }
      }
      for (int i = 0; i <= maxd[y]; ++i) {
        number(x, i + 1) += number(y, i);
        for (int j = 1; j < sqrt_n; ++j) {
          foo[j][(depth[y] + i) % j] += number(y, i);
        }
      }
    }
  }
  for (int i = 1; i < sqrt_n; ++i) {
    ++foo[i][depth[x] % i];
  }
  if (reset) {
    for (int i = 1; i < sqrt_n; ++i) {
      for (int j = depth[x]; j <= depth[x] + maxd[x]; ++j) {
        foo[i][j % i] = 0;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i < n; ++i) {
    for (int j = i; j < n; j += i) {
      factor[j].push_back(i);
    }
  }
  for (int i = 2, x; i <= n; ++i) {
    cin >> x;
    adj[x].push_back(i);
  }
  dfs1(1, 0);
  dfs2(1);
  solve(1);
  for (int i = n - 1; i; --i) {
    diff[i] += diff[i + 1];
    for (int j = i + i; j < n; j += i) {
      answer[i] -= answer[j];
    }
  }
  for (int i = 1; i < n; ++i) {
    answer[i] += diff[i];
    cout << answer[i] << '\n';
  }
  return 0;
}
