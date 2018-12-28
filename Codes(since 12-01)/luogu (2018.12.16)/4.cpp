#include<bits/stdc++.h>

using namespace std;

const int N = 55, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x > mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

struct matrix {
  int n, m, a[N][N];

  matrix () {
    memset(a, 0, sizeof a);
  }

  matrix operator * (const matrix& c) const {
    matrix result;
    result.n = n;
    result.m = c.m;
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= c.m; ++j) {
        for (int k = 0; k <= m; ++k) {
          add(result.a[i][j], mul(a[i][k], c.a[k][j]));
        }
      }
    }
    return result;
  }
} bas[32];

int n, m, q, energy[N], degree[N];

int main() {
  scanf("%d%d%d", &n, &m, &q);
  bas[0].n = bas[0].m = n;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &energy[i]);
    bas[0].a[i][i] = 1;
    ++degree[i];
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    ++bas[0].a[u][v];
    ++degree[u];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      bas[0].a[i][j] = mul(bas[0].a[i][j], qpow(degree[i], mod - 2));
    }
  }
  for (int i = 1; i < 31; ++i) {
    bas[i] = bas[i - 1] * bas[i - 1];
  }
  for (int i = 1; i <= q; ++i) {
    int t;
    scanf("%d", &t);
    matrix result;
    result.n = 0;
    result.m = n;
    for (int j = 1; j <= n; ++j) {
      result.a[0][j] = energy[j];
    }
    for (int j = 30; ~j; --j) {
      if (t >> j & 1) {
        result = result * bas[j];
      }
    }
    int answer = 0;
    for (int j = 1; j <= n; ++j) {
      answer ^= result.a[0][j];
    }
    printf("%d\n", answer % mod);
  }
  return 0;
}
