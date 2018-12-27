#include<bits/stdc++.h>

using namespace std;

int main() {
  unsigned long long n, m;
  int up = 10000001;
  vector<bool> is_prime(up, true);
  vector<int> primes;
  vector<unsigned long long> phi(up);
  phi[1] = 1ull;
  for (int i = 2; i < up; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      phi[i] = i - 1;
    }
    for (auto v : primes) {
      int d = v * i;
      if (d >= up) {
        break;
      } else {
        is_prime[d] = false;
        if (i % v == 0) {
          phi[d] = phi[i] * v;
          break;
        } else {
          phi[d] = phi[i] * phi[v];
        }
      }
    }
  }
  for (int i = 1; i < up; ++i) {
    phi[i] += phi[i - 1];
  }
  map<unsigned long long, unsigned long long> phi_value;
  function<unsigned long long (unsigned long long)> get_phi = [&] (unsigned long long n) {
    if (n < up) {
      return phi[n];
    } else if (phi_value.count(n)) {
      return phi_value[n];
    } else {
      unsigned long long result = 0;
      for (unsigned long long i = 2, last; i <= n; i = last + 1) {
        last = n / (n / i);
        result += get_phi(n / i) * (last - i + 1);
      }
      return phi_value[n] = (n & 1 ? n * ((n + 1) / 2) : n / 2 * (n + 1)) - result;
    }
  };
  function<unsigned long long (unsigned long long, unsigned long long)> qpow = [&] (unsigned long long v, unsigned long long p) {
    unsigned long long result = 1;
    for (; p; p >>= 1, v *= v) {
      if (p & 1) {
        result *= v;
      }
    }
    return result;
  };
  scanf("%llu%llu", &n, &m);
  unsigned long long answer = 0;
  for (unsigned long long i = 1, last; i <= m; i = last + 1) {
    last = m / (m / i);
    answer += qpow(m / i, n) * (get_phi(last) - get_phi(i - 1));
  }
  printf("%llu\n", answer);
  return 0;
}
