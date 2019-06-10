#include<bits/stdc++.h>

using namespace std;

const int N = 12345678, mod = 1e9 + 7;

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

int n, m, f[N], binom[N], inv[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  n = n / 3 * 3;
  m = m / 3 * 3;
  binom[0] = inv[1] = 1;
  binom[1] = n + 3;
  for (int i = 2; i <= m + 1; ++i) {
    inv[i] = mul(mod - mod / i, inv[mod % i]);
    binom[i] = mul(binom[i - 1], mul(n + 4 - i, inv[i]));
  }
  f[0] = n / 3 + 1;
  f[1] = ((long long) (n + 3) * (n / 3) / 2) % mod;
  int inv3 = (mod + 1) / 3, answer = f[0];
  for (int i = 2; i <= m; ++i) {
    f[i] = binom[i + 1];
    sub(f[i], mul(3, f[i - 1]));
    sub(f[i], f[i - 2]);
    f[i] = mul(f[i], inv3);
    if (i % 3 == 0) {
      add(answer, f[i]);
    }
  }
  cout << answer << '\n';
  return 0;
}
