#include<bits/stdc++.h>

using namespace std;

const int N = 3e2 + 10;
const long long inf = 1e15;

void cmax(long long& x, long long y) {
  if (x < y) {
    x = y;
  }
}

int n, k, tran[1 << 8], scores[1 << 8];
long long f[N][N][1 << 8], g[2];
char str[N];

int main() {
  scanf("%d%d%s", &n, &k, str + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      for (int s = 0; s < 1 << k; ++s) {
        f[i][j][s] = -inf;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    f[i][i][str[i] - '0'] = 0;
  }
  for (int i = 0; i < 1 << k; ++i) {
    scanf("%d%d", &tran[i], &scores[i]);
  }
  for (int len = 2; len <= n; ++len) {
    for (int i = 1; i + len - 1 <= n; ++i) {
      int j = i + len - 1, final = (j - i) % (k - 1) + 1;
      if (final == 1) {
        final = k;
      }
      for (int p = j - 1; p >= i; p -= k - 1) {
        for (int s = 0; s < 1 << final; ++s) {
          cmax(f[i][j][s], f[i][p][s >> 1] + f[p + 1][j][s & 1]);
        }
      }
      if (final == k) {
        g[0] = -inf;
        g[1] = -inf;
        for (int s = 0; s < 1 << k; ++s) {
          cmax(g[tran[s]], f[i][j][s] + scores[s]);
        }
        f[i][j][0] = g[0];
        f[i][j][1] = g[1];
      }
    }
  }
  long long answer = 0;
  for (int i = 0; i < 1 << (n - 1) % (k - 1) + 1; ++i) {
    cmax(answer, f[1][n][i]);
  }
  printf("%lld\n", answer);
  return 0;
}
