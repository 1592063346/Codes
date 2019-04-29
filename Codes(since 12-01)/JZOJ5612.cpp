#include<bits/stdc++.h>

using namespace std;

const int mod = 100003;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

long long a, b, x, y;
int fac[mod], ifac[mod], inv[mod], f[5][2];
vector<int> bitx, bitxy;

int binom(int x, int y) {
  return x < 0 || y < 0 || x < y ? 0 : mul(fac[x], mul(ifac[y], ifac[x - y]));
}

int dp(int here, bool borrow) {
  if (!~here) {
    return !borrow;
  }
  if (~f[here][borrow]) {
    return f[here][borrow];
  }
  int result = 0;
  for (int i = 0; i <= bitx[here]; ++i) {
    if (!borrow) {
      if (bitxy[here] - i >= 0) {
        add(result, mul(mul(binom(bitx[here], i), binom(bitxy[here] - i, bitx[here])), dp(here - 1, false)));
      }
      if (bitxy[here] - i > 0) {
        add(result, mul(mul(binom(bitx[here], i), binom(bitxy[here] - i - 1, bitx[here])), dp(here - 1, true)));
      }
    } else {
      if (bitxy[here] - i < 0) {
        add(result, mul(mul(binom(bitx[here], i), binom(bitxy[here] - i + mod, bitx[here])), dp(here - 1, false)));
      }
      if (bitxy[here] - i <= 0) {
        add(result, mul(mul(binom(bitx[here], i), binom(bitxy[here] - i + mod - 1, bitx[here])), dp(here - 1, true)));
      }
    }
  }
  return f[here][borrow] = result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  fac[0] = ifac[0] = inv[1] = 1;
  for (int i = 1; i < mod; ++i) {
    if (i > 1) {
      inv[i] = mul(mod - mod / i, inv[mod % i]);
    }
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(ifac[i - 1], inv[i]);
  }
  cin >> a >> b;
  if (a < b || (a + b & 1)) {
    cout << 0 << '\n';
    return 0;
  }
  x = a + b >> 1;
  y = a - b >> 1;
  for (long long t = x; t; t /= mod) {
    bitx.push_back(t % mod);
  }
  for (long long t = x + y; t; t /= mod) {
    bitxy.push_back(t % mod);
  }
  cerr << bitx.size() << ' ' << bitxy.size() << '\n';
  int answer = 0;
  memset(f, -1, sizeof f);
  add(answer, dp(bitx.size() - 1, false));
  if (bitxy.size() > bitx.size()) {
    add(answer, dp(bitx.size() - 1, true));
  }
  cout << answer << '\n';
  return 0;
}
