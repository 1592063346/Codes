#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10, mod = 1e9 + 7;

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

void ufmt(int* buffer, int n) {
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        sub(buffer[i + j + k], buffer[j + k]);
      }
    }
  }
}

int n, s[N], f[N][1 << 15], answer[N], all, prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
long long a[N], s1, s2;
vector<int> adj[N];

void dfs(int u, int p) {
  for (int i = 0; i < all; ++i) {
    f[u][i] = 1;
  }
  for (auto v : adj[u]) {
    if (v != p) {
      dfs(v, u);
      int diff = s[u] ^ s[v];
      for (int i = all - 1 ^ diff;; i = i - 1 & (all - 1 ^ diff)) {
        add(f[u][diff | i], mul(f[u][diff | i], f[v][diff | i]));
        if (!i) {
          break;
        }
      }
    }
  }
  for (int i = 0; i < all; ++i) {
    add(answer[i], f[u][i]);
  }
}

int main() {
  scanf("%d%lld%lld", &n, &s1, &s2);
  vector<int> primes;
  for (int i = 0; i < 15; ++i) {
    if (!(s2 % prime[i]) && (s1 % prime[i])) {
      primes.push_back(prime[i]);
    }
  }
  all = 1 << primes.size();
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    for (int j = 0; j < primes.size(); ++j) {
      if (a[i] % primes[j] == 0) {
        s[i] |= 1 << j;
      }
    }
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 0);
  ufmt(answer, all);
  printf("%d\n", answer[all - 1]);
  return 0;
}
