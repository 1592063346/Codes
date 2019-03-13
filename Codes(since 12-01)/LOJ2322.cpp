#include<bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10, M = 81;

int n, q, f0[260][N], f1[260][N], depth[N], fb[20][N];
long long a[N];
vector<int> adj[N];

struct fen_wick_t {
  long long c[N];

  fen_wick_t() {
    memset(c, 0, sizeof c);
  }

  void add(int p, long long v) {
    for (; p <= n; p += p & -p) {
      c[p] += v;
    }
  }

  long long query(int p) {
    long long result = 0;
    for (; p; p -= p & -p) {
      result += c[p];
    }
    return result;
  }
};

void dfs(int u, int p) {
  fb[0][u] = p;
  f0[0][u] = u;
  f1[0][u] = u;
  for (int i = 1; (1 << i) <= n; ++i) {
    fb[i][u] = fb[i - 1][fb[i - 1][u]];
  }
  f0[1][u] = p;
  for (int i = 2; i <= 0xff; ++i) {
    f0[i][u] = f0[1][f0[i - 1][u]];
  }
  f1[1][u] = f0[1][f0[0xff][u]];
  for (int i = 2; i <= 0xff; ++i) {
    f1[i][u] = f1[1][f1[i - 1][u]];
  }
  for (auto v : adj[u]) {
    if (v != p) {
      depth[v] = depth[u] + 1;
      dfs(v, u);
    }
  }
}

int jump(int u, int d) {
  return f0[d & 0xff][f1[d >> 8][u]];
}

int get_lca(int u, int v) {
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  for (int i = 15; ~i; --i) {
    if (depth[u] - (1 << i) >= depth[v]) {
      u = fb[i][u];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 15; ~i; --i) {
    if (fb[i][u] != fb[i][v]) {
      u = fb[i][u];
      v = fb[i][v];
    }
  }
  return fb[0][u];
}

struct tree_t {
  int dfn[N], edfn[N], f[N], father[N], dfn_cnt;
  vector<int> adj[N];
  fen_wick_t bit;

  int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
  }

  void dfs(int u) {
    if (u) {
      dfn[u] = ++dfn_cnt;
    }
    for (auto v : adj[u]) {
      dfs(v);
    }
    if (u) {
      edfn[u] = dfn_cnt;
    }
  }

  void add(int u, long long v) {
    bit.add(dfn[u], v);
    bit.add(edfn[u] + 1, -v);
  }

  long long query(int u) {
    return bit.query(dfn[u]);
  }

  void init(int k) {
    for (int i = 1; i <= n; ++i) {
      f[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
      adj[father[i] = jump(i, k)].push_back(i);
    }
    dfs(0);
    for (int i = 1; i <= n; ++i) {
      add(i, a[i]);
    }
    for (int i = 1; i <= n; ++i) {
      f[i] = a[i] == 1 ? father[i] : i;
    }
  }
} trees[M];

void modify(int u) {
  if (a[u] != 1) {
    long long diff = (long long) sqrt(a[u]) - a[u];
    a[u] = (long long) sqrt(a[u]);
    for (int i = 1; i < M; ++i) {
      trees[i].add(u, diff);
      if (a[u] == 1) {
        trees[i].f[u] = trees[i].find(trees[i].father[u]);
      }
    }
  }
}

void modify(int s, int t, int k) {
  int lca = get_lca(s, t), dist = depth[s] + depth[t] - (depth[lca] << 1);
  if (dist % k) {
    modify(t);
    t = jump(t, dist % k);
  }
  if (k >= M) {
    for (; depth[s] >= depth[lca]; s = jump(s, k)) {
      modify(s);
    }
    for (; depth[t] > depth[lca]; t = jump(t, k)) {
      modify(t);
    }
  } else {
    for (; depth[s] >= depth[lca]; s = trees[k].find(trees[k].father[s])) {
      modify(s);
    }
    for (; depth[t] > depth[lca]; t = trees[k].find(trees[k].father[t])) {
      modify(t);
    }
  }
}

long long query(int s, int t, int k) {
  int lca = get_lca(s, t), dist = depth[s] + depth[t] - (depth[lca] << 1);
  long long answer = 0;
  if (dist % k) {
    answer += a[t];
    t = jump(t, dist % k);
  }
  if (k >= M) {
    for (; depth[s] >= depth[lca]; s = jump(s, k)) {
      answer += a[s];
    }
    for (; depth[t] > depth[lca]; t = jump(t, k)) {
      answer += a[t];
    }
  } else {
    int x = jump(s, (depth[s] - depth[lca]) / k * k + k);
    answer += trees[k].query(s) - trees[k].query(x);
    if (depth[t] > depth[lca]) {
      x = jump(t, (depth[t] - depth[lca] - 1) / k * k + k);
      answer += trees[k].query(t) - trees[k].query(x);
    }
  }
  return answer;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  depth[1] = 1;
  dfs(1, 0);
  for (int i = 1; i < M; ++i) {
    trees[i].init(i);
  }
  scanf("%d", &q);
  while (q--) {
    int opt, s, t, k;
    scanf("%d%d%d%d", &opt, &s, &t, &k);
    if (opt == 0) {
      modify(s, t, k);
    } else {
      printf("%lld\n", query(s, t, k));
    }
  }
  return 0;
}
