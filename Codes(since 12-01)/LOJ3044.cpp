#include<bits/stdc++.h>

using namespace std;

const int N = 234567, mod = 998244353;

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

struct info_t {
  int foo, bar;

  info_t() {
  }

  info_t(int foo, int bar): foo(foo), bar(bar) {
  }
};

info_t merge(info_t a, info_t b) {
  return info_t(mul(a.foo, b.foo), (mul(a.bar, b.foo) + b.bar) % mod);
}

struct number_t {
  int foo, bar;

  number_t() {
    foo = 1;
    bar = 0;
  }

  void multiply(int x) {
    if (!x) {
      ++bar;
    } else {
      foo = mul(foo, x);
    }
  }

  void divide(int x) {
    if (!x) {
      --bar;
    } else {
      foo = mul(foo, qpow(x, mod - 2));
    }
  }

  int get() {
    return bar ? 0 : foo;
  }
};

int n, l, r, tt, w, ch[N][2], father[N], depth[N];
vector<int> adj[N], adds[N];
number_t lightf[N], lightg[N];
info_t f[N], g[N];

bool isroot(int x) {
  int f = father[x];
  return ch[f][0] != x && ch[f][1] != x;
}

int side(int x) {
  int f = father[x];
  return ch[f][1] == x;
}

void pull(int x) {
  f[x] = info_t((mod - lightf[x].get()) % mod, lightf[x].get());
  g[x] = info_t((mod - lightg[x].get()) % mod, lightg[x].get());
  if (ch[x][1]) {
    f[x] = merge(f[ch[x][1]], f[x]);
    g[x] = merge(g[ch[x][1]], g[x]);
  }
  if (ch[x][0]) {
    f[x] = merge(f[x], f[ch[x][0]]);
    g[x] = merge(g[x], g[ch[x][0]]);
  }
}

void rotate(int x) {
  int f = father[x], s = side(x), ano = ch[x][!s], fs = side(f);
  father[x] = father[f];
  if (!isroot(f)) {
    ch[father[f]][fs] = x;
  }
  father[ano] = f;
  ch[f][s] = ano;
  father[f] = x;
  ch[x][!s] = f;
  pull(f);
  pull(x);
}

void splay(int x) {
  for (; !isroot(x); rotate(x)) {
    if (!isroot(father[x])) {
      if (side(x) == side(father[x])) {
        rotate(father[x]);
      } else {
        rotate(x);
      }
    }
  }
}

void access(int x) {
  for (int y = 0; x; y = x, x = father[x]) {
    splay(x);
    if (ch[x][1]) {
      lightf[x].multiply((1 - f[ch[x][1]].bar + mod) % mod);
      lightg[x].multiply((1 - g[ch[x][1]].bar + mod) % mod);
    }
    ch[x][1] = y;
    if (ch[x][1]) {
      lightf[x].divide((1 - f[ch[x][1]].bar + mod) % mod);
      lightg[x].divide((1 - g[ch[x][1]].bar + mod) % mod);
    }
    pull(x);
  }
}

int dfs(int x, int p) {
  father[x] = p;
  depth[x] = depth[p] + 1;
  if (x != 1 && adj[x].size() == 1) {
    ++tt;
    return x;
  } else {
    int result = depth[x] & 1 ? 0 : n + 1;
    for (auto y : adj[x]) {
      if (y != p) {
        if (depth[x] & 1) {
          result = max(result, dfs(y, x));
        } else {
          result = min(result, dfs(y, x));
        }
      }
    }
    return result;
  }
}

void dfs(int x) {
  if (x != 1 && adj[x].size() == 1) {
    int fmul = 0, gmul = 0;
    if (x < w) {
      adds[w + 1 - x].push_back(x);
      if (!(depth[x] & 1)) {
        fmul = gmul = 1;
      }
    } else if (x > w) {
      adds[x - w + 1].push_back(x);
      if (depth[x] & 1) {
        fmul = gmul = 1;
      }
    } else {
      if (depth[x] & 1) {
        gmul = 1;
      } else {
        fmul = 1;
      }
    }
    lightf[father[x]].multiply(fmul);
    lightg[father[x]].multiply(gmul);
  } else {
    for (auto y : adj[x]) {
      if (y != father[x]) {
        dfs(y);
      }
    }
    if (father[x]) {
      lightf[father[x]].multiply((1 - lightf[x].get() + mod) % mod);
      lightg[father[x]].multiply((1 - lightg[x].get() + mod) % mod);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> l >> r;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  w = dfs(1, 0);
  dfs(1);
  int all = qpow(2, tt - 1), last = all;
  if (l == 1) {
    cout << last << " \n"[r == 1];
  }
  for (int i = 2; i <= r; ++i) {
    for (auto x : adds[i]) {
      int y = father[x];
      access(y);
      splay(y);
      if (x + i == w + 1) {
        if (depth[x] & 1) {
          lightf[y].divide(0);
          lightf[y].multiply(mod + 1 >> 1);
        } else {
          lightf[y].divide(1);
          lightf[y].multiply((1 - (mod + 1 >> 1) + mod) % mod);
        }
      } else {
        if (depth[x] & 1) {
          lightg[y].divide(1);
          lightg[y].multiply((1 - (mod + 1 >> 1) + mod) % mod);
        } else {
          lightg[y].divide(0);
          lightg[y].multiply(mod + 1 >> 1);
        }
      }
      pull(y);
    }
    splay(1);
    int now = 2;
    sub(now, mul(f[1].bar, (1 - g[1].bar + mod) % mod));
    now = mul(now, all);
    if (i >= l) {
      if (i == n) {
        cout << ((all + all - 1 - last) % mod + mod) % mod << '\n';
      } else {
        cout << (now - last + mod) % mod << " \n"[i == r];
      }
    }
    last = now;
  }
  return 0;
}
