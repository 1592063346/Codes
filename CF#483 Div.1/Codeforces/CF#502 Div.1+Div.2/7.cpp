#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, inf = 0x3f3f3f3f;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, q, size[N], heavy[N], top[N], dfn[N], depth[N], fa[N], dfn_cnt;
vector<int> graph[N];

void dfs1(int u, int pa) {
  size[u] = 1;
  for (auto v : graph[u]) {
    fa[v] = u;
    depth[v] = depth[u] + 1;
    dfs1(v, u);
    size[u] += size[v];
    if (size[v] > size[heavy[u]]) {
      heavy[u] = v;
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++dfn_cnt;
  if (heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : graph[u]) {
      if (v != heavy[u]) {
        dfs2(v, v);
      }
    }
  }
}

#define lo (o<<1)
#define ro (o<<1|1)

struct state {
  int sum, max_t;

  state () {}
  state (int sum, int max_t): sum(sum), max_t(max_t) {}

  state operator + (const state& a) const {
    state result;
    result.sum = sum + a.sum;
    result.max_t = max(a.max_t, a.sum + max_t);
    return result;
  }
} seg_info_t[N << 2];

int cover_tag[N << 2];

void cover_t(int l, int r, int o, int v) {
  cover_tag[o] = v;
  seg_info_t[o] = state (v * (r - l + 1), v >= 0 ? v * (r - l + 1) : v);
}

void push_down(int l, int r, int o) {
  if (cover_tag[o] != inf) {
    int mid = l + r >> 1;
    cover_t(l, mid, lo, cover_tag[o]);
    cover_t(mid + 1, r, ro, cover_tag[o]);
    cover_tag[o] = inf;
  }
}

void build(int l, int r, int o) {
  if (l == r) {
    seg_info_t[o] = state (-1, -1);
  } else {
    int mid = l + r >> 1;
    build(l, mid, lo);
    build(mid + 1, r, ro);
    seg_info_t[o] = seg_info_t[lo] + seg_info_t[ro];
  }
}

void modify(int l, int r, int o, int ql, int qr, int v) {
  if (ql <= l && r <= qr) {
    cover_t(l, r, o, v);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (ql <= mid) {
      modify(l, mid, lo, ql, qr, v);
    } if (qr > mid) {
      modify(mid + 1, r, ro, ql, qr, v);
    }
    seg_info_t[o] = seg_info_t[lo] + seg_info_t[ro];
  }
}

state query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return seg_info_t[o];
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (qr <= mid) {
      return query(l, mid, lo, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, ro, ql, qr);
    } else {
      return query(l, mid, lo, ql, qr) + query(mid + 1, r, ro, ql, qr);
    }
  }
}

int query(int u) {
  int result = -inf, sumv = 0;
  for (; u; u = fa[top[u]]) {
    int l = dfn[top[u]], r = dfn[u];
    state x = query(1, n, 1, l, r);
    cmax(result, sumv + x.max_t);
    sumv += x.sum;
  }
  return result;
}

void modify_subtree(int u) {
  int x = fa[u] ? query(fa[u]) : 0;
  modify(1, n, 1, dfn[u], dfn[u], min(-x - 1, -1));
  for (auto v : graph[u]) {
    modify(1, n, 1, dfn[v], dfn[v] + size[v] - 1, -1);
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 2; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    graph[x].push_back(i);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  build(1, n, 1);
  memset(cover_tag, 0x3f, sizeof cover_tag);
  for (int i = 1; i <= q; ++i) {
    int type, x;
    scanf("%d%d", &type, &x);
    if (type == 1) {
      int y = query(1, n, 1, dfn[x], dfn[x]).sum;
      modify(1, n, 1, dfn[x], dfn[x], y + 1);
    } else if (type == 2) {
      modify_subtree(x);
    } else {
      printf("%s\n", query(x) >= 0 ? "black" : "white");
    }
  }
  return 0;
}
