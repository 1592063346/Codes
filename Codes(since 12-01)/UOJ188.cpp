#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

long long l, r, n;
int sq;
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

my_array<long long> g0;

void sieve(int n) {
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
    for (auto v : primes) {
      long long d = (long long) i * v;
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
    g0[x] = x - 1;
  }
  for (auto p : primes) {
    for (auto x : values) {
      if (x < (long long) p * p) {
        break;
      }
      long long y = x / p;
      g0[x] -= g0[y] - g0[p - 1];
    }
  }
}

long long get_s(long long n, int x) {
  if (n <= 1 || (x <= primes.size() && primes[x - 1] > n)) {
    return 0;
  }
  long long result = 0;
  for (int i = x; i <= primes.size(); ++i) {
    int p = primes[i - 1];
    long long t = p;
    if (t * p > n) {
      break;
    }
    for (int j = 1; t * p <= n; ++j, t *= p) {
      result += get_s(n / t, i + 1) + p * (1 + max(0ll, g0[n / t] - i));
    }
  }
  return result;
}

long long solve(long long x) {
  n = x;
  sq = sqrt(n);
  primes.clear();
  values.clear();
  sieve(max(2, sq));
  min_25_sieve();
  return get_s(x, 1);
}

int main() {
  scanf("%lld%lld", &l, &r);
  printf("%lld\n", solve(r) - solve(l - 1));
  return 0;
}
