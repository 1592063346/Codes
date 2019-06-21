#include<bits/stdc++.h>

using namespace std;

const int N = 56789;
const long long llinf = 1e18;

template<typename T>
T read() {
  T x = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

using pii = pair<int, int>;
using pil = pair<int, long long>;
using pll = pair<long long, long long>;

struct node_t {
  int l, r;
  multiset<long long> foos, bars;
  long long foo, bar;

  node_t() {
    foo = bar = -llinf;
  }

  node_t(int l, int r, long long foo, long long bar): l(l), r(r), foo(foo), bar(bar) {
    foos.clear();
    bars.clear();
  }

  void update() {
    foo = foos.size() ? *--foos.end() : -llinf;
    bar = bars.size() ? *--bars.end() : -llinf;
  }
} node[N * 50];

int tt, n, m, here, node_tt, dfn_tt, rmq_tt, top, log_2[N << 1], first[N], size[N], sta[N], dfn[N], father[18][N], depth[N], root[N];
vector<pii> adj[N];
vector<int> virt_adj[N];
vector<pil> values[N];
vector<pair<pii, long long>> virt[N];
vector<pair<int, pll>> add[N], del[N];
pair<pil, pil> dir[N];
pii rmq_t[20][N << 1];
long long d[N], answer;

void dfs_init(int x, int f) {
  dfn[x] = ++dfn_tt;
  first[x] = ++rmq_tt;
  rmq_t[0][rmq_tt] = make_pair(depth[x], x);
  father[0][x] = f;
  size[x] = 1;
  for (int i = 1; i < 17; ++i) {
    father[i][x] = father[i - 1][father[i - 1][x]];
  }
  for (auto e : adj[x]) {
    int y = e.first;
    if (y != f) {
      depth[y] = depth[x] + 1;
      d[y] = d[x] + e.second;
      dfs_init(y, x);
      rmq_t[0][++rmq_tt] = make_pair(depth[x], x);
      size[x] += size[y];
    }
  }
}

int get_lca(int x, int y) {
  x = first[x];
  y = first[y];
  if (x > y) {
    swap(x, y);
  }
  int k = log_2[y - x + 1];
  return min(rmq_t[k][x], rmq_t[k][y - (1 << k) + 1]).second;
}

int jump(int x, int d) {
  for (int i = 16; ~i; --i) {
    if (d >> i & 1) {
      x = father[i][x];
    }
  }
  return x;
}

void push(int x) {
  int ll = node[x].l, rr = node[x].r;
  node[x].foo = max(node[ll].foo, node[rr].foo);
  node[x].bar = max(node[ll].bar, node[rr].bar);
}

void modify(int l, int r, int& x, int p, long long foo, long long bar, bool add = true) {
  if (!x) {
    x = ++node_tt;
  }
  if (l == r) {
    if (add) {
      node[x].foos.insert(foo);
      node[x].bars.insert(bar);
    } else {
      node[x].foos.erase(node[x].foos.find(foo));
      node[x].bars.erase(node[x].bars.find(bar));
    }
    node[x].update();
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, node[x].l, p, foo, bar, add);
    } else {
      modify(mid + 1, r, node[x].r, p, foo, bar, add);
    }
    push(x);
  }
}

long long query(int l, int r, int x, int ql, int qr, int op) {
  if (ql > qr || !x) {
    return -llinf;
  }
  if (ql <= l && r <= qr) {
    return !op ? node[x].foo : node[x].bar;
  } else {
    int mid = l + r >> 1;
    long long result = -llinf;
    if (ql <= mid) {
      result = max(result, query(l, mid, node[x].l, ql, qr, op));
    }
    if (qr > mid) {
      result = max(result, query(mid + 1, r, node[x].r, ql, qr, op));
    }
    return result;
  }
}

int merge(int l, int r, int x, int y) {
  if (!x || !y) {
    return x | y;
  } else if (l == r) {
    if (node[x].foos.size() < node[y].foos.size()) {
      swap(x, y);
    }
    for (auto z : node[y].foos) {
      node[x].foos.insert(z);
    }
    for (auto z : node[y].bars) {
      node[x].bars.insert(z);
    }
    node[y].foos.clear();
    node[y].bars.clear();
    node[x].update();
    return x;
  } else {
    int mid = l + r >> 1;
    answer = max(answer, node[node[x].l].foo + node[node[y].r].bar - d[here]);
    answer = max(answer, node[node[y].l].foo + node[node[x].r].bar - d[here]);
    node[x].l = merge(l, mid, node[x].l, node[y].l);
    node[x].r = merge(mid + 1, r, node[x].r, node[y].r);
    push(x);
    return x;
  }
}

void dfs(int x, int f) {
  for (auto info : add[x]) {
    answer = max(answer, info.second.first + query(1, n, root[x], info.first + 1, n, 1) - d[x]);
    answer = max(answer, info.second.second + query(1, n, root[x], 1, info.first - 1, 0) - d[x]);
    modify(1, n, root[x], info.first, info.second.first, info.second.second);
  }
  for (auto e : adj[x]) {
    int y = e.first;
    if (y != f) {
      dfs(y, x);
      here = x;
      root[x] = merge(1, n, root[x], root[y]);
    }
  }
  for (auto info : del[x]) {
    modify(1, n, root[x], info.first, info.second.first, info.second.second, false);
  }
}

long long f(pil x, pil y) {
  if (!x.first || !y.first) {
    return -llinf;
  }
  int lca = get_lca(x.first, y.first);
  return x.second + y.second + d[x.first] + d[y.first] - 2 * d[lca];
}

void merge(int x, pil y) {
  if (!dir[x].first.first) {
    dir[x].first = y;
  } else if (!dir[x].second.first) {
    dir[x].second = y;
  } else {
    long long t1 = f(dir[x].first, dir[x].second);
    long long t2 = f(dir[x].first, y);
    long long t3 = f(dir[x].second, y);
    long long final = max(max(t1, t2), t3);
    if (t2 == final) {
      dir[x].second = y;
    } else if (t3 == final) {
      dir[x].first = y;
    }
  }
  answer = max(answer, f(dir[x].first, dir[x].second) / 2 - d[x]);
}

void merge(int x, pair<pil, pil> y) {
  if (!dir[x].first.first) {
    dir[x] = y;
  } else {
    long long t1 = f(dir[x].first, y.first);
    long long t2 = f(dir[x].first, y.second);
    long long t3 = f(dir[x].second, y.first);
    long long t4 = f(dir[x].second, y.second);
    long long t5 = f(dir[x].first, dir[x].second);
    long long t6 = f(y.first, y.second);
    long long final = max(max(max(t1, t2), max(t3, t4)), max(t5, t6));
    answer = max(answer, max(max(t1, t2), max(t3, t4)) / 2 - d[x]);
    if (t1 == final) {
      dir[x].second = y.first;
    } else if (t2 == final) {
      dir[x].second = y.second;
    } else if (t3 == final) {
      dir[x].first = y.first;
    } else if (t4 == final) {
      dir[x].first = y.second;
    } else if (t6 == final) {
      dir[x] = y;
    }
  }
}

void dfs(int x) {
  for (auto info : values[x]) {
    merge(x, info);
  }
  for (auto y : virt_adj[x]) {
    dfs(y);
    merge(x, dir[y]);
  }
}

int main() {
  freopen("center.in", "r", stdin);
  freopen("center.out", "w", stdout);
  tt = read<int>();
  while (tt--) {
    n = read<int>();
    while (node_tt) {
      node[node_tt--] = node_t(0, 0, -llinf, -llinf);
    }
    for (int i = 1; i <= n; ++i) {
      root[i] = 0;
      virt[i].clear();
      adj[i].clear();
      add[i].clear();
      del[i].clear();
    }
    dfn_tt = rmq_tt = 0;
    answer = -llinf;
    for (int i = 1, x, y, z; i < n; ++i) {
      x = read<int>();
      y = read<int>();
      z = read<int>();
      adj[x].emplace_back(y, z);
      adj[y].emplace_back(x, z);
    }
    depth[1] = 1;
    dfs_init(1, 0);
    for (int i = 2; i <= rmq_tt; ++i) {
      log_2[i] = log_2[i >> 1] + 1;
    }
    for (int i = 1; (1 << i) <= rmq_tt; ++i) {
      for (int j = 1; j + (1 << i) - 1 <= rmq_tt; ++j) {
        rmq_t[i][j] = min(rmq_t[i - 1][j], rmq_t[i - 1][j + (1 << i - 1)]);
      }
    }
    m = read<int>();
    for (int i = 1, x, y; i <= m; ++i) {
      long long z;
      x = read<int>();
      y = read<int>();
      z = read<long long>();
      int lca = get_lca(x, y);
      virt[lca].emplace_back(make_pair(x, y), z);
      long long w = d[x] + d[y] - 2 * d[lca];
      if (x != lca) {
        int t = jump(x, depth[x] - depth[lca] - 1);
        add[x].emplace_back(depth[lca], make_pair(w - z, w - z + d[lca]));
        del[t].emplace_back(depth[lca], make_pair(w - z, w - z + d[lca]));
      }
      if (y != lca) {
        int t = jump(y, depth[y] - depth[lca] - 1);
        add[y].emplace_back(depth[lca], make_pair(w - z, w - z + d[lca]));
        del[t].emplace_back(depth[lca], make_pair(w - z, w - z + d[lca]));
      }
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
      if (!virt[i].size()) {
        continue;
      }
      vector<int> nodes(1, i);
      for (auto info : virt[i]) {
        int x = info.first.first, y = info.first.second, lca = get_lca(x, y);
        long long w = d[x] + d[y] - 2 * d[lca];
        nodes.push_back(x);
        nodes.push_back(y);
        values[x].emplace_back(y, w - 2 * info.second + d[x]);
        values[y].emplace_back(x, w - 2 * info.second + d[y]);
      }
      sort(nodes.begin(), nodes.end(), [&] (const int& x, const int& y) {
        return dfn[x] < dfn[y];
      });
      int old = nodes.size();
      for (int i = 0; i + 1 < old; ++i) {
        if (nodes[i] != nodes[i + 1]) {
          nodes.push_back(get_lca(nodes[i], nodes[i + 1]));
        }
      }
      sort(nodes.begin(), nodes.end(), [&] (const int& x, const int& y) {
        return dfn[x] < dfn[y];
      });
      nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
      top = 0;
      for (auto x : nodes) {
        while (top && dfn[sta[top]] + size[sta[top]] <= dfn[x]) {
          --top;
        }
        if (top) {
          virt_adj[sta[top]].push_back(x);
        }
        sta[++top] = x;
      }
      for (auto y : virt_adj[nodes[0]]) {
        dfs(y);
      }
      for (auto x : nodes) {
        virt_adj[x].clear();
        values[x].clear();
        dir[x].first.first = dir[x].second.first = 0;
      }
    }
    if (answer < -1e15) {
      cout << (char) 'F' << '\n';
    } else {
      cout << answer << '\n';
    }
  }
  return 0;
}
