#include<bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10, mod = 998244353;

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

int m, q, f[N];

int main() {
  scanf("%d", &m);
  f[0] = 1;
  while (m--) {
    int a, b;
    scanf("%d%d", &a, &b);
    int coef2 = 0, coef1 = 0, coef0 = 0;
    for (int i = 0; i <= 10000; ++i) {
      add(coef2, mul(f[i], a));
      add(coef1, mul(f[i], b));
      sub(coef1, mul(f[i], mul(2, mul(i, a))));
      add(coef0, mul(f[i], mul(i, mul(i, a))));
      sub(coef0, mul(f[i], mul(i, b)));
      add(coef0, f[i]);
      f[i] = ((long long) coef2 * i * i % mod + (long long) coef1 * i % mod + coef0) % mod;
    }
  }
  scanf("%d", &q);
  while (q--) {
    int x;
    scanf("%d", &x);
    printf("%d\n", f[x]);
  }
  return 0;
}
