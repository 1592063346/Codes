#include<bits/stdc++.h>

using namespace std;

const int N = 87654;

int n, m, q, limit, longi[N][123], father[N], id[N];
unsigned int sa, sb, sc;
vector<pair<int, int>> adj[N];
bool on_tree[N];

int get_weight() {
  sa ^= sa << 16;
  sa ^= sa >> 5;
  sa ^= sa << 1;
  unsigned int t = sa;
  sa = sb;
  sb = sc;
  sc ^= t ^ sa;
  return sc % limit + 1;
}

struct edge_t {
  int u, v, w;

  edge_t() {
  }

  edge_t(int u, int v, int w): u(u), v(v), w(w) {
  }

  bool operator < (const edge_t& a) const {
    return w < a.w;
  }
};

struct graph_t {
  int nodes;
  long long sum;
  vector<edge_t> edges;
} pre[N], suf[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> sa >> sb >> sc >> limit;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      longi[j][i] = get_weight();
    }
  }
  for (int i = 1; i <= m; ++i) {
    pre[i].nodes = n;
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= m; ++j) {
      pre[j].edges.emplace_back(i, i + 1, get_weight());
    }
  }
  for (int i = 1; i <= m; ++i) {
    suf[i] = pre[i];
  }
  auto merge = [&] (graph_t x, graph_t y, int* weight) {
    vector<edge_t> edges;
    for (auto e : x.edges) {
      edges.push_back(e);
    }
    for (auto e : y.edges) {
      e.u += x.nodes;
      e.v += x.nodes;
      edges.push_back(e);
    }
    int nodes = x.nodes + y.nodes;
    for (int i = 1; i <= n; ++i) {
      edges.emplace_back(x.nodes - n + i, x.nodes + i, weight[i]);
    }
    for (int i = 1; i <= nodes; ++i) {
      father[i] = i;
      adj[i].clear();
    }
    function<int (int)> find = [&] (int x) {
      return father[x] == x ? x : father[x] = find(father[x]);
    };
    long long other_value = 0;
    auto merge = [&] (edge_t e) {
      father[find(e.u)] = find(e.v);
      other_value += e.w;
      adj[e.u].emplace_back(e.v, e.w);
      adj[e.v].emplace_back(e.u, e.w);
    };
    sort(edges.begin(), edges.end());
    for (auto e : edges) {
      if (find(e.u) != find(e.v)) {
        merge(e);
      }
    }
    for (int i = 1; i <= nodes; ++i) {
      on_tree[i] = (i <= n || i > nodes - n);
    }
    vector<edge_t> final;
    function<bool (int, int)> dfs = [&] (int x, int f) {
      int sub = 0;
      for (auto e : adj[x]) {
        int y = e.first;
        if (y != f) {
          sub += dfs(y, x);
        }
      }
      if (sub > 1) {
        on_tree[x] = true;
      }
      return sub > 0 || on_tree[x];
    };
    function<void (int, int, pair<int, int>)> build = [&] (int x, int f, pair<int, int> last) {
      if (on_tree[x] && last.first) {
        final.emplace_back(last.first, id[x], last.second);
        other_value -= last.second;
      }
      if (on_tree[x]) {
        last = pair<int, int>(id[x], 0);
      }
      for (auto e : adj[x]) {
        int y = e.first;
        if (y != f) {
          build(y, x, pair<int, int>(last.first, max(last.second, e.second)));
        }
      }
    };
    dfs(1, 0);
    int tt = 0;
    for (int i = 1; i <= nodes; ++i) {
      if (on_tree[i]) {
        id[i] = ++tt;
      }
    }
    build(1, 0, pair<int, int>(0, 0));
    graph_t result;
    result.nodes = tt;
    result.sum = x.sum + y.sum + other_value;
    result.edges = final;
    return result;
  };
  for (int i = 2; i <= m; ++i) {
    pre[i] = merge(pre[i - 1], pre[i], longi[i - 1]);
  }
  for (int i = m - 1; i; --i) {
    suf[i] = merge(suf[i], suf[i + 1], longi[i]);
  }
  cin >> q;
  for (int i = 1, l, r; i <= q; ++i) {
    cin >> l >> r;
    --l;
    ++r;
    graph_t result = merge(suf[r], pre[l], longi[m]);
    long long answer = result.sum;
    for (auto e : result.edges) {
      answer += e.w;
    }
    cout << answer << '\n';
  }
  return 0;
}
