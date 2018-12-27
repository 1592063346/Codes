#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, max_value = 1e7, mod = 1e9 + 7;

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

struct info_t {
  int u, v, x, id;

  info_t () {}
  info_t (int u, int v, int x, int id): u(u), v(v), x(x), id(id) {}
};

int n, q, a[N], answer[N], size[N], heavy[N], depth[N], father[N], top[N], dfn[N], dfn_cnt, sum[N << 2];
bool is_prime[max_value + 10];
vector<int> graph[N], primes, nodes[max_value + 10];
vector<info_t> que[max_value + 10];

void sieve(int m) {
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i <= m; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
    for (auto v : primes) {
      int d = i * v;
      if (d > m) {
        break;
      }
      is_prime[d] = false;
      if (i % v == 0) {
        break;
      }
    }
  }
}

void dfs1(int u, int pa) {
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v != pa) {
      depth[v] = depth[u] + 1;
      father[v] = u;
      dfs1(v, u);
      size[u] += size[v];
      if (size[v] > size[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
}

void dfs2(int u, int t) {
  dfn[u] = ++dfn_cnt;
  top[u] = t;
  if (heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : graph[u]) {
      if (v != heavy[u] && v != father[u]) {
        dfs2(v, v);
      }
    }
  }
}

#define lo (o<<1)
#define ro (o<<1|1)

void modify(int l, int r, int o, int p, int v, bool cover = false) {
  if (l == r) {
    if (cover) {
      sum[o] = v;
    } else {
      sum[o] += v;
    }
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, lo, p, v, cover);
    } else {
      modify(mid + 1, r, ro, p, v, cover);
    }
    sum[o] = sum[lo] + sum[ro];
  }
}

int query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return sum[o];
  } else {
    int mid = l + r >> 1, result = 0;
    if (ql <= mid) {
      result += query(l, mid, lo, ql, qr);
    } if (qr > mid) {
      result += query(mid + 1, r, ro, ql, qr);
    }
    return result;
  }
}

int query(int u, int v) {
  int result = 0;
  for (; top[u] != top[v]; u = father[top[u]]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    }
    result += query(1, n, 1, dfn[top[u]], dfn[u]);
  }
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  result += query(1, n, 1, dfn[u], dfn[v]);
  return result;
}

void solve(int value) {
  for (long long i = value; i <= max_value; i *= value) {
    for (auto v : nodes[value]) {
      if (a[v] % i == 0) {
        modify(1, n, 1, dfn[v], 1);
      }
    }
    for (auto v : que[value]) {
      if (v.x % i == 0 && v.x % ((long long) i * value) != 0) {
        answer[v.id] = mul(answer[v.id], qpow(value, query(v.u, v.v)));
      }
    }
  }
  for (auto v : nodes[value]) {
    modify(1, n, 1, dfn[v], 0, true);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  sieve(max_value);
  for (int i = 1; i <= n; ++i) {
    int x = a[i];
    for (auto v : primes) {
      if (v * v > x) {
        break;
      }
      if (x % v == 0) {
        nodes[v].push_back(i);
        while (x % v == 0) {
          x /= v;
        }
      }
    }
    if (x != 1) {
      nodes[x].push_back(i);
    }
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    int a, b, w;
    scanf("%d%d%d", &a, &b, &w);
    answer[i] = 1;
    int x = w;
    for (auto v : primes) {
      if (v * v > x) {
        break;
      }
      if (x % v == 0) {
        que[v].emplace_back(a, b, w, i);
        while (x % v == 0) {
          x /= v;
        }
      }
    }
    if (x != 1) {
      que[x].emplace_back(a, b, w, i);
    }
  }
  for (auto v : primes) {
    if (que[v].size()) {
      solve(v);
    }
  }
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
