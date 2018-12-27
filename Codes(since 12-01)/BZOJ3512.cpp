#include<bits/stdc++.h>

using namespace std;

const int N = 3e6 + 1, mod = 1e9 + 7, inv2 = 5e8 + 4;

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

int n, m;
bool is_prime[N];
int phi[N], minp[N];
map<int, int> value_phi, value_s[N];

void sieve() {
  memset(is_prime, true, sizeof is_prime);
  vector<int> primes;
  for (int i = 2; i < N; ++i) {
    if (is_prime[i]) {
      minp[i] = i;
      phi[i] = i - 1;
      primes.push_back(i);
    }
    for (int j = 0; j < primes.size(); ++j) {
      int d = i * primes[j];
      if (d > N) {
        break;
      }
      is_prime[d] = false;
      minp[d] = primes[j];
      if (i % primes[j] == 0) {
        phi[d] = phi[i] * primes[j];
        break;
      } else {
        phi[d] = phi[i] * phi[primes[j]];
      }
    }
  }
  phi[1] = 1;
  for (int i = 2; i < N; ++i) {
    add(phi[i], phi[i - 1]);
  }
}

int get_phi(int n) {
  if (n < N) {
    return phi[n];
  } else if (value_phi.count(n)) {
    return value_phi[n];
  } else {
    int result = mul(mul(n, n + 1), inv2);
    for (int i = 2, last; i <= n; i = last + 1) {
      last = n / (n / i);
      sub(result, mul(get_phi(n / i), last - i + 1));
    }
    return value_phi[n] = result;
  }
}

int s(int n, int m) {
  if (!m) {
    return 0;
  } else if (value_s[n].count(m)) {
    return value_s[n][m];
  } else if (n == 1) {
    return value_s[n][m] = get_phi(m);
  } else {
    int w = 1;
    for (int x = n, y; x != 1;) {
      y = minp[x];
      w *= y;
      for (; x % y == 0; x /= y);
    }
    int result = 0;
    for (int i = 1; i * i <= w; ++i) {
      if (w % i == 0) {
        add(result, mul((get_phi(w / i) - get_phi(w / i - 1) + mod) % mod, s(i, m / i)));
        if (i * i != w) {
          add(result, mul((get_phi(i) - get_phi(i - 1) + mod) % mod, s(w / i, m / (w / i))));
        }
      }
    }
    return value_s[n][m] = mul(result, n / w);
  }
}

int main() {
  sieve();
  scanf("%d%d", &n, &m);
  if (n > m) {
    swap(n, m);
  }
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    add(answer, s(i, m));
  }
  printf("%d\n", answer);
  return 0;
}
