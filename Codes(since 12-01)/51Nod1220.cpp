#include<bits/stdc++.h>

using namespace std;

const int mod = 1000000007, inv2 = 500000004, inv6 = 166666668, up = 10000001;

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
  vector<int> mu(up), primes;
  mu[1] = 1;
  for (int i = 2; i < up; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      mu[i] = mod - 1;
    }
    for (auto v : primes) {
      int d = v * i;
      if (d >= up) {
        break;
      }
      is_prime[d] = false;
      if (i % v == 0) {
        mu[d] = 0;
        break;
      } else {
        mu[d] = (mod - mu[i]) % mod;
      }
    }
  }
  for (int i = 2; i < up; ++i) {
    mu[i] = mul(mu[i], i);
    add(mu[i], mu[i - 1]);
  }
  function<int (int)> sum_pow2 = [&] (int n) {
    return mul(mul(mul(n, n + 1), 2 * n + 1), inv6);
  };
  map<int, int> value;
  function<int (int)> f = [&] (int n) {
    if (n < up) {
      return mu[n];
    } else if (value.count(n)) {
      return value[n];
    } else {
      int result = 1;
      for (int i = 2, last; i <= n; i = last + 1) {
        last = n / (n / i);
        sub(result, mul(mul(mul(i + last, last - i + 1), inv2), f(n / i)));
      }
      return value[n] = result;
    }
  };
  function<int (int)> s = [&] (int n) {
    int result = 0;
    for (int i = 1, last; i <= n; i = last + 1) {
      last = n / (n / i);
      add(result, mul(mul(mul(i + last, last - i + 1), inv2), n / i));
    }
    return result;
  };
  int n;
  scanf("%d", &n);
  int answer = 0;
  for (int i = 1, last; i <= n; i = last + 1) {
    last = n / (n / i);
    add(answer, mul((f(last) - f(i - 1) + mod) % mod, mul(s(n / i), s(n / i))));
  }
  printf("%d\n", answer);
  return 0;
}
