#include<bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10, inf = 0x3f3f3f3f;

int n, m, minv = inf, maxv = -inf, a[N][N], answer = inf;

bool check(int x) {
  int u = minv + x, d = maxv - x;
  for (int i = 1, j = m; i <= n; ++i) {
    for (int k = 1; k <= j; ++k) {
      if (a[i][k] > u) {
        j = k - 1;
        break;
      }
    }
    if (i == 1 && !j) {
      return false;
    }
    for (int k = j + 1; k <= m; ++k) {
      if (a[i][k] < d) {
        return false;
      }
    }
  }
  return true;
}

void solve() {
  int l = 1, r = 1e9;
  while (l != r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  answer = min(answer, l);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &a[i][j]);
      minv = min(minv, a[i][j]);
      maxv = max(maxv, a[i][j]);
    }
  }
  solve();
  for (int i = 1; i <= n; ++i) {
    reverse(a[i] + 1, a[i] + 1 + m);
  }
  solve();
  for (int i = 1; i <= n >> 1; ++i) {
    for (int j = 1; j <= m; ++j) {
      swap(a[i][j], a[n - i + 1][j]);
    }
  }
  solve();
  for (int i = 1; i <= n; ++i) {
    reverse(a[i] + 1, a[i] + 1 + m);
  }
  solve();
  printf("%d\n", answer);
  return 0;
}
