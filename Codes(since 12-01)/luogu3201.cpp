#include<bits/stdc++.h>

using namespace std;

const int N = 456789;

int n, m, t, a[N], h[N], type[N], qx[N], qy[N], id[N], go[20][N], depth[N], node[N], value[N], answer[N];
vector<int> adj[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    h[++t] = a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> type[i];
    if (type[i] == 1) {
      cin >> qx[i] >> qy[i];
      h[++t] = qx[i];
      h[++t] = qy[i];
    }
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(h + 1, h + 1 + t, a[i]) - h;
  }
  for (int i = 1; i <= m; ++i) {
    if (type[i] == 1) {
      qx[i] = lower_bound(h + 1, h + 1 + t, qx[i]) - h;
      qy[i] = lower_bound(h + 1, h + 1 + t, qy[i]) - h;
    }
  }
  for (int i = 1; i <= t; ++i) {
    node[i] = i;
  }
  for (int i = 1; i <= m; ++i) {
    if (type[i] == 1) {
      int x = qx[i], y = qy[i];
      if (x == y || !node[x]) {
        continue;
      }
      if (!node[y]) {
        node[y] = node[x];
      } else {
        go[0][node[x]] = go[0][node[y]] = ++t;
        adj[t].push_back(node[x]);
        adj[t].push_back(node[y]);
        value[t] = i;
        node[y] = t;
      }
      node[x] = 0;
    }
  }
  int here = 0;
  function<void (int)> dfs = [&] (int x) {
    id[x] = here;
    for (int i = 1; i < 20; ++i) {
      go[i][x] = go[i - 1][go[i - 1][x]];
    }
    for (auto y : adj[x]) {
      depth[y] = depth[x] + 1;
      dfs(y);
    }
  };
  for (int i = t; i; --i) {
    if (!id[i]) {
      ++here;
      dfs(i);
    }
  }
  auto get_lca = [&] (int x, int y) {
    if (depth[x] < depth[y]) {
      swap(x, y);
    }
    for (int i = 19; ~i; --i) {
      if (depth[x] - (1 << i) >= depth[y]) {
        x = go[i][x];
      }
    }
    if (x == y) {
      return x;
    }
    for (int i = 19; ~i; --i) {
      if (go[i][x] != go[i][y]) {
        x = go[i][x];
        y = go[i][y];
      }
    }
    return go[0][x];
  };
  for (int i = 2; i <= n; ++i) {
    if (a[i] != a[i - 1]) {
      ++answer[1];
      if (id[a[i]] == id[a[i - 1]]) {
        --answer[value[get_lca(a[i], a[i - 1])]];
      }
    }
  }
  for (int i = 1; i <= m; ++i) {
    answer[i] += answer[i - 1];
    if (type[i] == 2) {
      cout << answer[i] + 1 << '\n';
    }
  }
  return 0;
}
