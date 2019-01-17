#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, mod = 998244353;

int n, p[N], c[N];

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

void modify(int p) {
  for (; p <= n; p += p & -p) {
    ++c[p];
  }
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    result += c[p];
  }
  return result;
}

int query(int l, int r) {
  return query(r) - query(l - 1);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &p[i]);
  }
  int answer = 0, t = 0, emp = 0;
  for (int i = 1; i <= n; ++i) {
    if (!~p[i]) {
      ++t;
    }
  }
  emp = t;
  add(answer, mul(mul(t, t - 1), qpow(4, mod - 2)));
  for (int i = 1; i <= n; ++i) {
    if (~p[i]) {
      add(answer, query(p[i], n));
      modify(p[i]);
    }
  }
  t = 0;
  for (int i = 1; i <= n; ++i) {
    if (!~p[i]) {
      ++t;
    } else {
      int pos = mul(n - p[i] - query(p[i] + 1, n), qpow(emp, mod - 2));
      add(answer, mul(pos, t));
    }
  }
  t = 0;
  for (int i = n; i; --i) {
    if (!~p[i]) {
      ++t;
    } else {
      int pos = mul(p[i] - 1 - query(1, p[i] - 1), qpow(emp, mod - 2));
      add(answer, mul(pos, t));
    }
  }
  printf("%d\n", answer);
  return 0;
}
