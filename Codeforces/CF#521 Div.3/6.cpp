#include<bits/stdc++.h>

using namespace std;

#define rg register

typedef long long ll;

template<typename T> inline bool checkMax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}

const int N = 5e3 + 10;
const ll inf = 1e16;

int n, k, x, a[N], Q[N], ql, qr;
ll f[N][N];

int main() {
  scanf("%d%d%d", &n, &k, &x);
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (rg int i = 0; i <= x; ++i) {
    for (rg int j = 0; j <= n; ++j) {
      f[i][j] = -inf;
    }
  }
  f[0][0] = 0;
  for (rg int i = 1; i <= x; ++i) {
    ql = 0, qr = -1;
    for (rg int j = 0; j < i; ++j) {
      for (; Q[ql] < j - k; ++ql);
      for (; ql <= qr && f[i - 1][j] >= f[i - 1][Q[qr]]; --qr);
      Q[++qr] = j;
    }
    for (rg int j = i; j <= n; ++j) {
      for (; Q[ql] < j - k; ++ql);
      f[i][j] = f[i - 1][Q[ql]] + a[j];
      for (; ql <= qr && f[i - 1][j] >= f[i - 1][Q[qr]]; --qr);
      Q[++qr] = j;
    }
  }
  ll ans = -inf;
  for (rg int i = n - k + 1; i <= n; ++i) {
    checkMax(ans, f[x][i]);
  }
  printf("%I64d\n", ans < 0 ? -1 : ans);
  return 0;
}
