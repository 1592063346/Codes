#include<bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int add(int x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
  return x;
}

int sub(int x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
  return x;
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  int inv100 = qpow(100, mod - 2);
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i];
    a[i] = mul(a[i], inv100);
    b[i] = mul(b[i], inv100);
  }
  for (int i = n - 2; ~i; --i) {
    int dcoef = qpow(sub(1, mul(b[i], b[i + 1])), mod - 2);
    b[i] = add(b[i], mul(mul(mul(a[i], a[i]), b[i + 1]), dcoef));
    a[i] = mul(mul(a[i], a[i + 1]), dcoef);
  }
  cout << a[0] << '\n';
  return 0;
}
