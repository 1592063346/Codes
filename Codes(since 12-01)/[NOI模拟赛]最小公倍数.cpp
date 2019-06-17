#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, M = 1e7 + 10, mod = 998244353;

int mul(int x, int y) {
  return (long long) x * y % mod;
}

struct node_t {
  int l, r, x;

  node_t() {
    l = r = 0;
    x = 1;
  }
} node[N * 600];

int n, t, q, tt, dfn_t, node_cnt, a[N], inv[M], size[N], root[N], min_p[M], h[N * 30], dfn[N], adfn[N], first[N], depth[N], log_v[N << 1];
vector<int> adj[N], foo[N], nodes[N];
pair<int, int> rmq_t[20][N << 1];
set<int> bar[N * 30];
bool is_prime[M];

void sieve() {
  vector<int> primes;
  fill(is_prime + 1, is_prime + M, true);
  for (int i = 2; i < M; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      min_p[i] = i;
    }
    for (auto x : primes) {
      if (i * x >= M) {
        break;
      }
      is_prime[i * x] = false;
      min_p[i * x] = min(min_p[i], x);
      if (i % x == 0) {
        break;
      }
    }
  }
}

vector<int> divide(int x) {
  vector<int> result;
  while (x != 1) {
    int y = 1, z = min_p[x];
    while (x % z == 0) {
      result.push_back(y *= z);
      x /= z;
    }
  }
  return result;
}

void dfs(int x, int f) {
  nodes[depth[x]].push_back(x);
  first[x] = ++tt;
  dfn[x] = ++dfn_t;
  adfn[dfn_t] = x;
  size[x] = 1;
  rmq_t[0][tt] = pair<int, int>(depth[x], x);
  for (auto y : adj[x]) {
    if (y != f) {
      depth[y] = depth[x] + 1;
      dfs(y, x);
      size[x] += size[y];
      rmq_t[0][++tt] = pair<int, int>(depth[x], x);
    }
  }
}

int get_lca(int x, int y) {
  x = first[x];
  y = first[y];
  if (x > y) {
    swap(x, y);
  }
  int k = log_v[y - x + 1];
  return min(rmq_t[k][x], rmq_t[k][y - (1 << k) + 1]).second;
}

int modify(int l, int r, int x, int y, int z) {
  int p = ++node_cnt;
  node[p] = node[x];
  node[p].x = mul(node[p].x, z);
  if (l != r) {
    int mid = l + r >> 1;
    if (y <= mid) {
      node[p].l = modify(l, mid, node[x].l, y, z);
    } else {
      node[p].r = modify(mid + 1, r, node[x].r, y, z);
    }
  }
  return p;
}

int query(int l, int r, int x, int ql, int qr) {
  if (!x) {
    return 1;
  }
  if (ql <= l && r <= qr) {
    return node[x].x;
  } else {
    int mid = l + r >> 1, result = 1;
    if (ql <= mid) {
      result = mul(result, query(l, mid, node[x].l, ql, qr));
    }
    if (qr > mid) {
      result = mul(result, query(mid + 1, r, node[x].r, ql, qr));
    }
    return result;
  }
}

void update(int& troot, int x, int y, int z, bool op = false) {
  int lca = get_lca(x, y);
  troot = modify(1, n, troot, dfn[lca], op ? z : inv[z]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  sieve();
  inv[1] = 1;
  for (int i = 2; i < M; ++i) {
    inv[i] = mul(mod - mod / i, inv[mod % i]);
  }
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    foo[i] = divide(a[i]);
    for (auto x : foo[i]) {
      h[++t] = x;
    }
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  for (int i = 1; i <= n; ++i) {
    for (auto& x : foo[i]) {
      x = lower_bound(h + 1, h + 1 + t, x) - h;
    }
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  depth[1] = 1;
  dfs(1, 0);
  for (int i = 2; i <= tt; ++i) {
    log_v[i] = log_v[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= tt; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= tt; ++j) {
      rmq_t[i][j] = min(rmq_t[i - 1][j], rmq_t[i - 1][j + (1 << i - 1)]);
    }
  }
  for (int d = 1; d <= n; ++d) {
    root[d] = root[d - 1];
    for (auto x : nodes[d]) {
      for (auto y : foo[x]) {
        int z = min_p[h[y]];
        bar[y].insert(dfn[x]);
        root[d] = modify(1, n, root[d], dfn[x], z);
        int l = 0, r = 0;
        set<int>::iterator ll = bar[y].find(dfn[x]), rr = ll;
        ++rr;
        if (ll != bar[y].begin()) {
          l = adfn[*--ll];
        }
        if (rr != bar[y].end()) {
          r = adfn[*rr];
        }
        if (l && r) {
          update(root[d], l, r, z, true);
        }
        if (l) {
          update(root[d], l, x, z);
        }
        if (r) {
          update(root[d], x, r, z);
        }
      }
    }
  }
  int last_answer = 0;
  while (q--) {
    int x, y;
    cin >> x >> y;
    x ^= last_answer;
    y ^= last_answer;
    int d = min(depth[x] + y, n);
    cout << (last_answer = query(1, n, root[d], dfn[x], dfn[x] + size[x] - 1)) << '\n';
  }
  return 0;
}
