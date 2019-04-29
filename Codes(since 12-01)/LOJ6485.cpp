#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353, root = 3;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int x, long long y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

int tt, s, a[4];
long long n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> tt;
  while (tt--) {
    cin >> n >> s >> a[0] >> a[1] >> a[2] >> a[3];
    int omega = qpow(root, mod - 1 >> 2), result = 0;
    for (int i = 0; i < 4; ++i) {
      for (int k = 0, j = 1; k < 4; ++k, j = mul(j, omega)) {
        int foo = qpow((mul(s, j) + 1) % mod, n);
        int bar = qpow(qpow(j, i), mod - 2);
        add(result, mul(a[i], mul(foo, bar)));
      }
    }
    result = mul(result, qpow(4, mod - 2));
    cout << result << '\n';
  }
  return 0;
}
