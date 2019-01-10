#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int type, n, q, size[N], heavy[N], depth[N], father[N], father_v[N], top[N], dfn[N], rdfn[N], p[N], dfn_t, root[N], t, lo[N * 80], ro[N * 80], times[N * 80];
long long dis[N], pre[N], sum[N * 80], sumdis[N];
vector<pair<int, int>> graph[N];

void dfs1(int u, int father) {
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v.first != father) {
      ::father[v.first] = u;
      father_v[v.first] = v.second;
      depth[v.first] = depth[u] + 1;
      dis[v.first] = dis[u] + v.second;
      dfs1(v.first, u);
      size[u] += size[v.first];
      if (size[v.first] > size[heavy[u]]) {
        heavy[u] = v.first;
      }
    }
  }
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++dfn_t;
  rdfn[dfn_t] = u;
  if (heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : graph[u]) {
      if (v.first != father[u] && v.first != heavy[u]) {
        dfs2(v.first, v.first);
      }
    }
  }
}

int getlca(int u, int v) {
  for (; top[u] != top[v]; u = father[top[u]]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    }
  }
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  return u;
}

void modify(int l, int r, int& o, int ql, int qr) {
  ++t;
  sum[t] = sum[o];
  times[t] = times[o];
  lo[t] = lo[o];
  ro[t] = ro[o];
  o = t;
  sum[o] += pre[min(r, qr)] - pre[max(l, ql) - 1];
  if (ql <= l && r <= qr) {
    ++times[o];
    return;
  } else {
    int mid = l + r >> 1;
    if (ql <= mid) {
      modify(l, mid, lo[o], ql, qr);
    } if (qr > mid) {
      modify(mid + 1, r, ro[o], ql, qr);
    }
  }
}

long long query(int l, int r, int o, int ql, int qr) {
  if (!o) {
    return 0;
  }
  if (ql <= l && r <= qr) {
    return sum[o];
  } else {
    int mid = l + r >> 1;
    long long result = (pre[min(r, qr)] - pre[max(l, ql) - 1]) * times[o];
    if (ql <= mid) {
      result += query(l, mid, lo[o], ql, qr);
    } if (qr > mid) {
      result += query(mid + 1, r, ro[o], ql, qr);
    }
    return result;
  }
}

void dfs(int u, int father) {
  root[u] = root[father];
  int x = p[u];
  sumdis[u] = sumdis[father] + dis[x];
  for (; x; x = ::father[top[x]]) {
    modify(1, n, root[u], dfn[top[x]], dfn[x]);
  }
  for (auto v : graph[u]) {
    if (v.first != father) {
      dfs(v.first, u);
    }
  }
}

long long query(int u, int x) {
  long long result = dis[x] * depth[u] + sumdis[u];
  for (; x; x = father[top[x]]) {
    result -= query(1, n, root[u], dfn[top[x]], dfn[x]) << 1;
  }
  return result;
}

int main() {
  scanf("%d%d%d", &type, &n, &q);
  for (int i = 1; i < n; ++i) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    graph[x].emplace_back(y, c);
    graph[y].emplace_back(x, c);
  }
  depth[1] = 1;
  dfs1(1, 0);
  dfs2(1, 1);
  for (int i = 1; i <= n; ++i) {
    pre[i] = pre[i - 1] + father_v[rdfn[i]];
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &p[i]);
  }
  dfs(1, 0);
  long long last_answer = 0;
  while (q--) {
    long long u, v, k;
    scanf("%lld%lld%lld", &u, &v, &k);
    u ^= type * last_answer;
    v ^= type * last_answer;
    k ^= type * last_answer;
    last_answer = query(u, k) + query(v, k) - query(getlca(u, v), k) - query(father[getlca(u, v)], k);
    printf("%lld\n", last_answer);
  }
  return 0;
}
