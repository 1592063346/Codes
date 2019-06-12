#include<bits/stdc++.h>

using namespace std;

const int N = 5678;
const long long llinf = 1e18;

int n, a, b, p[N];
long long dp[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> a >> b;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
  }
  ++n;
  p[n] = n;
  fill(dp + 1, dp + n + 1, llinf);
  for (int i = 0; i < n; ++i) {
    int foo = n + 1;
    long long cost = 0;
    for (int j = i + 1; j <= n; ++j) {
      if (p[j] > p[i]) {
        if (p[j] < foo) {
          dp[j] = min(dp[j], dp[i] + cost);
        }
        foo = min(foo, p[j]);
      }
      if (p[j] < p[i]) {
        cost += b;
      } else {
        cost += a;
      }
    }
  }
  cout << dp[n] << '\n';
  return 0;
}
