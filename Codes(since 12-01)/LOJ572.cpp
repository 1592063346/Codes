#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, md = 1000003;

int n, k, sq;
bool is_prime[N];
vector<int> primes, values;
vector<pair<int, unsigned int>> result_s[md];
unsigned int prime_pow[N];

template<typename T>
struct my_array {
  T a[N];

  T& operator [] (int x) {
    return x <= sq ? a[x] : a[n / x + sq];
  }
};

my_array<int> g0;

unsigned int qpow(unsigned int v, int p) {
  unsigned int result = 1;
  for (; p; p >>= 1, v *= v) {
    if (p & 1) {
      result *= v;
    }
  }
  return result;
}

void sieve(int n) {
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      prime_pow[primes.size()] = qpow(i, k);
    }
    for (auto v : primes) {
      int d = i * v;
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
  for (int i = 1; i <= n; i = n / (n / i) + 1) {
    values.push_back(n / i);
  }
  for (auto x : values) {
    g0[x] = x - 1;
  }
  for (auto p : primes) {
    for (auto x : values) {
      if (x < p * p) {
        break;
      }
      int y = x / p;
      g0[x] -= g0[y] - g0[p - 1];
    }
  }
}

unsigned int get_s(int n, int x) {
  if (n <= 1 || (x <= primes.size() && primes[x - 1] > n)) {
    return 0;
  }
  unsigned int result = 0;
  for (int i = x; i <= primes.size(); ++i) {
    int p = primes[i - 1];
    long long t = p;
    if (t * p > n) {
      break;
    }
    for (int j = 1; t * p <= n; ++j, t *= p) {
      result += get_s(n / t, i + 1) + prime_pow[i] * (1 + max(0, g0[n / t] - i));
    }
  }
  return result;
}

unsigned int find(int x) {
  int p = x % md;
  for (auto e : result_s[p]) {
    if (e.first == x) {
      return e.second;
    }
  }
  return 0;
}

void update(int x, unsigned int result) {
  result_s[x % md].emplace_back(x, result);
}

unsigned int get_s(int n) {
  unsigned int result = find(n);
  if (result) {
    return result;
  } else {
    result = get_s(n, 1) + g0[n];
    for (int i = 2; i <= n; i = n / (n / i) + 1) {
      int j = n / (n / i);
      result -= get_s(n / i) * (j - i + 1);
    }
  }
  update(n, result);
  return result;
}

int main() {
  scanf("%d%d", &n, &k);
  sq = sqrt(n);
  sieve(sq);
  min_25_sieve();
  unsigned int answer = 0;
  for (int i = 1; i <= n; i = n / (n / i) + 1) {
    int j = n / (n / i);
    answer += (unsigned int) (n / i) * (n / i) * (get_s(j) - get_s(i - 1));
  }
  printf("%u\n", answer);
  return 0;
}
