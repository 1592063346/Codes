#include<bits/stdc++.h>

using namespace std;

const int N = 123456;
const long long llinf = 1e18;

int n, e, t, p[N], q[N], l, r;
long long dp[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> e >> t;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
  }
  q[l = r = 0] = 0;
  long long pre_min = llinf;
  for (int i = 1, j = 0; i <= n; ++i) {
    dp[i] = llinf;
    while (l <= r && 2 * (p[i] - p[q[l] + 1]) > t) {
      ++l;
    }
    if (l <= r) {
      dp[i] = min(dp[i], dp[q[l]] - p[q[l]] + p[i] + t);
    }
    while (2 * (p[i] - p[j + 1]) > t) {
      pre_min = min(pre_min, dp[j] - p[j] - 2 * p[j + 1]);
      ++j;
    }
    dp[i] = min(dp[i], pre_min + 3ll * p[i]);
    while (l <= r && dp[i] - p[i] <= dp[q[r]] - p[q[r]]) {
      --r;
    }
    q[++r] = i;
  }
  cout << dp[n] + e - p[n] << '\n';
  return 0;
}
