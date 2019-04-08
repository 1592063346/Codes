#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;

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

template<typename T, typename R, const int md>
struct hash_t {
  vector<pair<T, R>> bottle[md];
  R unfound = 0;

  int f(pair<int, int> x) {
    return (x.first * 233ll + x.second) % md;
  }

  void insert(T x, R y) {
    int p = f(x);
    bottle[p].emplace_back(x, y);
  }

  R& operator [] (T x) {
    int p = f(x);
    for (auto& info : bottle[p]) {
      if (info.first == x) {
        return info.second;
      }
    }
    return unfound;
  }
};

int opt, n, m, tt, fac[N], ifac[N], size[N], father[N], ch[N][2], answer = 1;
vector<int> adj[N];
hash_t<pair<int, int>, int, 1000003> id;

int binom(int x, int y) {
  return mul(fac[x], mul(ifac[y], ifac[x - y]));
}

int ibinom(int x, int y) {
  return mul(ifac[x], mul(fac[y], fac[x - y]));
}

int value(int x, int y) {
  return binom(x + y, x);
}

int ivalue(int x, int y) {
  return ibinom(x + y, x);
}

int dfs(int l, int r, int p) {
  int x = ++tt;
  father[x] = p;
  id.insert({l, r}, x);
  size[x] = 0;
  if (l + 1 != r) {
    int mid = adj[l][lower_bound(adj[l].begin(), adj[l].end(), r) - adj[l].begin() - 1];
    ch[x][0] = dfs(l, mid, x);
    ch[x][1] = dfs(mid, r, x);
    size[x] += size[ch[x][0]];
    size[x] += size[ch[x][1]];
    ++size[x];
    answer = mul(answer, value(size[ch[x][0]], size[ch[x][1]]));
  }
  return x;
}

void print(int x, int y) {
  if (opt) {
    printf("%d %d\n", x, y);
  } else {
    printf("%d\n", x);
  }
}

int main() {
  scanf("%d%d", &opt, &n);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  ifac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    ifac[i] = mul(ifac[i + 1], i + 1);
  }
  for (int i = 1; i <= n - 3; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  for (int i = 1; i <= n; ++i) {
    adj[i].push_back(i - 1 == 0 ? n : i - 1);
    adj[i].push_back(i + 1 == n + 1 ? 1 : i + 1);
  }
  for (int i = 1; i <= n; ++i) {
    sort(adj[i].begin(), adj[i].end());
  }
  int all = 0;
  for (int i = 0; i + 1 < adj[n].size(); ++i) {
    int root = dfs(adj[n][i], adj[n][i + 1], 0);
    answer = mul(answer, ifac[size[root]]);
    all += size[root];
  }
  answer = mul(answer, fac[all]);
  int mint = n - 1 - adj[n].size();
  print(mint, answer);
  scanf("%d", &m);
  while (m--) {
    int x, y, z, a = mint, b = answer;
    scanf("%d%d", &x, &y);
    z = id[{x, y}];
    if (!father[z]) {
      b = mul(b, ivalue(size[ch[z][0]], size[ch[z][1]]));
      b = mul(b, fac[size[z]]);
      b = mul(b, ifac[size[ch[z][0]]]);
      b = mul(b, ifac[size[ch[z][1]]]);
      b = mul(b, qpow(a--, mod - 2));
    } else {
      int f = father[z];
      b = mul(b, ivalue(size[ch[z][0]], size[ch[z][1]]));
      b = mul(b, ivalue(size[z], size[ch[f][1]]));
      b = mul(b, value(size[ch[z][1]], size[ch[f][1]]));
      b = mul(b, value(size[ch[z][0]], size[ch[z][1]] + size[ch[f][1]] + 1));
    }
    print(a, b);
  }
  return 0;
}
