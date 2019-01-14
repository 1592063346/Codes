#include<bits/stdc++.h>

using namespace std;

const int N = 9, M = 166, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
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

int tt, m, k, where, id[N][N][N], states, result[M], tmp[M], matpow[60][M][M];

int main() {
  scanf("%d%d%d", &tt, &m, &k);
  if (m == 1) {
    for (int a = 0; a <= k; ++a) {
      id[a][0][0] = states++;
    }
    for (int a = 0; a <= k; ++a) {
      int p = qpow(a + 1, mod - 2), d = id[a][0][0];
      matpow[0][d][d] = p;
      matpow[0][states][d] = p;
      if (a) {
        matpow[0][id[a - 1][0][0]][d] = mul(p, a);
      }
    }
    where = id[1][0][0];
  } else if (m == 2) {
    for (int a = 0; a <= k; ++a) {
      for (int b = 0; a + b <= k; ++b) {
        id[a][b][0] = states++;
      }
    }
    for (int a = 0; a <= k; ++a) {
      for (int b = 0; a + b <= k; ++b) {
        int p = qpow(a + b + 1, mod - 2), d = id[a][b][0];
        matpow[0][d][d] = p;
        matpow[0][states][d] = p;
        if (a) {
          matpow[0][id[a - 1][b][0]][d] = mul(p, a);
        }
        if (b) {
          matpow[0][id[a + 1][a + b < k ? b : b - 1][0]][d] = mul(p, b);
        }
      }
    }
    where = id[0][1][0];
  } else {
    for (int a = 0; a <= k; ++a) {
      for (int b = 0; a + b <= k; ++b) {
        for (int c = 0; a + b + c <= k; ++c) {
          id[a][b][c] = states++;
        }
      }
    }
    for (int a = 0; a <= k; ++a) {
      for (int b = 0; a + b <= k; ++b) {
        for (int c = 0; a + b + c <= k; ++c) {
          int p = qpow(a + b + c + 1, mod - 2), d = id[a][b][c];
          matpow[0][d][d] = p;
          matpow[0][states][d] = p;
          if (a) {
            matpow[0][id[a - 1][b][c]][d] = mul(p, a);
          }
          if (b) {
            matpow[0][id[a + 1][b - 1][a + b + c < k ? c + 1 : c]][d] = mul(p, b);
          }
          if (c) {
            matpow[0][id[a][b + 1][a + b + c < k ? c : c - 1]][d] = mul(p, c);
          }
        }
      }
    }
    where = id[0][0][1];
  }
  matpow[0][states][states] = 1;
  for (int i = 1; i < 60; ++i) {
    for (int a = 0; a <= states; ++a) {
      for (int c = 0; c <= states; ++c) {
        for (int b = 0; b <= states; ++b) {
          matpow[i][a][b] = (matpow[i][a][b] + (long long) matpow[i - 1][a][c] * matpow[i - 1][c][b]) % mod;
        }
      }
    }
  }
  while (tt--) {
    long long n;
    scanf("%lld", &n);
    memset(result, 0, sizeof result);
    result[states] = 1;
    for (int i = 59; ~i; --i) {
      if (n >> i & 1) {
        memset(tmp, 0, sizeof tmp);
        for (int b = 0; b <= states; ++b) {
          for (int a = 0; a <= states; ++a) {
            tmp[a] = (tmp[a] + (long long) result[b] * matpow[i][b][a]) % mod;
          }
        }
        memcpy(result, tmp, sizeof tmp);
      }
    }
    printf("%d\n", result[where]);
  }
  return 0;
}
