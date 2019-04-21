#include<bits/stdc++.h>

using namespace std;

const int N = 345678;

long long n, k;
int mod, sq, ways[N];
vector<int> primes;

class my_array {
 public:
  int a[N << 1];

  int& operator [] (long long x) {
    return x <= sq ? a[x] : a[sq + n / x];
  }
};

my_array sump1, sump3, sump;

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

int qpow(int v, long long p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

void sieve(int n) {
  vector<bool> is_prime(n + 1, true);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
    for (auto x : primes) {
      if (i * x > n) {
        break;
      }
      is_prime[i * x] = false;
      if (i % x == 0) {
        break;
      }
    }
  }
}

void min_25_sieve() {
  vector<long long> values;
  for (long long i = 1; i <= n; i = n / (n / i) + 1) {
    values.push_back(n / i);
  }
  for (auto x : values) {
    sump1[x] = (x - 1 >> 2) % mod;
    sump3[x] = (x + 1 >> 2) % mod;
  }
  for (auto p : primes) {
    if (p != 2) {
      if (p % 4 == 1) {
        for (auto x : values) {
          if (x < (long long) p * p) {
            break;
          }
          sub(sump1[x], (sump1[x / p] - sump1[p - 1] + mod) % mod);
          sub(sump3[x], (sump3[x / p] - sump3[p - 1] + mod) % mod);
        }
      } else {
        for (auto x : values) {
          if (x < (long long) p * p) {
            break;
          }
          sub(sump1[x], (sump3[x / p] - sump3[p - 1] + mod) % mod);
          sub(sump3[x], (sump1[x / p] - sump1[p - 1] + mod) % mod);
        }
      }
    }
  }
  for (auto x : values) {
    sump[x] = (mul(sump1[x], ways[1]) + sump3[x] + (x >= 2)) % mod;
  }
}

int solve(long long n, int x) {
  if (n <= 1 || (x <= primes.size() && primes[x - 1] > n)) {
    return 0;
  }
  int result = (sump[n] - (x <= primes.size() ? sump[primes[x - 1] - 1] : sump[primes.back()]) + mod) % mod;
  for (int i = x; i <= primes.size(); ++i) {
    long long p = primes[i - 1], q = p;
    if (p * q > n) {
      break;
    }
    for (int j = 1; p * q <= n; ++j, q *= p) {
      add(result, mul(ways[p % 4 == 1 ? j : 0], solve(n / q, i + 1)));
      add(result, ways[p % 4 == 1 ? j + 1 : 0]);
    }
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k >> mod;
  for (int i = 0; i < 34; ++i) {
    ways[i] = qpow(i << 1 | 1, k);
  }
  sq = sqrt(n);
  sq = max(sq, 2);
  sieve(sq);
  min_25_sieve();
  cout << mul(qpow(4, k), (1 + solve(n, 1)) % mod) << '\n';
  return 0;
}
