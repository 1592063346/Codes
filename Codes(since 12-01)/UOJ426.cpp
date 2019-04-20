#include<bits/stdc++.h>

using namespace std;

const int N = 123456, M = 21;

long long n;
int m, k, sq, scc[M], dfn[M], low[M], sta[M], ways[M], pre[M], top, dfn_cnt, scc_cnt;
unsigned int dp[M][1 << M];
vector<int> adj[M], primes;

class my_array {
 public:
  unsigned int a[N << 1];

  unsigned int& operator [] (long long x) {
    return x <= sq ? a[x] : a[sq + n / x];
  }
};

my_array g0, f;

void tarjan(int u) {
  dfn[u] = low[u] = dfn_cnt++;
  sta[++top] = u;
  for (auto v : adj[u]) {
    if (!~dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (!~scc[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    while (1) {
      int x = sta[top--];
      scc[x] = scc_cnt;
      if (x == u) {
        break;
      }
    }
    ++scc_cnt;
  }
}

vector<unsigned int> get_binom(long long all) {
  vector<unsigned int> result(m + 1);
  if (all == 1) {
    result[0] = result[1] = 1;
  } else {
    vector<unsigned int> p = get_binom(all >> 1);
    for (int i = 0; i <= m; ++i) {
      for (int j = 0; i + j <= m; ++j) {
        result[i + j] += p[i] * p[j];
      }
    }
    if (all & 1) {
      for (int i = m; i; --i) {
        result[i] += result[i - 1];
      }
    }
  }
  return result;
}

unsigned int get_ways(long long all) {
  vector<unsigned int> binom = get_binom(all);
  unsigned int result = 0;
  for (int i = 1; i <= m; ++i) {
    result += ways[i] * binom[i];
  }
  return result;
}

void sieve(int n) {
  vector<bool> is_prime(n + 1, true);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
    for (auto x : primes) {
      if (i * x > n) {
        break;
      }
      is_prime[i * x] = false;
      if (i % x == 0) {
        break;
      }
    }
  }
}

unsigned int powerf(int c) {
  return 81 * c * c - 27 * c + 9;
}

void min_25_sieve() {
  vector<long long> values;
  for (long long i = 1; i <= n; i = n / (n / i) + 1) {
    values.push_back(n / i);
  }
  for (auto x : values) {
    g0[x] = (x - 1) % (1ll << 32);
  }
  for (auto p : primes) {
    for (auto x : values) {
      if (x < (long long) p * p) {
        break;
      }
      g0[x] -= g0[x / p] - g0[p - 1];
    }
  }
  for (auto x : values) {
    f[x] = (g0[x] *= 63);
  }
  reverse(primes.begin(), primes.end());
  for (auto p : primes) {
    for (auto x : values) {
      if (x < (long long) p * p) {
        break;
      }
      long long q = p;
      for (int j = 1; q * p <= x; ++j, q *= p) {
        f[x] += powerf(j) * (f[x / q] - g0[p]) + powerf(j + 1);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> m >> n >> k;
  sq = sqrt(n);
  sq = max(sq, 2);
  sieve(sq);
  for (int i = 0, x, y; i < k; ++i) {
    cin >> x >> y;
    --x;
    --y;
    adj[y].push_back(x);
  }
  for (int i = 0; i < m; ++i) {
    dfn[i] = low[i] = scc[i] = -1;
  }
  for (int i = 0; i < m; ++i) {
    if (!~dfn[i]) {
      tarjan(i);
    }
  }
  for (int i = 0; i < m; ++i) {
    for (auto j : adj[i]) {
      if (scc[i] != scc[j]) {
        pre[scc[i]] |= 1 << scc[j];
      }
    }
  }
  m = scc_cnt;
  dp[0][0] = 1;
  for (int colors = 1; colors <= m; ++colors) {
    for (int i = 0; i < m; ++i) {
      memset(dp[i + 1], 0, sizeof dp[i + 1]);
      for (int j = 0; j < 1 << m + 1; ++j) {
        dp[i + 1][j] += dp[i][j];
        if (!(j >> i & 1) && (j & pre[i]) == pre[i]) {
          dp[i + 1][j | 1 << i | 1 << m] += dp[i][j];
        }
      }
    }
    ways[colors] = dp[m][(1 << m + 1) - 1];
    for (int i = 0; i < 1 << m; ++i) {
      dp[0][i] = dp[m][i | 1 << m];
    }
  }
  min_25_sieve();
  unsigned int answer = get_ways(n);
  for (long long i = 1; i <= n; i = n / (n / i) + 1) {
    long long j = n / (n / i);
    answer += get_ways(n / i) * (f[j] - f[i - 1]);
  }
  cout << answer << '\n';
  return 0;
}
