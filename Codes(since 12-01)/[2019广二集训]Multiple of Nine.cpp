#include<bits/stdc++.h>

using namespace std;

const int N = 32, mod = 1e9 + 7;

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

int n, q, t, l[N], r[N], ways[1 << 15], dp[10][1 << 15];
pair<int, int> h[N];
bool tag[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> l[i] >> r[i];
    --l[i];
    h[++t] = make_pair(l[i], i);
    h[++t] = make_pair(r[i], -i);
  }
  sort(h + 1, h + 1 + t);
  for (int i = 1; i <= t; ++i) {
    if (h[i].second > 0) {
      l[h[i].second] = i;
    } else {
      r[-h[i].second] = i;
    }
  }
  auto f = [&] (int n, bool diff) {
    int x = mul(qpow(10, n) - 1, (mod + 1) / 9);
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
  dp[0][0] = 1;
  int answer = 0;
  for (int i = 1, j = 1; i <= min(q, 9); j = mul(j, 9 - i), ++i) {
    for (int j = 1; j < 1 << q; ++j) {
      for (int k = j; k; k = j & (k - 1)) {
        int compj = j ^ k;
        if (k > compj) {
          add(dp[i][j], mul(dp[i - 1][compj], ways[k]));
        }
      }
    }
    add(answer, mul(dp[i][(1 << q) - 1], j));
  }
  cout << mul(answer, qpow(10, n - h[t].first)) << '\n';
  return 0;
}
