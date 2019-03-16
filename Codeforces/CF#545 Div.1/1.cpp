#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

int n, m, a[N][N], b[N][N], c[N][N], h[N], rv[N], cv[N], t;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      h[j] = a[i][j];
    }
    sort(h + 1, h + 1 + m);
    t = unique(h + 1, h + 1 + m) - h - 1;
    rv[i] = t;
    for (int j = 1; j <= m; ++j) {
      b[i][j] = lower_bound(h + 1, h + 1 + t, a[i][j]) - h;
    }
  }
  for (int j = 1; j <= m; ++j) {
    for (int i = 1; i <= n; ++i) {
      h[i] = a[i][j];
    }
    sort(h + 1, h + 1 + n);
    t = unique(h + 1, h + 1 + n) - h - 1;
    cv[j] = t;
    for (int i = 1; i <= n; ++i) {
      c[i][j] = lower_bound(h + 1, h + 1 + t, a[i][j]) - h;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int answer = max(rv[i], cv[j]);
      if (b[i][j] < c[i][j]) {
        answer = max(answer, rv[i] + c[i][j] - b[i][j]);
      } else {
        answer = max(answer, cv[j] + b[i][j] - c[i][j]);
      }
      printf("%d%c", answer, " \n"[j == m]);
    }
  }
  return 0;
}
