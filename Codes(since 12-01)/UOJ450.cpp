#include<bits/stdc++.h>

using namespace std;

const int N = 556789, mod = 19491001;

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

int n, k, d, fac[N], ifac[N], inv[N];

int binom(int x, int y) {
  return mul(fac[x], mul(ifac[y], ifac[x - y]));
}

int find_root(int x) {
  vector<int> factor;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      factor.push_back(i);
      if (x / i != i) {
        factor.push_back(x / i);
      }
    }
  }
  for (int i = 2;; ++i) {
    bool ok = true;
    for (auto x : factor) {
      if (qpow(i, x) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) {
      return i;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k >> d;
  if (d == 1) {
    cout << qpow(k, n) << '\n';
  } else {
    fac[0] = ifac[0] = inv[1] = 1;
    for (int i = 1; i <= k; ++i) {
      if (i > 1) {
        inv[i] = mul(mod - mod / i, inv[mod % i]);
      }
      fac[i] = mul(fac[i - 1], i);
      ifac[i] = mul(ifac[i - 1], inv[i]);
    }
    int answer = 0;
    if (d == 2) {
      for (int i = 0; i <= k; ++i) {
        add(answer, mul(binom(k, i), qpow((2 * i - k + mod) % mod, n)));
      }
      int inv2 = mod + 1 >> 1;
      cout << mul(answer, qpow(inv2, k)) << '\n';
    } else {
      int root = find_root(mod), omega = qpow(root, (mod - 1) / 3), omega2 = mul(omega, omega);
      for (int i = 0; i <= k; ++i) {
        for (int j = 0; i + j <= k; ++j) {
          int foo = mul(binom(k, i), binom(k - i, j)), bar = i;
          add(bar, mul(omega, j));
          add(bar, mul(omega2, k - i - j));
          add(answer, mul(foo, qpow(bar, n)));
        }
      }
      int inv3 = qpow(3, mod - 2);
      cout << mul(answer, qpow(inv3, k)) << '\n';
    }
  }
  return 0;
}
