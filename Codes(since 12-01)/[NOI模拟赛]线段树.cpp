#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

unordered_map<long long, int> f, g, h;

long long H(long long x) {
  if (h.count(x)) {
    return h[x];
  } else {
    h[x] = (x + 1 >> 1) % mod;
    add(h[x], H(x >> 1));
    add(h[x], H(x + 1 >> 1));
    return h[x];
  }
}

long long G(long long x) {
  if (g.count(x)) {
    return g[x];
  } else {
    g[x] = (x >> 1) % mod;
    add(g[x], G(x >> 1));
    add(g[x], G(x + 1 >> 1));
    return g[x];
  }
}

long long F(long long x) {
  if (f.count(x)) {
    return f[x];
  } else {
    f[x] = (x - 1) % mod;
    add(f[x], F(x >> 1));
    add(f[x], F(x + 1 >> 1));
    add(f[x], mul(H(x + 1 >> 1), (x >> 1) % mod));
    add(f[x], mul(G(x >> 1), (x + 1 >> 1) % mod));
    return f[x];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  f[1] = 1;
  g[1] = h[1] = 0;
  int tt;
  long long n;
  cin >> tt;
  while (tt--) {
    cin >> n;
    cout << F(n) << '\n';
  } 
  return 0;
}
