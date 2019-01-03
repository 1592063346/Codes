#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int k, mod, powk[N], fac[N], invfac[N];
bool is_prime[N];
char s[N];

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

int binom(int n, int m) {
  return mul(fac[n], mul(invfac[m], invfac[n - m]));
}

int square(int x) {
  return mul(x, x);
}

int main() {
  scanf("%s%d%d", s, &k, &mod);
  int len = strlen(s), quotient = 0, remainder = 0;
  for (int i = 0; i < len; ++i) {
    remainder = remainder * 10 + s[i] - '0';
    quotient = (quotient * 10 + remainder / mod) % (mod - 1);
    remainder = remainder % mod;
  }
  vector<int> primes;
  memset(is_prime, true, sizeof is_prime);
  powk[1] = 1;
  for (int i = 2; i <= remainder; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      powk[i] = qpow(i, k);
    }
    for (auto v : primes) {
      int d = i * v;
      if (d > remainder) {
        break;
      }
      is_prime[d] = false;
      powk[d] = mul(powk[i], powk[v]);
      if (i % v == 0) {
        break;
      }
    }
  }
  fac[0] = invfac[0] = 1;
  for (int i = 1; i <= remainder; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  invfac[remainder] = qpow(fac[remainder], mod - 2);
  for (int i = remainder - 1; i > 0; --i) {
    invfac[i] = mul(invfac[i + 1], i + 1);
  }
  int answer = 0;
  for (int i = 0; i <= remainder; ++i) {
    add(answer, mul(binom(remainder, i), square((powk[i] - powk[remainder - i] + mod) % mod)));
  }
  printf("%d\n", mul(answer, qpow(2, quotient)));
  return 0;
}
