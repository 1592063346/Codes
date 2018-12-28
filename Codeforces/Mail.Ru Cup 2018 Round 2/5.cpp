#include<bits/stdc++.h>

using namespace std;

const int N = 1505;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, s, m, k, a[N], maxr[N], pre[N], f[N][N];

bool check(int x) {
  for (int i = 1; i <= n; ++i) {
    pre[i] = pre[i - 1] + (a[i] <= x);
  }
  memset(f, 0, sizeof f);
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      cmax(f[i][j], f[i - 1][j]);
      if (maxr[i]) {
        cmax(f[maxr[i]][j + 1], f[i - 1][j] + pre[maxr[i]] - pre[i - 1]);
      }
      if (i == n) {
        cmax(answer, f[n][j]);
      }
    }
  }
  return answer >= k;
}

int main() {
  scanf("%d%d%d%d", &n, &s, &m, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= s; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    for (int j = l; j <= r; ++j) {
      cmax(maxr[j], r);
    }
  }
  int l = 1, r = 1e9;
  while (l != r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  printf("%d\n", check(l) ? l : -1);
  return 0;
}
