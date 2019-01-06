#include<bits/stdc++.h>

using namespace std;

const int mod = 1000000007, inv2 = 500000004, inv6 = 166666668, up = 4641589, md = 1000003;

int main() {
  function<int (int, int)> mul = [&] (int x, int y) {
    return (long long) x * y % mod;
  };
  function<void (int&, int)> add = [&] (int& x, int y) {
    x += y;
    if (x >= mod) {
      x -= mod;
    }
  };
  function<void (int&, int)> sub = [&] (int& x, int y) {
    x -= y;
    if (x < 0) {
      x += mod;
    }
  };
  vector<bool> is_prime(up, true);
  vector<int> phi(up), primes;
  phi[1] = 1;
  for (int i = 2; i < up; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      phi[i] = i - 1;
    }
    for (auto v : primes) {
      int d = v * i;
      if (d >= up) {
        break;
      }
      is_prime[d] = false;
      if (i % v == 0) {
        phi[d] = mul(phi[i], v);
        break;
      } else {
        phi[d] = mul(phi[i], phi[v]);
      }
    }
  }
  for (int i = 2; i < up; ++i) {
    phi[i] = mul(mul(phi[i], i), i);
    add(phi[i], phi[i - 1]);
  }
  function<int (long long)> sum_pow2 = [&] (long long n) {
    n %= mod;
    return mul(mul(mul(n, n + 1), (n * 2 + 1)), inv6);
  };
  vector<pair<long long, int>> value[md];
  function<int (long long)> find = [&] (long long v) {
    int p = v % md;
    for (auto e : value[p]) {
      if (e.first == v) {
        return e.second;
      }
    }
    return -1;
  };
  function<void (long long, int)> insert = [&] (long long v, int result) {
    value[v % md].emplace_back(v, result);
  };
  function<int (long long)> f = [&] (long long n) {
    int returned = find(n);
    if (~returned) {
      return returned;
    } else {
      if (n < up) {
        return phi[n];
      } else {
        int result = 0, x = n % mod;
        x = mul(mul(x, x + 1), inv2);
        result = mul(x, x);
        for (long long i = 2, last; i <= n; i = last + 1) {
          last = n / (n / i);
          sub(result, mul((sum_pow2(last) - sum_pow2(i - 1) + mod) % mod, f(n / i)));
        }
        insert(n, result);
        return result;
      }
    }
  };
  long long n;
  scanf("%lld", &n);
  int answer = 0;
  for (long long i = 1, last; i <= n; i = last + 1) {
    last = n / (n / i);
    add(answer, mul(mul(mul((i + last) % mod, (last - i + 1) % mod), inv2), f(n / i)));
  }
  printf("%d\n", answer);
  return 0;
}
