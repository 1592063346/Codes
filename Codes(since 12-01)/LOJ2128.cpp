#include<bits/stdc++.h>

using namespace std;

const int N = 5e2 + 10, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, m;
char s[N];

struct matrix_t {
  int a[5][5];

  matrix_t() {
    memset(a, 0, sizeof a);
  }

  matrix_t operator + (matrix_t b) {
    matrix_t result;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        add(result.a[i][j], (a[i][j] + b.a[i][j]) % mod);
      }
    }
    return result;
  }

  matrix_t operator * (matrix_t b) {
    matrix_t result;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        for (int k = 0; k < m; ++k) {
          add(result.a[i][j], mul(a[i][k], b.a[k][j]));
        }
      }
    }
    return result;
  }
} normal_mat, pow_mat[N][10], f[N], g[N][N];

int main() {
  scanf("%s%d", s + 1, &m);
  n = strlen(s + 1);
  for (int i = 0; i < m; ++i) {
    normal_mat.a[i][i] = 1;
  }
  pow_mat[0][0] = normal_mat;
  matrix_t& tran = pow_mat[0][1];
  for (int i = 0; i < m; ++i) {
    tran.a[i][0] = 1;
    if (i + 1 < m) {
      tran.a[i][i + 1] = 1;
    }
  }
  for (int i = 2; i < 10; ++i) {
    pow_mat[0][i] = pow_mat[0][i - 1] * tran;
  }
  for (int i = 1; i <= n; ++i) {
    pow_mat[i][0] = normal_mat;
    matrix_t& tran = pow_mat[i][1];
    tran = pow_mat[i - 1][9] * pow_mat[i - 1][1];
    for (int j = 2; j < 10; ++j) {
      pow_mat[i][j] = pow_mat[i][j - 1] * tran;
    }
  }
  for (int i = 1; i <= n; ++i) {
    g[i][i] = pow_mat[0][s[i] - '0'];
    for (int j = i - 1; j >= 1; --j) {
      g[j][i] = pow_mat[i - j][s[j] - '0'] * g[j + 1][i];
    }
  }
  f[0] = normal_mat;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      f[i] = f[i] + f[j] * g[j + 1][i];
    }
  }
  printf("%d\n", f[n].a[0][0]);
  return 0;
}
