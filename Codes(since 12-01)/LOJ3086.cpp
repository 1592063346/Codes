#include<bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

struct matrix_t {
  int a[5][5];

  matrix_t() {
    memset(a, 0, sizeof a);
  }

  int* operator [] (int x) {
    return a[x];
  }

  matrix_t operator * (matrix_t b) {
    matrix_t result;
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        for (int k = 0; k < 5; ++k) {
          add(result[i][j], mul(a[i][k], b[k][j]));
        }
      }
    }
    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tt, n;
  cin >> tt;
  while (tt--) {
    cin >> n;
    if (n < 3) {
      cout << 0 << '\n';
    } else {
      n -= 3;
      matrix_t result, tran, foo;
      result[0][0] = 6;
      result[0][1] = result[0][3] = 2;
      result[0][2] = 4;
      result[0][4] = 1;
      tran[0][0] = tran[0][1] = tran[1][0] = tran[2][2] = tran[3][2] = tran[3][3] = tran[3][4] = tran[4][2] = tran[4][3] = 1;
      tran[2][0] = 2;
      for (int i = 0; i < 5; ++i) {
        foo[i][i] = 1;
      }
      for (; n; n >>= 1, tran = tran * tran) {
        if (n & 1) {
          foo = foo * tran;
        }
      }
      result = result * foo;
      cout << result[0][1] << '\n';
    }
  }
  return 0;
}
