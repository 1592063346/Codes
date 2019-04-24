#include<bits/stdc++.h>

using namespace std;

const int N = 123456, C = 36, mod = 998244353;

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

int qpow(int x, int y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

int tt, n, m, mu[N], phi[N], f[N];
vector<int> primes, g[N], pres[C + 5][C + 5];

void init(int n) {
  vector<bool> is_prime(n + 1, true);
  phi[1] = mu[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      mu[i] = mod - 1;
      phi[i] = i - 1;
    }
    for (auto p : primes) {
      if (i * p > n) {
        break;
      }
      is_prime[i * p] = false;
      if (i % p == 0) {
        mu[i * p] = 0;
        phi[i * p] = phi[i] * p;
      } else {
        mu[i * p] = (mod - mu[i]) % mod;
        phi[i * p] = phi[i] * phi[p];
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    int foo = mul(i, qpow(phi[i], mod - 2));
    for (int j = i; j <= n; j += i) {
      add(f[j], mul(foo, mu[j / i]));
    }
  }
  for (int i = 1; i <= n; ++i) {
    g[i].resize(n / i + 1);
    for (int j = 1; j * i <= n; ++j) {
      g[i][j] = (g[i][j - 1] + phi[j * i]) % mod;
    }
  }
  for (int i = 1; i <= C; ++i) {
    for (int j = 1; j <= C; ++j) {
      pres[i][j].resize(n / max(i, j) + 1);
      for (int k = 1; k * max(i, j) <= n; ++k) {
        pres[i][j][k] = (pres[i][j][k - 1] + mul(f[k], mul(g[k][i], g[k][j]))) % mod;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  init(1e5);
  cin >> tt;
  while (tt--) {
    cin >> n >> m;
    int answer = 0;
    for (int i = 1; i <= max(n, m) / C; ++i) {
      add(answer, mul(f[i], mul(g[i][n / i], g[i][m / i])));
    }
    for (int i = max(n, m) / C + 1, j; i <= min(n, m); i = j + 1) {
      j = min(n / (n / i), m / (m / i));
      add(answer, (pres[n / i][m / i][j] - pres[n / i][m / i][i - 1] + mod) % mod);
    }
    cout << answer << '\n';
  }
  return 0;
}
