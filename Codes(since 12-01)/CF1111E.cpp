#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, q, size[N], father[N], depth[N], heavy[N], top[N], dfn[N], dfn_cnt, node[N], s[N], number[N << 2], f[N][305];
vector<int> graph[N];

void dfs1(int u, int p) {
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v != p) {
      father[v] = u;
      depth[v] = depth[u] + 1;
      dfs1(v, u);
      size[u] += size[v];
      if (size[v] > size[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++dfn_cnt;
  if (heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : graph[u]) {
      if (v != father[u] && v != heavy[u]) {
        dfs2(v, v);
      }
    }
  }
}

void modify(int p, int v) {
  for (; p <= n; p += p & -p) {
    number[p] += v;
  }
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    result += number[p];
  }
  return result;
}

int query(int l, int r) {
  return query(r) - query(l - 1);
}

int query_nodes(int u, int v) {
  int answer = -1;
  for (; top[u] != top[v]; u = father[top[u]]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    }
    answer += query(dfn[top[u]], dfn[u]);
  }
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  answer += query(dfn[u], dfn[v]);
  return answer;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs1(1, 0);
  dfs2(1, 1);
  while (q--) {
    int k, m, r;
    scanf("%d%d%d", &k, &m, &r);
    for (int i = 1; i <= k; ++i) {
      scanf("%d", &node[i]);
      modify(dfn[node[i]], 1);
    }
    for (int i = 1; i <= k; ++i) {
      s[node[i]] = query_nodes(node[i], r);
    }
    sort(node + 1, node + 1 + k, [&] (const int& x, const int& y) {
      return s[x] < s[y];
    });
    f[0][0] = 1;
    for (int i = 1; i <= k; ++i) {
      for (int j = 1; j <= min(i, m); ++j) {
        f[i][j] = (mul(f[i - 1][j], max(0, j - s[node[i]])) + f[i - 1][j - 1]) % mod;
      }
    }
    int answer = 0;
    for (int i = 1; i <= m; ++i) {
      add(answer, f[k][i]);
    }
    printf("%d\n", answer);
    for (int i = 1; i <= k; ++i) {
      modify(dfn[node[i]], -1);
    }
  }
  return 0;
}
