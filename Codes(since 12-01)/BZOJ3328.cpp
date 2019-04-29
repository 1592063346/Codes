#include<bits/stdc++.h>

using namespace std;

int tt, k, mod;
long long n;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int x, int y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

struct matrix_t {
  int a[2][2];

  matrix_t() {
    memset(a, 0, sizeof a);
  }

  int* operator [] (int x) {
    return a[x];
  }

  matrix_t operator + (matrix_t b) {
    matrix_t result;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        result[i][j] = (a[i][j] + b[i][j]) % mod;
      }
    }
    return result;
  }

  matrix_t operator * (int x) {
    matrix_t result;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        result[i][j] = mul(a[i][j], x);
      }
    }
    return result;
  }

  matrix_t operator * (matrix_t b) {
    matrix_t result;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 2; ++k) {
          add(result[i][j], mul(a[i][k], b[k][j]));
        }
      }
    }
    return result;
  }
};

int find_root(int x) {
  vector<int> factor;
  for (int i = 2; i * i <= x - 2; ++i) {
    if ((x - 1) % i == 0) {
      factor.push_back(i);
      if (i != (x - 1) / i) {
        factor.push_back((x - 1) / i);
      }
    }
  }
  for (int i = 2;; ++i) {
    bool ok = true;
    for (int j = 0; j < factor.size(); ++j) {
      if (qpow(i, factor[j]) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) {
      return i;
    }
  }
}

matrix_t qpow(matrix_t x, long long y) {
  matrix_t result;
  result[0][0] = result[1][1] = 1;
  for (; y; y >>= 1, x = x * x) {
    if (y & 1) {
      result = result * x;
    }
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> tt;
  while (tt--) {
    cin >> n >> k >> mod;
    int root = find_root(mod), omega = qpow(root, (mod - 1) / k);
    matrix_t foo, bar, e;
    foo[0][0] = foo[0][1] = foo[1][0] = 1;
    e[0][0] = e[1][1] = 1;
    for (int i = 0, j = 1; i < k; ++i, j = mul(j, omega)) {
      bar = bar + qpow(foo * j + e, n);
    }
    bar = bar * qpow(k, mod - 2);
    cout << bar[0][0] << '\n';
  }
  return 0;
}
