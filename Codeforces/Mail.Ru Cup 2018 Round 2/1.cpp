#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

int n, t, a[N], b[N], go[2][N][N];

int main() {
  scanf("%d%d", &n, &t);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &b[i]);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      if (a[i] && a[j]) {
        go[0][i][j] = 1;
      }
      if (b[i] && b[j]) {
        go[1][j][i] = 1;
      }
    }
  }
  bool can = go[0][1][t];
  for (int i = 1; i <= n; ++i) {
    if (go[0][1][i] && go[1][i][t]) {
      can = true;
    }
  }
  puts(can ? "yes" : "no");
  return 0;
}
