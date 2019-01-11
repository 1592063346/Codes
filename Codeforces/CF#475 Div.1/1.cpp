#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 9;

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

int n, a, b, k;
char sign[N];

int main() {
  scanf("%d%d%d%d%s", &n, &a, &b, &k, sign);
  int s = 0, t = (n + 1) / k;
  for (int i = 0; i < k; ++i) {
    if (sign[i] == '+') {
      add(s, mul(qpow(a, n - i), qpow(b, i)));
    } else {
      sub(s, mul(qpow(a, n - i), qpow(b, i)));
    }
  }
  int p = mul(qpow(b, k), qpow(qpow(a, mod - 2), k)), answer;
  if (p == 1) {
    answer = mul(t, s);
  } else {
    int pa = (1 - qpow(p, t) + mod) % mod;
    int pb = (1 - p + mod) % mod;
    answer = mul(s, mul(pa, qpow(pb, mod - 2)));
  }
  printf("%d\n", answer);
  return 0;
}
