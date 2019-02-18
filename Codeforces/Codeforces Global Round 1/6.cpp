#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;
const long long inf = 1e18;

void cmin(long long& x, long long y) {
  if (x > y) {
    x = y;
  }
}

int n, q, w[N], dfn[N], adfn[N], edfn[N], dfn_cnt;
vector<int> graph[N];
vector<pair<int, pair<int, int>>> queries[N];
long long d[N], minv[N << 2], addv[N << 2], answer[N];

void dfs(int u) {
  dfn[u] = ++dfn_cnt;
  adfn[dfn_cnt] = u;
  for (auto v : graph[u]) {
    dfs(v);
  }
  edfn[u] = dfn_cnt;
}

#define lo (o<<1)
#define ro (o<<1|1)

void build(int l, int r, int o) {
  if (l == r) {
    int u = adfn[l];
    minv[o] = graph[u].size() ? inf : d[u];
  } else {
    int mid = l + r >> 1;
    build(l, mid, lo);
    build(mid + 1, r, ro);
    minv[o] = min(minv[lo], minv[ro]);
  }
}

void add(int o, long long v) {
  minv[o] += v;
  addv[o] += v;
}

void push_down(int o) {
  if (addv[o]) {
    add(lo, addv[o]);
    add(ro, addv[o]);
    addv[o] = 0;
  }
}

void modify(int l, int r, int o, int ql, int qr, long long v) {
  if (ql <= l && r <= qr) {
    add(o, v);
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (ql <= mid) {
      modify(l, mid, lo, ql, qr, v);
    }
    if (qr > mid) {
      modify(mid + 1, r, ro, ql, qr, v);
    }
    minv[o] = min(minv[lo], minv[ro]);
  }
}

long long query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return minv[o];
  } else {
    int mid = l + r >> 1;
    long long result = inf;
    push_down(o);
    if (ql <= mid) {
      cmin(result, query(l, mid, lo, ql, qr));
    }
    if (qr > mid) {
      cmin(result, query(mid + 1, r, ro, ql, qr));
    }
    return result;
  }
}

void solve(int u) {
  modify(1, n, 1, dfn[u], edfn[u], -w[u] << 1);
  for (auto que : queries[u]) {
    answer[que.first] = d[u] + query(1, n, 1, que.second.first, que.second.second);
  }
  for (auto v : graph[u]) {
    solve(v);
  }
  modify(1, n, 1, dfn[u], edfn[u], w[u] << 1);
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 2; i <= n; ++i) {
    int p;
    scanf("%d%d", &p, &w[i]);
    graph[p].push_back(i);
    d[i] = d[p] + w[i];
  }
  for (int i = 1; i <= n; ++i) {
    sort(graph[i].begin(), graph[i].end());
  }
  dfs(1);
  build(1, n, 1);
  for (int i = 1; i <= q; ++i) {
    int u, l, r;
    scanf("%d%d%d", &u, &l, &r);
    queries[u].emplace_back(i, pair<int, int>(l, r));
  }
  solve(1);
  for (int i = 1; i <= q; ++i) {
    printf("%lld\n", answer[i]);
  }
  return 0;
}
