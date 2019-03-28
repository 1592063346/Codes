#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, M = 200;

int n, m, a[N], h[N], sta[N], father[N], logv[N], de[20][N], id[20][N], firstp[N], block[N], number[N], answer[N], total, tt, ttt, result;
bool visit[N];
vector<int> adj[N];

struct query_t {
  int u, v, id;

  query_t() {}
  query_t(int u, int v, int id): u(u), v(v), id(id) {}

  bool operator < (const query_t& a) const {
    return block[u] == block[a.u] ? block[v] < block[a.v] : block[u] < block[a.u];
  }
} queries[N];

void dfs(int u, int p, int d) {
  firstp[u] = ++total;
  id[0][total] = u;
  de[0][total] = d;
  for (auto v : adj[u]) {
    if (v != p) {
      father[v] = u;
      dfs(v, u, d + 1);
      if (tt >= M) {
        ++ttt;
        while (tt) {
          block[sta[tt--]] = ttt;
        }
      }
      ++total;
      id[0][total] = u;
      de[0][total] = d;
    }
  }
  sta[++tt] = u;
}

void rmq_init() {
  for (int i = 2; i <= total; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= total; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= total; ++j) {
      int d1 = de[i - 1][j], d2 = de[i - 1][j + (1 << i - 1)];
      de[i][j] = min(d1, d2);
      id[i][j] = d1 < d2 ? id[i - 1][j] : id[i - 1][j + (1 << i - 1)];
    }
  }
}

int get_lca(int u, int v) {
  u = firstp[u];
  v = firstp[v];
  if (u > v) {
    swap(u, v);
  }
  int k = logv[v - u + 1];
  return de[k][u] < de[k][v - (1 << k) + 1] ? id[k][u] : id[k][v - (1 << k) + 1];
}

void get_all_blocks() {
  dfs(1, 0, 0);
  while (tt) {
    block[sta[tt--]] = ttt;
  }
}

void update(int u) {
  if (!visit[u]) {
    if (++number[a[u]] == 1) {
      ++result;
    }
  } else {
    if (--number[a[u]] == 0) {
      --result;
    }
  }
  visit[u] = !visit[u];
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    h[i] = a[i];
  }
  sort(h + 1, h + 1 + n);
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(h + 1, h + 1 + n, a[i]) - h;
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  get_all_blocks();
  rmq_init();
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    queries[i] = query_t(u, v, i);
  }
  sort(queries + 1, queries + 1 + m);
  int pu = 1, pv = 1;
  for (int i = 1; i <= m; ++i) {
    int lca = get_lca(queries[i].u, pu);
    for (int x = pu; x != lca; x = father[x]) {
      update(x);
    }
    for (int x = queries[i].u; x != lca; x = father[x]) {
      update(x);
    }
    lca = get_lca(queries[i].v, pv);
    for (int x = pv; x != lca; x = father[x]) {
      update(x);
    }
    for (int x = queries[i].v; x != lca; x = father[x]) {
      update(x);
    }
    pu = queries[i].u;
    pv = queries[i].v;
    lca = get_lca(queries[i].u, queries[i].v);
    update(lca);
    answer[queries[i].id] = result;
    update(lca);
  }
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
