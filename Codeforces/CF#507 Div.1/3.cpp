#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

int n, m, k, f[N];
long long value[N];
map<long long, vector<pair<int, int> > > s;

int find(int x) {
  return f[x] == x ? x : f[x] = find(f[x]);
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%I64d", &value[i]);
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    long long diff = value[u] ^ value[v];
    s[diff].emplace_back(u, v);
  }
  int total = qpow(2, n), ans = mul(total, ((1ll << k) - s.size()) % mod);
  for (map<long long, vector<pair<int, int> > >:: iterator it = s.begin(); it != s.end(); ++it) {
    int nodes = 0;
    for (auto v : it->second) {
      if (f[v.first] ^ v.first) {
        f[v.first] = v.first;
        ++nodes;
      }
      if (f[v.second] ^ v.second) {
        f[v.second] = v.second;
        ++nodes;
      }
    }
    int other = n - nodes;
    for (auto v : it->second) {
      if (find(v.first) ^ find(v.second)) {
        f[find(v.first)] = find(v.second);
        --nodes;
      }
    }
    add(ans, qpow(2, other + nodes));
    for (auto v : it->second) {
      f[v.first] = f[v.second] = 0;
    }
  }
  printf("%d\n", ans);
  return 0;
}
