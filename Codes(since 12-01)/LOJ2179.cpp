#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
const int inf = 0x3f3f3f3f;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, m, query_l, query_r, nodes, root, max_d[N], value[N], size[N], f[N], answer = -inf;
vector<pair<int, int>> graph[N], info, tmp;
bool visit[N];

void find_root(int u, int father) {
  f[u] = 0;
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v.first != father && !visit[v.first]) {
      find_root(v.first, u);
      size[u] += size[v.first];
      cmax(f[u], size[v.first]);
    }
  }
  cmax(f[u], nodes - f[u]);
  if (f[u] < f[root]) {
    root = u;
  }
}

void get_max_d(int u, int father, int type, int d) {
  cmax(max_d[type], d);
  if (d != query_r) {
    for (auto v : graph[u]) {
      if (v.first != father && !visit[v.first]) {
        get_max_d(v.first, u, type, d + 1);
      }
    }
  }
}

void get_info(int u, int father, int last_color, int d, int w) {
  info.emplace_back(d, w);
  if (d != query_r) {
    for (auto v : graph[u]) {
      if (v.first != father && !visit[v.first]) {
        get_info(v.first, u, v.second, d + 1, w + (v.second == last_color ? 0 : value[v.second]));
      }
    }
  }
}

struct segment_t {
  int maxv[N << 2];

  void build(int l, int r, int o) {
    maxv[o] = -inf;
    if (l != r) {
      int mid = l + r >> 1;
      build(l, mid, o << 1);
      build(mid + 1, r, o << 1 | 1);
    }
  }

  void modify(int l, int r, int o, int p, int v) {
    cmax(maxv[o], v);
    if (l != r) {
      int mid = l + r >> 1;
      if (p <= mid) {
        modify(l, mid, o << 1, p, v);
      } else {
        modify(mid + 1, r, o << 1 | 1, p, v);
      }
    }
  }

  int query(int l, int r, int o, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return maxv[o];
    } else {
      int mid = l + r >> 1;
      if (qr <= mid) {
        return query(l, mid, o << 1, ql, qr);
      } else if (ql > mid) {
        return query(mid + 1, r, o << 1 | 1, ql, qr);
      } else {
        return max(query(l, mid, o << 1, ql, qr), query(mid + 1, r, o << 1 | 1, ql, qr));
      }
    }
  }
} t0, t1;

void dfs(int u) {
  visit[u] = true;
  for (auto v : graph[u]) {
    if (!visit[v.first]) {
      max_d[v.second] = 0;
    }
  }
  for (auto v : graph[u]) {
    if (!visit[v.first]) {
      get_max_d(v.first, u, v.second, 1);
    }
  }
  t0.build(0, nodes, 1);
  t0.modify(0, nodes, 1, 0, 0);
  int last_color = 0;
  for (auto v : graph[u]) {
    if (!visit[v.first]) {
      if (v.second != last_color) {
        for (auto p : tmp) {
          t0.modify(0, nodes, 1, p.first, p.second);
        }
        tmp.clear();
        last_color = v.second;
        t1.build(0, max_d[v.second], 1);
      }
      info.clear();
      get_info(v.first, u, v.second, 1, value[v.second]);
      for (auto p : info) {
        if (max(0, query_l - p.first) <= min(nodes, query_r - p.first)) {
          cmax(answer, t0.query(0, nodes, 1, max(0, query_l - p.first), min(nodes, query_r - p.first)) + p.second);
        }
        if (max(0, query_l - p.first) <= min(max_d[v.second], query_r - p.first)) {
          cmax(answer, t1.query(0, max_d[v.second], 1, max(0, query_l - p.first), min(max_d[v.second], query_r - p.first)) + p.second);
        }
      }
      for (auto p : info) {
        t1.modify(0, max_d[v.second], 1, p.first, p.second - value[v.second]);
        tmp.push_back(p);
      }
    }
  }
  for (auto p : tmp) {
    t0.modify(0, nodes, 1, p.first, p.second);
  }
  tmp.clear();
  if (query_l <= nodes) {
    cmax(answer, t0.query(0, nodes, 1, query_l, min(nodes, query_r)));
  }
  int old = nodes;
  for (auto v : graph[u]) {
    if (!visit[v.first]) {
      if (size[v.first] > size[u]) {
        nodes = old - size[u];
      } else {
        nodes = size[v.first];
      }
      root = 0;
      find_root(v.first, u);
      dfs(root);
    }
  }
}

int main() {
  scanf("%d%d%d%d", &n, &m, &query_l, &query_r);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &value[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    graph[u].emplace_back(v, c);
    graph[v].emplace_back(u, c);
  }
  for (int i = 1; i <= n; ++i) {
    sort(graph[i].begin(), graph[i].end(), [&] (const pair<int, int>& a, const pair<int, int>& b) {
      return a.second < b.second;
    });
  }
  nodes = n;
  root = 0;
  f[0] = n + 1;
  find_root(1, 0);
  dfs(1);
  printf("%d\n", answer);
  return 0;
}
