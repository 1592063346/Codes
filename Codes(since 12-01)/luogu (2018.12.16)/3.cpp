#include<bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7, N = 1e6 + 10;

int mul(int x, int y, int mo) {
  return (long long) x * y % mo;
}

int qpow(int v, int p, int mo) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v, mo)) {
    if (p & 1) {
      result = mul(result, v, mo);
    }
  }
  return result;
}

bool is_prime[N];

vector<int> sieve_prime(int n) {
  memset(is_prime, true, sizeof is_prime);
  vector<int> primes;
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
    for (auto v : primes) {
      int d = v * i;
      if (d > n) {
        break;
      }
      is_prime[d] = false;
      if (i % v == 0) {
        break;
      }
    }
  }
  return primes;
}

int n, k;

int main() {
  scanf("%d%d", &n, &k);
  vector<int> primes = sieve_prime(n);
  int answer = 1;
  for (auto v : primes) {
    int pi = mul(v - 1, qpow(v, mod - 2, mod), mod), num = n - n / v;
    answer = mul(answer, qpow(pi, (qpow(n, k, mod - 1) - qpow(num, k, mod - 1) + mod - 1) % (mod - 1), mod), mod);
    for (long long i = v; i <= n; i *= v) {
      int add = n / i - n / (i * v);
      answer = mul(answer, qpow(i, (qpow(num + add, k, mod - 1) - qpow(num, k, mod - 1) + mod - 1) % (mod - 1), mod), mod);
      num += add;
    }
  }
  printf("%d\n", answer);
  return 0;
}
