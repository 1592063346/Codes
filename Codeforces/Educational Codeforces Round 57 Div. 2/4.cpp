#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const long long inf = 1e15;

int n, a[N];
long long f[N][4];
char s[N];

int main() {
  scanf("%d%s", &n, s + 1);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j < 4; ++j) {
      f[i][j] = inf;
    }
  }
  f[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    memcpy(f[i], f[i - 1], sizeof f[i - 1]);
    if (s[i] == 'h') {
      f[i][0] = f[i - 1][0] + a[i];
      f[i][1] = min(f[i - 1][1], f[i - 1][0]);
    } else if (s[i] == 'a') {
      f[i][1] = f[i - 1][1] + a[i];
      f[i][2] = min(f[i - 1][2], f[i - 1][1]);
    } else if (s[i] == 'r') {
      f[i][2] = f[i - 1][2] + a[i];
      f[i][3] = min(f[i - 1][3], f[i - 1][2]);
    } else if (s[i] == 'd') {
      f[i][3] = f[i - 1][3] + a[i];
    }
  }
  long long answer = inf;
  for (int i = 0; i < 4; ++i) {
    answer = min(answer, f[n][i]);
  }
  printf("%lld\n", answer);
  return 0;
}
