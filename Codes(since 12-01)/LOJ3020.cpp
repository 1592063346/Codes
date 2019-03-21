#include<bits/stdc++.h>

using namespace std;

const int N = 4e6 + 10, M = 2e3, mod = 1e9 + 7;

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

int n, m, phi[N], h[N], g[N], s_part[M + 10][M + 10], s[M + 10];
vector<int> primes;
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
}

void modify(int p, int x) {
  int block = (p - 1) / M + 1;
  for (int i = block + 1; i <= (n - 1) / M + 1; ++i) {
    add(s[i], x);
  }
  p -= (block - 1) * M;
  for (int i = p; i <= M; ++i) {
    add(s_part[block][i], x);
  }
}

int query(int p) {
  int block = (p - 1) / M + 1;
  return (s[block] + s_part[block][p - (block - 1) * M]) % mod;
}

int main() {
  scanf("%d%d", &m, &n);
  sieve(n);
  for (int i = 1; i <= (n - 1) / M + 1; ++i) {
    int result = 0;
    for (int j = (i - 1) * M + 1; j <= min(i * M, n); ++j) {
      g[j] = mul(j, j);
      add(result, g[j]);
      s_part[i][j - (i - 1) * M] = result;
    }
    for (int j = i + 1; j <= (n - 1) / M + 1; ++j) {
      add(s[j], result);
    }
  }
  h[1] = 1;
  for (int i = 2; i <= n; ++i) {
    h[i] = (h[i - 1] + mul(i, mul(i, phi[i]))) % mod;
  }
  while (m--) {
    int a, b, k;
    long long x;
    scanf("%d%d%lld%d", &a, &b, &x, &k);
    int d = __gcd(a, b);
    modify(d, (mod - g[d]) % mod);
    modify(d, g[d] = ((long long) x / (a / d) / (b / d)) % mod);
    int answer = 0;
    for (int l = 1, r; l <= k; l = r + 1) {
      r = k / (k / l);
      add(answer, mul((query(r) - query(l - 1) + mod) % mod, h[k / l]));
    }
    printf("%d\n", answer);
  }
  return 0;
}
