#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10;

int n, q, tt, p[N], pos[N], depth[N], firstp[N], logv[N], rmq_d[N][20], rmq_p[N][20];
vector<int> graph[N];
pair<int, int> nodes[N << 2];

void dfs(int u, int father) {
  ++tt;
  firstp[u] = tt;
  rmq_p[tt][0] = u;
  rmq_d[tt][0] = depth[u];
  for (auto v : graph[u]) {
    if (v != father) {
      depth[v] = depth[u] + 1;
      dfs(v, u);
      ++tt;
      rmq_p[tt][0] = u;
      rmq_d[tt][0] = depth[u];
    }
  }
}

void rmq_init() {
  for (int i = 2; i <= tt; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int j = 1; (1 << j) <= tt; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= tt; ++i) {
      int dl = rmq_d[i][j - 1];
      int dr = rmq_d[i + (1 << j - 1)][j - 1];
      rmq_d[i][j] = min(dl, dr);
      rmq_p[i][j] = dl < dr ? rmq_p[i][j - 1] : rmq_p[i + (1 << j - 1)][j - 1];
    }
  }
}

int getlca(int u, int v) {
  u = firstp[u];
  v = firstp[v];
  if (u > v) {
    swap(u, v);
  }
  int k = logv[v - u + 1];
  return rmq_d[u][k] < rmq_d[v - (1 << k) + 1][k] ? rmq_p[u][k] : rmq_p[v - (1 << k) + 1][k];
}

#define lo (o<<1)
#define ro (o<<1|1)

bool including(int u, int v, int a, int b) {
  int lca = getlca(u, v);
  if ((getlca(a, u) != a && getlca(a, v) != a) || getlca(a, lca) != lca) {
    return false;
  }
  if ((getlca(b, u) != b && getlca(b, v) != b) || getlca(b, lca) != lca) {
    return false;
  }
  return true;
}

pair<int, int> operator + (const pair<int, int>& a, const pair<int, int>& b) {
  if (!~a.first || !~b.first) {
    return {-1, -1};
  }
  if (including(a.first, a.second, b.first, b.second)) {
    return {a.first, a.second};
  }
  if (including(a.first, b.first, a.second, b.second)) {
    return {a.first, b.first};
  }
  if (including(a.first, b.second, a.second, b.first)) {
    return {a.first, b.second};
  }
  if (including(a.second, b.first, a.first, b.second)) {
    return {a.second, b.first};
  }
  if (including(a.second, b.second, a.first, b.first)) {
    return {a.second, b.second};
  }
  if (including(b.first, b.second, a.first, a.second)) {
    return {b.first, b.second};
  }
  return {-1, -1};
}

void build(int l, int r, int o) {
  if (l == r) {
    nodes[o] = {pos[l], pos[l]};
  } else {
    int mid = l + r >> 1;
    build(l, mid, lo);
    build(mid + 1, r, ro);
    nodes[o] = nodes[lo] + nodes[ro];
  }
}

void modify(int l, int r, int o, int p) {
  if (l == r) {
    nodes[o] = {pos[l], pos[l]};
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, lo, p);
    } else {
      modify(mid + 1, r, ro, p);
    }
    nodes[o] = nodes[lo] + nodes[ro];
  }
}

int query(int l, int r, int o, pair<int, int> result) {
  if (l == r) {
    result = result + nodes[o];
    return ~result.first ? l : l - 1;
  } else {
    int mid = l + r >> 1;
    if (!~(result + nodes[lo]).first) {
      return query(l, mid, lo, result);
    } else {
      return query(mid + 1, r, ro, result + nodes[lo]);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &p[i]);
    pos[p[i]] = i;
  }
  for (int i = 2; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    graph[i].push_back(x);
    graph[x].push_back(i);
  }
  dfs(1, 0);
  rmq_init();
  build(0, n - 1, 1);
  scanf("%d", &q);
  while (q--) {
    int type, i, j;
    scanf("%d", &type);
    if (type == 1) {
      scanf("%d%d", &i, &j);
      swap(p[i], p[j]);
      swap(pos[p[i]], pos[p[j]]);
      modify(0, n - 1, 1, p[i]);
      modify(0, n - 1, 1, p[j]);
    } else {
      printf("%d\n", query(0, n - 1, 1, {pos[0], pos[0]}) + 1);
    }
  }
  return 0;
}
