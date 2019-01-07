#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10, mod = 1e9 + 7, inv2 = 5e8 + 4;

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

long long n;
int sq, sp[N];
bool is_prime[N];
vector<int> primes;
vector<long long> values;

template<typename T>
struct my_array {
  T a[N];

  T& operator [] (long long x) {
    return x <= sq ? a[x] : a[n / x + sq];
  }
};

my_array<int> g0, g1;

void sieve(int n) {
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      sp[primes.size()] = (sp[primes.size() - 1] + i) % mod;
    }
    for (auto v : primes) {
      long long d = (long long) v * i;
      if (d > n) {
        break;
      }
      is_prime[d] = false;
      if (i % v == 0) {
        break;
      }
    }
  }
}

void min_25_sieve() {
  for (long long i = 1; i <= n; i = n / (n / i) + 1) {
    values.push_back(n / i);
  }
  for (auto x : values) {
    g0[x] = (x - 1) % mod;
    g1[x] = (mul(mul(x % mod, (x + 1) % mod), inv2) - 1 + mod) % mod;
  }
  for (auto p : primes) {
    for (auto x : values) {
      if (x < (long long) p * p) {
        break;
      }
      long long y = x / p;
      sub(g0[x], (g0[y] - g0[p - 1] + mod) % mod);
      sub(g1[x], mul((g1[y] - g1[p - 1] + mod) % mod, p));
    }
  }
}

int get_s(long long n, int x) {
  if (n <= 1 || (x <= primes.size() && primes[x - 1] > n)) {
    return 0;
  }
  int result = (((long long) g1[n] - g0[n] - sp[x - 1] + x - 1) % mod + mod) % mod;
  if (x == 1) {
    add(result, 2);
  }
  for (int i = x; i <= primes.size(); ++i) {
    int p = primes[i - 1];
    long long t = p;
    if (t * p > n) {
      break;
    }
    for (int j = 1; t * p <= n; ++j, t *= p) {
      add(result, mul(p ^ j, get_s(n / t, i + 1)));
      add(result, p ^ j + 1);
    }
  }
  return result;
}

int main() {
  scanf("%lld", &n);
  sq = sqrt(n);
  sieve(max(2, sq));
  min_25_sieve();
  printf("%d\n", get_s(n, 1) + 1);
  return 0;
}
