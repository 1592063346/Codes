#include<bits/stdc++.h>

using namespace std;

const int N = 678, mod = 998244353;

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

int n, tt, a[N][N];
map<vector<int>, int> rel;

int encode(vector<int> s) {
  vector<int> foo;
  vector<bool> visit(n, false);
  for (int i = 0; i < s.size(); ++i) {
    if (!visit[i]) {
      int x = i, t = 0;
      while (1) {
        ++t;
        visit[x] = true;
        if (s[x] == i) {
          break;
        }
        x = s[x];
      }
      foo.push_back(t);
    }
  }
  sort(foo.begin(), foo.end());
  return rel[foo];
}

void dfs(int n, int x, vector<int> state) {
  if (!n) {
    rel[state] = tt++;
  } else {
    for (int i = x; i <= n; ++i) {
      vector<int> new_state = state;
      new_state.push_back(i);
      dfs(n - i, i, new_state);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  dfs(n, 1, vector<int>());
  int inv = qpow(n * (n - 1) / 2, mod - 2), here = 0;
  for (auto p : rel) {
    vector<int> state = p.first, foo;
    int t = 0;
    for (auto x : state) {
      for (int j = 1; j < x; ++j) {
        foo.push_back(t + j);
      }
      foo.push_back(t);
      t += x;
    }
    if (state.size() == n) {
      a[here][p.second] = 1;
    } else {
      a[here][p.second] = a[here][tt] = 1;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
          swap(foo[i], foo[j]);
          sub(a[here][encode(foo)], inv);
          swap(foo[i], foo[j]);
        }
      }
    }
    ++here;
  }
  for (int i = 0; i < tt; ++i) {
    if (!a[i][i]) {
      int j = i;
      while (!a[j][i]) {
        ++j;
      }
      for (int k = i; k <= tt; ++k) {
        swap(a[i][k], a[j][k]);
      }
    }
    int inv = qpow(a[i][i], mod - 2);
    for (int j = i + 1; j < tt; ++j) {
      int coef = mul(a[j][i], inv);
      for (int k = i; k <= tt; ++k) {
        sub(a[j][k], mul(a[i][k], coef));
      }
    }
  }
  for (int i = tt - 1; ~i; --i) {
    for (int j = i + 1; j < tt; ++j) {
      sub(a[i][tt], mul(a[i][j], a[j][tt]));
    }
    a[i][tt] = mul(a[i][tt], qpow(a[i][i], mod - 2));
  }
  vector<int> final(n);
  for (int i = 0; i < n; ++i) {
    cin >> final[i];
    --final[i];
  }
  cout << a[encode(final)][tt] << '\n';
  return 0;
}
