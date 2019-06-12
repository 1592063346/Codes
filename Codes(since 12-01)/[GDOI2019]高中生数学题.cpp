#include<bits/stdc++.h>

using namespace std;

const int N = 70;

long long n, p, bits[N], dp[N][N][2];
int k, t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> p >> k;
  long long x = n;
  while (x) {
    bits[++t] = x % p;
    x /= p;
  }
  dp[0][0][0] = 1;
  for (int i = 1; i <= t; ++i) {
    for (int a = 0; a <= i; ++a) {
      dp[i][a][0] += bits[i] * (dp[i - 1][a][0] + dp[i - 1][a][1]);
      dp[i][a][0] += dp[i - 1][a][0];
      if (a) {
        dp[i][a][1] += dp[i - 1][a - 1][1];
        dp[i][a][1] += (p - 1 - bits[i]) * (dp[i - 1][a - 1][0] + dp[i - 1][a - 1][1]);
      }
    }
  }
  long long answer = 0;
  for (int i = k; i <= t; ++i) {
    answer += dp[t][i][0];
  }
  cout << answer << '\n';
  return 0;
}
