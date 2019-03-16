#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, q, all, a[N], root[N], h[N], p1[N], p2[N], size[N], dfn[N], father[20][N], adfn[N], d[N], node_cnt, dfn_cnt, number[N], minv[N << 2], maxv[N << 2], answer[N * 5];
vector<int> adj[N];
vector<pair<int, int>> mem, queries[N];

struct point_t {
  int x, y, number;

  point_t() {}
  point_t(int x, int y, int number): x(x), y(y), number(number) {}

  bool operator < (const point_t& a) const {
    return x < a.x;
  }
} points[N * 80];

struct node_t {
  int l, r, tag;

  node_t() {}
  node_t(int l, int r, int tag): l(l), r(r), tag(tag) {}
} nodes[N * 150];

void add(int p, int v) {
  for (; p; p -= p & -p) {
    number[p] += v;
  }
}

int query(int p) {
  int result = 0;
  for (; p <= n + 1; p += p & -p) {
    result += number[p];
  }
  return result;
}

void pull(int o) {
  int v;
  if (v = nodes[o].tag) {
    if (nodes[o].l) {
      nodes[nodes[o].l].tag += v;
    }
    if (nodes[o].r) {
      nodes[nodes[o].r].tag += v;
    }
    nodes[o].tag = 0;
  }
}

void insert(int l, int r, int& o, int p) {
  if (!o) {
    o = ++node_cnt;
  }
  if (l != r) {
    int mid = l + r >> 1;
    pull(o);
    if (p <= mid) {
      insert(l, mid, nodes[o].l, p);
    } else {
      insert(mid + 1, r, nodes[o].r, p);
    }
  }
}

pair<int, int> query_max(int l, int r, int o, int p) {
  if (l == r) {
    int result = nodes[o].tag;
    nodes[o].tag = 0;
    return {l, result};
  } else {
    int mid = l + r >> 1;
    pair<int, int> result = {-1, -1};
    pull(o);
    if (p > mid && nodes[o].r) {
      result = query_max(mid + 1, r, nodes[o].r, p);
    }
    if (!~result.first && nodes[o].l) {
      result = query_max(l, mid, nodes[o].l, p);
    }
    return result;
  }
}

int query_min(int l, int r, int o, int p) {
  if (l == r) {
    return l;
  } else {
    int mid = l + r >> 1, result = -1;
    pull(o);
    if (p <= mid && nodes[o].l) {
      result = query_min(l, mid, nodes[o].l, p);
    }
    if (!~result && nodes[o].r) {
      result = query_min(mid + 1, r, nodes[o].r, p);
    }
    return result;
  }
}

void query(int l, int r, int o) {
  if (l == r) {
    mem.emplace_back(l, nodes[o].tag);
  } else {
    int mid = l + r >> 1;
    pull(o);
    if (nodes[o].l) {
      query(l, mid, nodes[o].l);
    }
    if (nodes[o].r) {
      query(mid + 1, r, nodes[o].r);
    }
  }
}

void dfs(int u, int p) {
  dfn[u] = ++dfn_cnt;
  adfn[dfn_cnt] = u;
  size[u] = 1;
  insert(0, n + 1, root[u], 0);
  insert(0, n + 1, root[u], n + 1);
  insert(0, n + 1, root[u], u);
  for (int i = 1; (1 << i) <= n; ++i) {
    father[i][u] = father[i - 1][father[i - 1][u]];
  }
  for (auto v : adj[u]) {
    if (v != p) {
      d[v] = d[u] + 1;
      father[0][v] = u;
      dfs(v, u);
      if (size[v] > size[u]) {
        swap(size[u], size[v]);
        swap(root[u], root[v]);
      }
      size[u] += size[v];
      mem.clear();
      query(0, n + 1, root[v]);
      for (int i = 0; i + 1 < mem.size(); ++i) {
        int a = mem[i].first, b = mem[i].second;
        points[++all] = point_t(a, mem[i + 1].first, b);
        if (i > 0) {
          pair<int, int> x = query_max(0, n + 1, root[u], a);
          int y = query_min(0, n + 1, root[u], a);
          points[++all] = point_t(x.first, y, x.second);
          insert(0, n + 1, root[u], a);
        }
      }
    }
  }
  ++nodes[root[u]].tag;
}

int get_lca(int u, int v) {
  if (d[u] < d[v]) {
    swap(u, v);
  }
  for (int i = 18; ~i; --i) {
    if (d[u] - (1 << i) >= d[v]) {
      u = father[i][u];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 15; ~i; --i) {
    if (father[i][u] != father[i][v]) {
      u = father[i][u];
      v = father[i][v];
    }
  }
  return father[0][u];
}

void push(int o) {
  minv[o] = min(minv[o << 1], minv[o << 1 | 1]);
  maxv[o] = max(maxv[o << 1], maxv[o << 1 | 1]);
}

void build(int l, int r, int o) {
  if (l == r) {
    minv[o] = maxv[o] = dfn[l];
  } else {
    int mid = l + r >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
    push(o);
  }
}

pair<int, int> query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return {minv[o], maxv[o]};
  } else {
    int mid = l + r >> 1;
    if (qr <= mid) {
      return query(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      pair<int, int> x = query(l, mid, o << 1, ql, qr);
      pair<int, int> y = query(mid + 1, r, o << 1 | 1, ql, qr);
      return {min(x.first, y.first), max(x.second, y.second)};
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    p1[i] = i;
    h[i] = a[i];
  }
  sort(h + 1, h + 1 + n);
  sort(p1 + 1, p1 + 1 + n, [&] (const int& x, const int& y) {
    return a[x] < a[y];
  });
  for (int i = 1; i <= n; ++i) {
    p2[p1[i]] = i;
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    u = p2[u];
    v = p2[v];
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 0);
  mem.clear();
  query(0, n + 1, root[1]);
  for (int i = 0; i + 1 < mem.size(); ++i) {
    points[++all] = point_t(mem[i].first, mem[i + 1].first, mem[i].second);
  }
  build(1, n, 1);
  for (int i = 1; i <= q; ++i) {
    int l, r;
    cin >> l >> r;
    l = lower_bound(h + 1, h + 1 + n, l) - h;
    r = upper_bound(h + 1, h + 1 + n, r) - h - 1;
    queries[l].emplace_back(r, i);
    if (l <= r) {
      pair<int, int> node = query(1, n, 1, l, r);
      answer[i] -= d[get_lca(adfn[node.first], adfn[node.second])];
    }
  }
  sort(points + 1, points + 1 + all);
  for (int i = 0, j = 1; i <= n + 1; ++i) {
    for (auto que : queries[i]) {
      answer[que.second] += n - query(que.first + 1);
    }
    for (; j <= all && points[j].x <= i; ++j) {
      add(points[j].y, points[j].number);
    }
  }
  for (int i = 1; i <= q; ++i) {
    cout << answer[i] << "\n";
  }
  return 0;
}
