#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, max_char = 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

char s[N];
int n, q, a[N][max_char][max_char], b[N][max_char][max_char];

int main() {
  scanf("%s%d", s + 1, &q);
  n = strlen(s + 1);
  for (int i = 0; i < max_char; ++i) {
    a[0][i][i] = b[0][i][i] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    int x = s[i] - 'a' + 1;
    for (int j = 0; j < max_char; ++j) {
      int sum = 0;
      for (int k = 0; k < max_char; ++k) {
        add(sum, a[i - 1][j][k]);
      }
      for (int k = 0; k < max_char; ++k) {
        if (k == x) {
          a[i][j][k] = sum;
        } else {
          a[i][j][k] = a[i - 1][j][k];
        }
      }
    }
    for (int j = 0; j < max_char; ++j) {
      for (int k = 0; k < max_char; ++k) {
        if (j == x) {
          b[i][j][k] = b[i - 1][j][k];
        } else {
          b[i][j][k] = (b[i - 1][j][k] - b[i - 1][x][k] + mod) % mod;
        }
      }
    }
  }
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    int answer = 0;
    for (int i = 0; i < max_char; ++i) {
      for (int j = 0; j < max_char; ++j) {
        add(answer, mul(b[l - 1][0][i], a[r][i][j]));
      }
    }
    printf("%d\n", (answer - 1 + mod) % mod);
  }
  return 0;
}
