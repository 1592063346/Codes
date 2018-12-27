#include<bits/stdc++.h>

using namespace std;

#define rg register

typedef long long ll;

const int N = 1e5 + 10, mod = 1e9 + 7;

inline void mul(int& x, int y) {
  x = 1ll * x * y % mod;
}

inline int qpow(int v, int p) {
  int res = 1;
  for (; p; p >>= 1, mul(v, v)) {
    if (p & 1) {
      mul(res, v);
    }
  }
  return res;
}

int n, q, a[N];
char s[N];

int main() {
  scanf("%d%d%s", &n, &q, s + 1);
  for (rg int i = 1; i <= n; ++i) {
    a[i] = a[i - 1] + (s[i] == '1');
  }
  for (rg int i = 1; i <= q; ++i) {
    int l, r; scanf("%d%d", &l, &r);
    int s1 = a[r] - a[l - 1], s0 = r - l + 1 - s1;
    int final = (qpow(2, s1) - 1 + mod) % mod;
    printf("%I64d\n", 1ll * final * qpow(2, s0) % mod);
  }
  return 0;
}
