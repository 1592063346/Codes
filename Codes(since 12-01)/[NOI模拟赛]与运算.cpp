#include<bits/stdc++.h>

using namespace std;

const int N = 1234567;

int n, a[N];
long long dp[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    ++a[x];
  }
  int limit = 1 << 20;
  for (int i = 1; i < limit; i <<= 1) {
    for (int j = 0; j < limit; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        a[j + k] += a[i + j + k];
      }
    }
  }
  long long answer = 0;
  for (int i = limit - 1; ~i; --i) {
    for (int j = 0; j < 20; ++j) {
      if (!(i >> j & 1)) {
        dp[i] = max(dp[i], dp[i | (1 << j)] + (long long) (a[i] - a[i | (1 << j)]) * i);
      }
    }
    answer = max(answer, dp[i]);
  }
  cout << answer << '\n';
  return 0;
}
