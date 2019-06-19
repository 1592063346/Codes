#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, m, q, tt, u[N], v[N], ll[N], rr[N], size[N], father[N], depth[N], dfn[N], heavy[N], top[N], answer[N];
vector<int> adj[N];

struct info_t {
  int t, l, foo, bar;

  info_t() {
  }

  info_t(int t, int l, int foo, int bar): t(t), l(l), foo(foo), bar(bar) {
  }

  bool operator < (const info_t& a) const {
    return l < a.l || (l == a.l && t > a.t);
  }
};

namespace segment_t {
int tag[N << 2];

void push(int x) {
  if (tag[x]) {
    tag[x << 1] = tag[x];
    tag[x << 1 | 1] = tag[x];
    tag[x] = 0;
  }
}

void modify(int l, int r, int x, int ql, int qr, int y) {
  if (ql <= l && r <= qr) {
    tag[x] = y;
  } else {
    int mid = l + r >> 1;
    push(x);
    if (ql <= mid) {
      modify(l, mid, x << 1, ql, qr, y);
    }
    if (qr > mid) {
      modify(mid + 1, r, x << 1 | 1, ql, qr, y);
    }
  }
}

int query(int l, int r, int x, int p) {
  if (tag[x] || l == r) {
    return tag[x];
  } else {
    int mid = l + r >> 1;
    push(x);
    if (p <= mid) {
      return query(l, mid, x << 1, p);
    } else {
      return query(mid + 1, r, x << 1 | 1, p);
    }
  }
}
}

namespace bit {
int a[N];

void modify(int x, int y) {
  while (x <= m) {
    a[x] += y;
    x += x & -x;
  }
}

int query(int x) {
  int result = 0;
  while (x) {
    result += a[x];
    x -= x & -x;
  }
  return result;
}
}

void dfs1(int x, int f) {
  size[x] = 1;
  father[x] = f;
  for (auto y : adj[x]) {
    if (y != f) {
      depth[y] = depth[x] + 1;
      dfs1(y, x);
      size[x] += size[y];
      if (size[y] > size[heavy[x]]) {
        heavy[x] = y;
      }
    }
  }
}

void dfs2(int x, int t) {
  dfn[x] = ++tt;
  top[x] = t;
  if (heavy[x]) {
    dfs2(heavy[x], t);
    for (auto y : adj[x]) {
      if (y != father[x] && y != heavy[x]) {
        dfs2(y, y);
      }
    }
  }
}

int get_lca(int x, int y) {
  for (; top[x] != top[y]; x = father[top[x]]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
  }
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  return x;
}

void modify(int x, int y, int z, bool lca = false) {
  for (; top[x] != top[y]; x = father[top[x]]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
    segment_t::modify(1, n, 1, dfn[top[x]], dfn[x], z);
  }
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  segment_t::modify(1, n, 1, dfn[x] + (!lca ? 1 : 0), dfn[y], z);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  for (int i = 1; i <= m; ++i) {
    cin >> u[i] >> v[i];
    int lca = get_lca(u[i], v[i]);
    ll[i] = segment_t::query(1, n, 1, dfn[lca]) + 1;
    modify(u[i], v[i], i);
  }
  memset(segment_t::tag, 0, sizeof segment_t::tag);
  for (int i = m; i; --i) {
    int lca = get_lca(u[i], v[i]);
    rr[i] = segment_t::query(1, n, 1, dfn[lca]);
    if (rr[i]) {
      --rr[i];
    } else {
      rr[i] = m;
    }
    modify(u[i], v[i], i, true);
  }
  vector<info_t> events;
  for (int i = 1; i <= m; ++i) {
    events.emplace_back(1, ll[i], i, rr[i]);
    events.emplace_back(-1, i, i, rr[i]);
  }
  for (int i = 1, l, r; i <= q; ++i) {
    cin >> l >> r;
    events.emplace_back(0, l, r, i);
  }
  sort(events.begin(), events.end());
  for (auto event : events) {
    if (event.t) {
      bit::modify(event.foo, event.t);
      bit::modify(event.bar + 1, -event.t);
    } else {
      answer[event.bar] = bit::query(event.foo);
    }
  }
  for (int i = 1; i <= q; ++i) {
    cout << answer[i] << '\n';
  }
  return 0;
}
