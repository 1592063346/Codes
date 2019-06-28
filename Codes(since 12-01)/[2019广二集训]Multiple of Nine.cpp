#include<bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

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

int power(int x, int y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, q, t = 0;
  cin >> n >> q;
  vector<int> inv(q + 1, 1), ifac(q + 1, 1);
  for (int i = 2; i <= q; ++i) {
    inv[i] = mul(mod - mod / i, inv[mod % i]);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  vector<int> l(q + 1), r(q + 1);
  vector<pair<int, int>> h((q << 1) + 1);
  vector<bool> tag((q << 1) + 1);
  for (int i = 1; i <= q; ++i) {
    cin >> l[i] >> r[i];
    --l[i];
    h[++t] = make_pair(l[i], i);
    h[++t] = make_pair(r[i], -i);
  }
  sort(h.begin() + 1, h.begin() + 1 + t);
  for (int i = 1; i <= t; ++i) {
    if (h[i].second > 0) {
      l[h[i].second] = i;
    } else {
      r[-h[i].second] = i;
    }
  }
  auto f = [&] (int n, bool diff) {
    int x = mul(power(10, n) - 1, (mod + 1) / 9);
    if (!diff) {
      ++x;
    }
    return x;
  };
  vector<int> ways(1 << q);
  for (int i = 1; i < 1 << q; ++i) {
    ways[i] = 1;
    for (int j = 1; j <= q; ++j) {
      if (i >> j - 1 & 1) {
        tag[l[j]] = tag[r[j]] = true;
      }
    }
    for (int j = 1; j <= q; ++j) {
      if (i >> j - 1 & 1) {
        if (l[j] == 1) {
          if (h[l[j]].first) {
            ways[i] = mul(ways[i], mul(8, f(h[l[j]].first, true)) + f(h[l[j]].first, false));
          }
        } else {
          int len = h[l[j]].first - h[l[j] - 1].first;
          if (tag[l[j] - 1]) {
            ways[i] = mul(ways[i], f(len, false));
          } else {
            ways[i] = mul(ways[i], f(len, true));
          }
        }
        int len = h[r[j]].first - h[r[j] - 1].first;
        if (tag[r[j] - 1]) {
          ways[i] = mul(ways[i], f(len, false));
        } else {
          ways[i] = mul(ways[i], f(len, true));
        }
      }
    }
    for (int j = 1; j <= q; ++j) {
      if (i >> j - 1 & 1) {
        tag[l[j]] = tag[r[j]] = false;
      }
    }
  }
  vector<int> bit(1 << q);
  for (int i = 1; i < 1 << q; ++i) {
    bit[i] = bit[i - (i & -i)] + 1;
  }
  auto fmt = [&] (vector<int>& buffer) {
    for (int i = 0; i < q; ++i) {
      for (int j = 0; j < 1 << q; ++j) {
        if (j >> i & 1) {
          add(buffer[j], buffer[j ^ (1 << i)]);
        }
      }
    }
  };
  auto ifmt = [&] (vector<int>& buffer) {
    for (int i = 0; i < q; ++i) {
      for (int j = 0; j < 1 << q; ++j) {
        if (j >> i & 1) {
          sub(buffer[j], buffer[j ^ (1 << i)]);
        }
      }
    }
  };
  auto merge = [&] (vector<int> x, vector<int> y) {
    vector<int> result(1 << q);
    vector<vector<int>> foo(q + 1, vector<int>(1 << q)), bar(q + 1, vector<int>(1 << q)), reg(q + 1, vector<int>(1 << q));
    for (int i = 0; i < 1 << q; ++i) {
      foo[bit[i]][i] = x[i];
      bar[bit[i]][i] = y[i];
    }
    for (int i = 0; i <= q; ++i) {
      fmt(foo[i]);
      fmt(bar[i]);
    }
    for (int i = 0; i <= q; ++i) {
      for (int j = 0; i + j <= q; ++j) {
        for (int k = 0; k < 1 << q; ++k) {
          add(reg[i + j][k], mul(foo[i][k], bar[j][k]));
        }
      }
    }
    for (int i = 0; i <= q; ++i) {
      ifmt(reg[i]);
      for (int j = 0; j < 1 << q; ++j) {
        if (bit[j] == i) {
          result[j] = reg[i][j];
        }
      }
    }
    return result;
  };
  vector<vector<int>> dp(10, vector<int>(1 << q));
  dp[0][0] = 1;
  int answer = 0;
  for (int i = 1, j = 1; i <= min(q, 9); j = mul(j, 9 - i), ++i) {
    dp[i] = merge(dp[i - 1], ways);
    add(answer, mul(mul(dp[i][(1 << q) - 1], j), ifac[i]));
  }
  cout << mul(answer, power(10, n - h[t].first)) << '\n';
  return 0;
}
