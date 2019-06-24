#include<bits/stdc++.h>

using namespace std;

const int N = 123456, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

namespace divide {
long long mul(long long x, long long y, long long md) {
  return ((x * y - (long long) (((long double) x * y + 0.5) / md) * md) % md + md) % md;
}

long long qpow(long long x, long long y, long long md) {
  long long result = 1;
  for (; y; y >>= 1, x = mul(x, x, md)) {
    if (y & 1) {
      result = mul(result, x, md);
    }
  }
  return result;
}

long long randll() {
  return ((long long) rand() << 30) | ((long long) rand() << 15) | rand();
}

bool miller_rabin(long long n) {
  if (n == 2) {
    return true;
  } else if (n < 2 || !(n & 1)) {
    return false;
  }
  long long m = n - 1;
  int t = 0;
  while (!(m & 1)) {
    m >>= 1;
    ++t;
  }
  for (int times = 0; times < 10; ++times) {
    long long a = randll() % (n - 1) + 1, x = qpow(a, m, n), y;
    for (int i = 0; i < t; ++i, x = y) {
      if ((y = mul(x, x, n)) == 1 && x != 1 && x != n - 1) {
        return false;
      }
    }
    if (x != 1) {
      return false;
    }
  }
  return true;
}

long long pollard_rho(long long n) {
  long long k = 2, x = randll() % n, y = x, c = randll() % (n - 1), p = 1;
  for (int i = 1; p == 1; ++i) {
    x = (mul(x, x, n) + c) % n;
    p = __gcd(abs(x - y), n);
    if (i == k) {
      k <<= 1;
      y = x;
    }
  }
  return p;
}

void solve(long long n, vector<long long>& factor) {
  if (n == 1) {
    return;
  } else if (miller_rabin(n)) {
    factor.push_back(n);
    return;
  }
  long long x = n;
  while (x == n) {
    x = pollard_rho(x);
  }
  solve(x, factor);
  solve(n / x, factor);
}

vector<long long> solve(long long n) {
  vector<long long> result;
  solve(n, result);
  sort(result.begin(), result.end());
  return result;
}
}

using divide::solve;

int n, tt, half, base[N], value[N], answer[N], sum[N];
long long a[N], prime[N];
vector<int> adj[N];
map<long long, int> id, power;

void modify(int d, int s, int t, int x) {
  if (d == tt) {
    t += s % base[half];
    add(sum[t], x);
  } else {
    for (int i = 0, j = s % base[d + 1] / base[d]; i <= j; ++i) {
      modify(d + 1, s, t + i * base[d], x);
    }
  }
}

int find(int d, int s, int t) {
  if (d == half) {
    t += s / base[half] * base[half];
    return sum[t];
  } else {
    int result = 0;
    for (int i = s % base[d + 1] / base[d]; i <= power[prime[d]]; ++i) {
      add(result, find(d + 1, s, t + i * base[d]));
    }
    return result;
  }
}

void dfs(int x, int f) {
  if (x == 1) {
    answer[x] = 1;
  } else {
    answer[x] = find(0, value[x], 0);
  }
  modify(half, value[x], 0, answer[x]);
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
    }
  }
  modify(half, value[x], 0, (mod - answer[x]) % mod);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  vector<long long> factor = solve(a[1]);
  for (auto x : factor) {
    ++power[x];
    if (!id.count(x)) {
      prime[id[x] = tt++] = x;
    }
  }
  base[0] = 1;
  for (auto p : power) {
    base[id[p.first] + 1] = base[id[p.first]] * (p.second + 1);
    if (base[id[p.first] + 1] > 500 && !half) {
      half = id[p.first] + 1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    long long x = a[i];
    for (auto p : power) {
      int t = 0;
      while (x % p.first == 0) {
        x /= p.first;
        ++t;
      }
      value[i] += base[id[p.first]] * t;
    }
  }
  dfs(1, 0);
  for (int i = 1; i <= n; ++i) {
    cout << answer[i] << '\n';
  }
  return 0;
}
