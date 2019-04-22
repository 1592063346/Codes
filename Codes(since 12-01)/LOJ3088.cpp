#include<bits/stdc++.h>

using namespace std;

const int N = 56789, mod = 998244353;

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

int n, q, k, tt, size[N], father[N], top[N], heavy[N], depth[N], dfn[N], adfn[N], answer[N];
vector<int> adj[N];

void dfs1(int u, int p) {
  size[u] = 1;
  father[u] = p;
  heavy[u] = -1;
  for (auto v : adj[u]) {
    if (v != p) {
      depth[v] = depth[u] + 1;
      dfs1(v, u);
      size[u] += size[v];
      if (!~heavy[u] || size[v] > size[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = tt;
  adfn[tt++] = u;
  if (~heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : adj[u]) {
      if (v != father[u] && v != heavy[u]) {
        dfs2(v, v);
      }
    }
  }
}

class segment_t {
 public:
  int n, value[N << 2], sum[N << 2], lazy[N << 2];

  segment_t(int n, vector<int> values): n(n) {
    init(0, n - 1, 1, values);
  }

  void addt(int o, int x) {
    add(sum[o], mul(value[o], x));
    add(lazy[o], x);
  }

  void pull(int o) {
    sum[o] = (sum[o << 1] + sum[o << 1 | 1]) % mod;
  }

  void push(int o) {
    if (lazy[o]) {
      addt(o << 1, lazy[o]);
      addt(o << 1 | 1, lazy[o]);
      lazy[o] = 0;
    }
  }

  void init(int l, int r, int o, vector<int>& values) {
    sum[o] = lazy[o] = 0;
    if (l == r) {
      value[o] = values[l];
    } else {
      int mid = l + r >> 1;
      init(l, mid, o << 1, values);
      init(mid + 1, r, o << 1 | 1, values);
      value[o] = (value[o << 1] + value[o << 1 | 1]) % mod;
    }
  }

  void modify(int l, int r, int o, int ql, int qr, int x) {
    if (ql <= l && r <= qr) {
      addt(o, x);
    } else {
      int mid = l + r >> 1;
      push(o);
      if (qr <= mid) {
        modify(l, mid, o << 1, ql, qr, x);
      } else if (ql > mid) {
        modify(mid + 1, r, o << 1 | 1, ql, qr, x);
      } else {
        modify(l, mid, o << 1, ql, qr, x);
        modify(mid + 1, r, o << 1 | 1, ql, qr, x);
      }
      pull(o);
    }
  }

  int query(int l, int r, int o, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return sum[o];
    } else {
      int mid = l + r >> 1;
      push(o);
      if (qr <= mid) {
        return query(l, mid, o << 1, ql, qr);
      } else if (ql > mid) {
        return query(mid + 1, r, o << 1 | 1, ql, qr);
      } else {
        return (query(l, mid, o << 1, ql, qr) + query(mid + 1, r, o << 1 | 1, ql, qr)) % mod;
      }
    }
  }

  void modify(int ql, int qr, int x) {
    modify(0, n - 1, 1, ql, qr, x);
  }

  int query(int ql, int qr) {
    return query(0, n - 1, 1, ql, qr);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q >> k;
  for (int i = 1, x; i < n; ++i) {
    cin >> x;
    --x;
    adj[x].push_back(i);
    adj[i].push_back(x);
  }
  depth[0] = 1;
  dfs1(0, -1);
  dfs2(0, 0);
  vector<int> values(n);
  for (int i = 0; i < n; ++i) {
    int x = adfn[i];
    values[i] = (qpow(depth[x], k) - qpow(depth[x] - 1, k) + mod) % mod;
  }
  segment_t tree(n, values);
  vector<pair<pair<int, int>, int>> queries(q);
  for (int i = 0; i < q; ++i) {
    cin >> queries[i].first.first >> queries[i].first.second;
    --queries[i].first.first;
    --queries[i].first.second;
    queries[i].second = i;
  }
  sort(queries.begin(), queries.end());
  int now = -1;
  for (auto query : queries) {
    while (now < query.first.first) {
      ++now;
      for (int x = now; ~x; x = father[top[x]]) {
        tree.modify(dfn[top[x]], dfn[x], 1);
      }
    }
    for (int x = query.first.second; ~x; x = father[top[x]]) {
      add(answer[query.second], tree.query(dfn[top[x]], dfn[x]));
    }
  }
  for (int i = 0; i < q; ++i) {
    cout << answer[i] << '\n';
  }
  return 0;
}
