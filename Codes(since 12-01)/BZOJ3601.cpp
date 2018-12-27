#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10, mod = 1e9 + 7;

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

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

int d, w, p[N], alpha[N], a[N][N];

void get_coefficient() {
  int sum = 0;
  for (int i = 0; i <= d + 1; ++i) {
    add(sum, qpow(i, d));
    a[i][d + 2] = sum;
    int pow_value = 1;
    for (int j = 0; j <= d + 1; ++j) {
      a[i][j] = pow_value;
      pow_value = mul(pow_value, i);
    }
  }
  for (int i = 0; i <= d + 1; ++i) {
    int rev = i;
    for (int j = i + 1; j <= d + 1; ++j) {
      if (a[j][i]) {
        rev = j;
        break;
      }
    }
    if (rev != i) {
      for (int j = i; j <= d + 2; ++j) {
        swap(a[rev][j], a[i][j]);
      }
    }
    for (int j = i + 1; j <= d + 1; ++j) {
      int p = mul(a[j][i], qpow(a[i][i], mod - 2));
      for (int k = i; k <= d + 2; ++k) {
        sub(a[j][k], mul(a[i][k], p));
      }
    }
  }
  for (int i = d + 1; ~i; --i) {
    for (int j = i + 1; j <= d + 1; ++j) {
      sub(a[i][d + 2], mul(a[i][j], a[j][d + 2]));
    }
    a[i][d + 2] = mul(a[i][d + 2], qpow(a[i][i], mod - 2));
  }
}

int g(int i, int j) {
  int p_i = p[j], alpha_i = alpha[j];
  int c1 = (long long) alpha_i * i % (mod - 1);
  int c2 = (c1 + d - i + mod - 1) % (mod - 1);
  return (qpow(p_i, c1) - qpow(p_i, c2) + mod) % mod;
}

int main() {
  scanf("%d%d", &d, &w);
  get_coefficient();
  for (int i = 1; i <= w; ++i) {
    scanf("%d%d", &p[i], &alpha[i]);
  }
  int answer = 0;
  for (int i = 0; i <= d + 1; ++i) {
    int result = a[i][d + 2];
    for (int j = 1; j <= w; ++j) {
      result = mul(result, g(i, j));
    }
    add(answer, result);
  }
  printf("%d\n", answer);
  return 0;
}
