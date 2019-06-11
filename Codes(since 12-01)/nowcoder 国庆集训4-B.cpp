#include<bits/stdc++.h>

using namespace std;

const int N = 100005, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, a[N], pre[N][30][30], suf[N][30][30], pre_number[N][30], suf_number[N][30];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  auto solve = [&] () {
    for (int i = 1; i <= n; ++i) {
      memcpy(pre[i], pre[i - 1], sizeof pre[i - 1]);
      memcpy(pre_number[i], pre_number[i - 1], sizeof pre_number[i - 1]);
      for (int j = 0; j < 30; ++j) {
        if (a[i] >> j & 1) {
          ++pre_number[i][j];
          for (int k = 0; k < 30; ++k) {
            if (a[i] >> k & 1) {
              ++pre[i][j][k];
            }
          }
        }
      }
    }
    for (int i = n; i; --i) {
      memcpy(suf[i], suf[i + 1], sizeof suf[i + 1]);
      memcpy(suf_number[i], suf_number[i + 1], sizeof suf_number[i + 1]);
      for (int j = 0; j < 30; ++j) {
        if (!(a[i] >> j & 1)) {
          ++suf_number[i][j];
          for (int k = 0; k < 30; ++k) {
            if (a[i] >> k & 1) {
              ++suf[i][j][k];
            }
          }
        }
      }
    }
    int answer = 0;
    for (int i = 2; i < n; ++i) {
      for (int j = 0; j < 30; ++j) {
        int pre_sum = 0, suf_sum = 0;
        for (int k = 0; k < 30; ++k) {
          int number1 = pre[i - 1][j][k];
          int number0 = pre_number[i - 1][j] - pre[i - 1][j][k];
          if (a[i] >> k & 1) {
            add(pre_sum, mul(number0, 1 << k));
          } else {
            add(pre_sum, mul(number1, 1 << k));
          }
          number1 = suf[i + 1][j][k];
          number0 = suf_number[i + 1][j] - suf[i + 1][j][k];
          if (a[i] >> k & 1) {
            add(suf_sum, mul(number0, 1 << k));
          } else {
            add(suf_sum, mul(number1, 1 << k));
          }
        }
        add(answer, mul(1 << j, mul(pre_sum, suf_sum)));
      }
    }
    return answer;
  };
  int answer = solve();
  reverse(a + 1, a + 1 + n);
  add(answer, solve());
  cout << answer << '\n';
  return 0;
}
