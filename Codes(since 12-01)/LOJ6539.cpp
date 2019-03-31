#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;

int n, a[N], phi[N], times[N], tag[N], tt = 1;
vector<int> primes, factor[N];
bool is_prime[N];

void sieve(int n) {
  phi[1] = 1;
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      phi[i] = i - 1;
    }
    for (auto v : primes) {
      if (i * v > n) {
        break;
      }
      is_prime[i * v] = false;
      if (i % v == 0) {
        phi[i * v] = phi[i] * v;
        break;
      } else {
        phi[i * v] = phi[i] * phi[v];
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      factor[j].push_back(i);
    }
  }
}

int main() {
  scanf("%d", &n);
  sieve(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  long long answer = 0;
  for (int x = 1; x <= n; ++x, ++tt) {
    long long result = 0;
    for (int k = 1; k * x <= n; ++k) {
      for (auto y : factor[a[k * x]]) {
        if (tag[y] != tt) {
          tag[y] = tt;
          times[y] = 0;
        }
        result += phi[y] * (++times[y] * 2 - 1);
      }
    }
    answer += phi[x] * result;
  }
  printf("%lld\n", answer % mod);
  return 0;
}
