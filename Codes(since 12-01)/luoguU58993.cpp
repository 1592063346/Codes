/*
  原 51nod1965。
*/
#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;
const long long mod = 1e12 + 39;

long long n;
int tt, sq;
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

my_array<long long> g0, g1, mu, mu_d;

long long add(long long x, long long y, long long md) {
  long long t = x + y;
  if (t >= md) {
    t -= md;
  }
  return t;
}

long long sub(long long x, long long y, long long md) {
  long long t = x - y;
  if (t < 0) {
    t += md;
  }
  return t;
}

long long mul(long long x, long long y, long long md) {
  long double t = (long double) x * y;
  return (x * y - (long long) (t / md) * md) % md;
}

long long qpow(long long v, long long p) {
  long long result = 1;
  for (; p; p >>= 1, v = mul(v, v, mod)) {
    if (p & 1) {
      result = mul(result, v, mod);
    }
  }
  return result;
}

void sieve(int n) {
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
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

long long same_diff(long long x) {
  long long y = x + 1;
  if (x & 1) {
    y >>= 1;
  } else {
    x >>= 1;
  }
  return mul(x, y, mod - 1);
}

void min_25_sieve() {
  for (long long i = 1; i <= n; i = n / (n / i) + 1) {
    values.push_back(n / i);
  }
  for (auto x : values) {
    g0[x] = x - 1;
    g1[x] = sub(same_diff(x), 1, mod - 1);
  }
  for (auto p : primes) {
    for (auto x : values) {
      if (x < (long long) p * p) {
        break;
      }
      long long y = x / p;
      g0[x] -= g0[y] - g0[p - 1];
      g1[x] = sub(g1[x], mul(p, sub(g1[y], g1[p - 1], mod - 1), mod - 1), mod - 1);
    }
  }
  reverse(primes.begin(), primes.end());
  for (auto x : values) {
    mu[x] = mu_d[x] = sub(0, g0[x], mod - 1);
  }
  for (auto p : primes) {
    for (auto x : values) {
      if (x < (long long) p * p) {
        break;
      }
      long long y = x / p;
      mu[x] = add(mu[x], sub(mu[p], mu[y], mod - 1), mod - 1);
      mu_d[x] = add(mu_d[x], add(sub(mu_d[p], mu_d[y], mod - 1), sub(mu[p], mu[y], mod - 1), mod - 1), mod - 1);
    }
  }
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%lld", &n);
    sq = sqrt(n);
    primes.clear();
    values.clear();
    sieve(sq);
    min_25_sieve();
    long long answer = 1;
    for (auto p : primes) {
      long long t = p;
      for (int j = 1; t <= n; ++j, t *= p) {
        long long num1 = mul(t, same_diff(n / t), mod - 1);
        long long num2 = mul(t * p, same_diff(n / t / p), mod - 1);
        answer = mul(answer, qpow(j + 1, sub(num1, num2, mod - 1)), mod);
      }
    }
    long long powm = 0;
    for (long long i = sq + 1; i <= n; i = n / (n / i) + 1) {
      long long j = n / (n / i);
      powm = add(powm, mul(sub(g1[j], g1[i - 1], mod - 1), same_diff(n / i), mod - 1), mod - 1);
    }
    answer = mul(answer, qpow(2, powm), mod);
    answer = mul(answer, qpow(2, mu_d[n]), mod);
    printf("%lld\n", answer);
  }
  return 0;
}
