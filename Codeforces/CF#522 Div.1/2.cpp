#include<bits/stdc++.h>

using namespace std;

#define rg register

template<typename T> inline bool checkMax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}

const int N = 1e2 + 10;

int n, a[N];
bitset<N * N> f[N][N], g[N][N];

inline bool check(int l, int r, int v, int k) {
  for (rg int i = 0; i <= k; ++i) {
    for (rg int j = 0; j <= v; ++j) {
      if (f[l][i][j] && g[r][k - i][v - j]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  scanf("%d", &n);
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a + 1, a + 1 + n);
  f[0][0][0] = 1, g[n + 1][0][0] = 1;
  for (rg int i = 1; i <= n; ++i) {
    for (rg int j = 0; j <= i; ++j) {
      f[i][j] |= f[i - 1][j];
      if (j) {
        f[i][j] |= f[i - 1][j - 1] << a[i];
      }
    }
  }
  for (rg int i = n; i; --i) {
    for (rg int j = 0; j <= n - i + 1; ++j) {
      g[i][j] |= g[i + 1][j];
      if (j) {
        g[i][j] |= g[i + 1][j - 1] << a[i];
      }
    }
  }
  int ans = 0, bl = 0, c1, c2;
  for (rg int i = 1, last; i <= n; i = last + 1) {
    for (last = i; a[last] == a[i]; ++last); --last;
    ++bl;
    if (bl == 1) {
      c1 = last - i + 1;
    }
    if (bl == 2) {
      c2 = last - i + 1;
    }
    for (rg int j = 1; j <= last - i + 1; ++j) {
      if (check(i - 1, last + 1, a[i] * j, j)) {
        checkMax(ans, j);
      } else {
        break;
      }
    }
  }
  printf("%d\n", bl == 2 && (ans == c1 || ans == c2) ? n : ans);
  return 0;
}
