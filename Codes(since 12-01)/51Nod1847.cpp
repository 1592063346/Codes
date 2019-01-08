#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, md = 1000003;

int n, k, sq;
unsigned int powk[N], stirling[55][55], fac[55];
bool is_prime[N];
vector<int> primes, values;
vector<pair<int, unsigned int>> result_s[md];

template<typename T>
struct my_array {
  T a[N];

  T& operator [] (int x) {
    return x <= sq ? a[x] : a[n / x + sq];
  }
};

my_array<unsigned int> g0, gk, f;

unsigned int qpow(unsigned int v, int p) {
  unsigned int result = 1;
  for (; p; p >>= 1, v *= v) {
    if (p & 1) {
      result *= v;
    }
  }
  return result;
}

void init(int n) {
  fac[0] = stirling[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      stirling[i][j] = stirling[i - 1][j - 1] + stirling[i - 1][j] * j;
    }
  }
}

void sieve(int n) {
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      powk[primes.size()] = powk[primes.size() - 1] + qpow(i, k);
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
}

unsigned int powk_sum(int n) {
  unsigned int result = 0;
  for (int i = 1; i <= min(n, k); ++i) {
    unsigned down_p = 1;
    for (int j = n + 1; j > n - i; --j) {
      if (j % (i + 1) == 0) {
        down_p *= j / (i + 1);
      } else {
        down_p *= j;
      }
    }
    result += down_p * stirling[k][i];
  }
  return result;
}

void min_25_sieve() {
  for (int i = 1; i <= n; i = n / (n / i) + 1) {
    values.push_back(n / i);
  }
  for (auto x : values) {
    g0[x] = x - 1;
    gk[x] = powk_sum(x) - 1;
  }
  for (int i = 1; i <= primes.size(); ++i) {
    int p = primes[i - 1];
    unsigned int powp = qpow(p, k);
    for (auto x : values) {
      if (x < p * p) {
        break;
      }
      int y = x / p;
      g0[x] -= g0[y] - g0[p - 1];
      gk[x] -= (gk[y] - gk[p - 1]) * powp;
      f[x] += gk[y] - powk[i - 1];
    }
  }
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
    result = f[n] + g0[n];
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
  init(k);
  sq = sqrt(n);
  sieve(sq);
  min_25_sieve();
  unsigned int answer = 0;
  for (int i = 1; i <= n; i = n / (n / i) + 1) {
    int j = n / (n / i);
    answer += (unsigned) (n / i) * (n / i) * (get_s(j) - get_s(i - 1));
  }
  printf("%u\n", answer);
  return 0;
}
