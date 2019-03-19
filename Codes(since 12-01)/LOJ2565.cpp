#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;

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

template<typename T>
int mul(T x) {
  return x;
}

template<typename T, typename... R>
int mul(T x, R... y) {
  return (long long) x * mul(y...) % mod;
}

int tt, A, B, C, a[N], b[N], c[N], d[N], e[N], f[N], p[N], q[N], r[N], s[N], t[N], w[N], u[N], v[N], primes[N], all;
bool is_prime[N];

void F(int* a, int n) {
  for (int i = 1; i <= n; ++i) {
    for (int j = i + i; j <= n; j += i) {
      sub(a[j], a[i]);
    }
  }
}

void G(int* a, int n) {
  for (int i = 1; i <= all && primes[i] <= n; ++i) {
    for (int j = n / primes[i]; j; --j) {
      add(a[j], a[j * primes[i]]);
    }
  }
}

void H(int* a, int n) {
  for (int i = 1; i <= all && primes[i] <= n; ++i) {
    for (int j = 1; j * primes[i] <= n; ++j) {
      add(a[j * primes[i]], a[j]);
    }
  }
}

void sieve(int n) {
  fill(is_prime + 1, is_prime + 1 + n, true);
  all = 0;
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
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d%d", &A, &B, &C);
    int n = max(A, max(B, C));
    sieve(n);
    for (int i = 1; i <= n; ++i) {
      a[i] = A / i;
      b[i] = B / i;
      c[i] = C / i;
      d[i] = e[i] = f[i] = (i == 1);
    }
    F(e, n);
    F(f, n);
    G(c, n);
    int answer = 0;
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
          u[j] = mul(u[j], w[j]);
          v[j] = mul(v[j], w[j]);
        }
        H(u, m);
        H(v, m);
        for (int j = 1; j <= m; ++j) {
          u[j] = mul(u[j], t[j]);
          v[j] = mul(v[j], s[j]);
        }
        for (int y = x; x * y <= m; ++y) {
          if (__gcd(x, y) == 1) {
            int s1 = 0, s2 = 0;
            for (int j = y; j <= m; j += y) {
              add(s1, u[j]);
              add(s2, v[j]);
            }
            add(answer, mul(s1, p[x], q[y], r[x * y]));
            if (x != y) {
              add(answer, mul(s2, p[y], q[x], r[x * y]));
            }
          }
        }
      }
    }
    printf("%d\n", answer);
  }
  return 0;
}
