#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

unsigned long long a[N], b[N], c[N], d[N], e[N], f[N], p[N], q[N], r[N], s[N], t[N], w[N], u[N], v[N];
int n, primes[N], all;
bool is_prime[N];

void F(unsigned long long* a, int n) {
  for (int i = 1; i <= n; ++i) {
    for (int j = i + i; j <= n; j += i) {
      a[j] -= a[i];
    }
  }
}

void G(unsigned long long* a, int n) {
  for (int i = 1; i <= all && primes[i] <= n; ++i) {
    for (int j = n / primes[i]; j; --j) {
      a[j] += a[j * primes[i]];
    }
  }
}

void H(unsigned long long* a, int n) {
  for (int i = 1; i <= all && primes[i] <= n; ++i) {
    for (int j = 1; j <= n / primes[i]; ++j) {
      a[j * primes[i]] += a[j];
    }
  }
}

void sieve(int n) {
  fill(is_prime + 1, is_prime + 1 + n, true);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes[++all] = i;
    }
    for (int j = 1; j <= all; ++j) {
      if (primes[j] * i > n) {
        break;
      }
      is_prime[primes[j] * i] = false;
      if (i % primes[j] == 0) {
        break;
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%llu", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%llu", &b[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%llu", &c[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%llu", &d[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%llu", &e[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%llu", &f[i]);
  }
  sieve(n);
  F(e, n);
  F(f, n);
  G(c, n);
  unsigned long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    int m = n / i;
    for (int j = 1; j <= m; ++j) {
      p[j] = e[j * i];
      q[j] = f[j * i];
      r[j] = c[j * i];
      s[j] = a[j * i];
      t[j] = b[j * i];
      w[j] = d[j * i];
    }
    F(w, m);
    for (int x = 1; x * x <= m; ++x) {
      fill(u + 1, u + 1 + m, 0);
      fill(v + 1, v + 1 + m, 0);
      for (int j = x; j <= m; j += x) {
        u[j] = s[j], v[j] = t[j];
      }
      G(u, m);
      G(v, m);
      for (int j = 1; j <= m; ++j) {
        u[j] *= w[j];
        v[j] *= w[j];
      }
      H(u, m);
      H(v, m);
      for (int j = 1; j <= m; ++j) {
        u[j] *= t[j];
        v[j] *= s[j];
      }
      for (int y = x; x * y <= m; ++y) {
        if (__gcd(x, y) == 1) {
          unsigned long long s1 = 0, s2 = 0;
          for (int j = y; j <= m; j += y) {
            s1 += u[j];
            s2 += v[j];
          }
          answer += s1 * p[x] * q[y] * r[x * y];
          if (x != y) {
            answer += s2 * p[y] * q[x] * r[x * y];
          }
        }
      }
    }
  }
  printf("%llu\n", answer);
  return 0;
}
