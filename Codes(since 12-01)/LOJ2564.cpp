#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

struct node_t {
  int l, r, number;
  long long sp, si, spi;

  node_t operator + (const node_t& a) const {
    node_t result;
    result.number = number + a.number;
    result.sp = sp + a.sp;
    result.si = si + a.si;
    result.spi = spi + a.spi;
    return result;
  }

  node_t operator - (const node_t& a) const {
    node_t result;
    result.number = number - a.number;
    result.sp = sp - a.sp;
    result.si = si - a.si;
    result.spi = spi - a.spi;
    return result;
  }
} info[N * 20];

int tt, ttt, n, m, p, a[N], root[N], firstp[N], id[20][N], de[20][N], pre[N], total, depth[N], logv[N], father[N], tag[N];
long long sumi[N], sump[N], sumi2[N], sumpi[N];
vector<int> adj[N], sta[N], nodes[N];
unsigned int sa, sb, sc;

unsigned int rng61() {
  sa ^= sa << 16;
  sa ^= sa >> 5;
  sa ^= sa << 1;
  unsigned int t = sa;
  sa = sb;
  sb = sc;
  sc ^= t ^ sa;
  return sc;
}

void gen() {
  scanf("%d%d%u%u%u", &n, &p, &sa, &sb, &sc);
  for (int i = 1; i <= n; ++i) {
    adj[i].clear();
    nodes[i].clear();
  }
  for (int i = 2; i <= p; ++i) {
    adj[i - 1].push_back(i);
  }
  for (int i = p + 1; i <= n; ++i) {
    adj[rng61() % (i - 1) + 1].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    a[i] = rng61() % n + 1;
    nodes[a[i]].push_back(i);
  }
}

int modify(int l, int r, int u, int p, int i) {
  int x = ++ttt;
  info[x] = info[u];
  ++info[x].number;
  info[x].sp += p;
  info[x].si += i;
  info[x].spi += (long long) p * i;
  if (l != r) {
    int mid = l + r >> 1;
    if (p <= mid) {
      info[x].l = modify(l, mid, info[u].l, p, i);
    } else {
      info[x].r = modify(mid + 1, r, info[u].r, p, i);
    }
  }
  return x;
}

node_t query(int l, int r, int o1, int o2, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return info[o2] - info[o1];
  } else {
    int mid = l + r >> 1;
    if (qr <= mid) {
      return query(l, mid, info[o1].l, info[o2].l, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, info[o1].r, info[o2].r, ql, qr);
    } else {
      return query(l, mid, info[o1].l, info[o2].l, ql, qr) + query(mid + 1, r, info[o1].r, info[o2].r, ql, qr);
    }
  }
}

void dfs(int u, int p) {
  pre[u] = sta[a[u]].size() ? sta[a[u]].back() : 0;
  sumi[u] = sumi[p] + depth[u];
  sump[u] = sump[p] + pre[u];
  sumi2[u] = sumi2[p] + (long long) depth[u] * depth[u];
  sumpi[u] = sumpi[p] + (long long) pre[u] * depth[u];
  sta[a[u]].push_back(depth[u]);
  firstp[u] = ++total;
  id[0][total] = u;
  de[0][total] = depth[u];
  root[u] = modify(0, n - 1, root[p], pre[u], depth[u]);
  for (auto v : adj[u]) {
    depth[v] = depth[u] + 1;
    father[v] = u;
    dfs(v, u);
    ++total;
    id[0][total] = u;
    de[0][total] = depth[u];
  }
  sta[a[u]].pop_back();
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

bool on_path(int u, int v, int x) {
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  return get_lca(u, x) == u && get_lca(x, v) == x;
}

long long solve(int a, int b) {
  if (depth[a] > depth[b]) {
    swap(a, b);
  }
  int x = depth[a], y = depth[b];
  node_t result = query(0, n - 1, root[a], root[b], 0, x);
  return (long long) result.number * (y + 1) * x - result.sp * (y + 1) - result.si * x + result.spi + (x + y + 2) * (sumi[a] - sump[a]) - 2 * (sumi2[a] - sumpi[a]) - x;
}

void reset() {
  gen();
  ttt = 0;
  total = 0;
  fill(root, root + n + 1, 0);
  fill(tag, tag + n + 1, 0);
  depth[1] = 1;
  dfs(1, 0);
  rmq_init();
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    reset();
    scanf("%d", &m);
    while (m--) {
      int opt, x, y;
      scanf("%d%d%d", &opt, &x, &y);
      if (depth[x] > depth[y]) {
        swap(x, y);
      }
      int lca = get_lca(x, y);
      if (opt == 1) {
        int answer = query(0, n - 1, root[father[lca]], root[y], 0, depth[lca] - 1).number;
        for (int i = x; i != lca; i = father[i]) {
          if (tag[a[i]] != m + 1) {
            tag[a[i]] = m + 1;
            bool found = false;
            for (auto u : nodes[a[i]]) {
              if (on_path(lca, y, u)) {
                found = true;
                break;
              }
            }
            answer += !found;
          }
        }
        printf("%d\n", answer);
      } else {
        long long answer = solve(father[lca], y) + solve(x, father[lca]) - 2 * (depth[lca] * (sumi[lca] - sump[lca]) - sumi2[lca] + sumpi[lca]) + depth[father[lca]];
        node_t result = query(0, n - 1, root[father[lca]], root[y], 0, depth[lca] - 1);
        answer += (depth[x] - depth[lca] + 1) * ((long long) (depth[y] + 1) * result.number - result.si);
        for (int i = x;; i = father[i]) {
          if (pre[i] < depth[lca] && tag[a[i]] != m + 1) {
            tag[a[i]] = m + 1;
            int mind = depth[y] + 1;
            for (auto u : nodes[a[i]]) {
              if (on_path(lca, y, u)) {
                cmin(mind, depth[u]);
              }
            }
            answer += (long long) (depth[x] - depth[i] + 1) * (mind - depth[lca]);
          }
          if (i == lca) {
            break;
          }
        }
        printf("%lld\n", answer);
      }
    }
  }
  return 0;
}
