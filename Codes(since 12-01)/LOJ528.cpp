#include<bits/stdc++.h>

using namespace std;

const int N = 1e7 + 10, mod = 998244353;

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

int mu[N], p = 1, total;
long long n, m;
vector<int> primes;
bool is_prime[N];

void sieve() {
  mu[1] = 1;
  memset(is_prime, true, sizeof is_prime);
  int up = (int) (sqrt(n) + 0.5);
  for (int i = 2; i <= up; ++i) {
    if (is_prime[i]) {
      mu[i] = -1;
      primes.push_back(i);
    }
    for (auto v : primes) {
      if (i * v > up) {
        break;
      }
      is_prime[i * v] = false;
      if (i % v == 0) {
        mu[i * v] = 0;
        break;
      } else {
        mu[i * v] = (mod - mu[i]) % mod;
      }
    }
  }
}

int f(long long x) {
  for (; (long long) p * p <= x; ++p) {
    add(total, mu[p]);
  }
  return total;
}

int main() {
  scanf("%lld%lld", &n, &m);
  if (n > m) {
    swap(n, m);
  }
  sieve();
  int answer = 0, last_answer = 0, tmp;
  long long last;
  for (long long i = 1; i <= n; i = last + 1) {
    last = min(n / (n / i), m / (m / i));
    int coef = mul(n / i % mod, m / i % mod);
    add(answer, mul(tmp = f(last), coef));
    sub(answer, mul(last_answer, coef));
    last_answer = tmp;
  }
  printf("%d\n", answer);
  return 0;
}
