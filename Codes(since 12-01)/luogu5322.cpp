#include<bits/stdc++.h>

using namespace std;

const int N = 123, M = 23456;

int s, n, m, a[N][N], sum[M], f[N][M];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> s >> n >> m;
  for (int j = 0; j < s; ++j) {
    for (int i = 1; i <= n; ++i) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    sort(a[i], a[i] + s);
    memset(sum, 0, sizeof sum);
    for (int j = 0; j < s; ++j) {
      if ((a[i][j] << 1 | 1) <= m) {
        sum[a[i][j] << 1 | 1] += i;
      }
    }
    for (int j = 1; j <= m; ++j) {
      sum[j] += sum[j - 1];
    }
    for (int j = 0; j <= m; ++j) {
      f[i][j] = f[i - 1][j];
    }
    for (int j = 0; j < s; ++j) {
      if ((a[i][j] << 1 | 1) <= m) {
        int x = a[i][j] << 1 | 1;
        for (int k = 0; k + x <= m; ++k) {
          f[i][k + x] = max(f[i][k + x], f[i - 1][k] + sum[x]);
        }
      }
    }
  }
  int answer = 0;
  for (int i = 0; i <= m; ++i) {
    answer = max(answer, f[n][i]);
  }
  cout << answer << '\n';
  return 0;
}
