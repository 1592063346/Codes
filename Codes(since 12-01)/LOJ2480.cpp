#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, m, q, ex[N], ey[N], dfn[N], low[N], anc[N], id[N], sta[N], result[N], father[20][N], fid[N], depth[N], top, tt, bcct;
vector<pair<int, int>> adj[N], bccadj[N];

void tarjan(int x, int f) {
  dfn[x] = low[x] = tt++;
  sta[++top] = x;
  bool ok = false;
  for (int i = 0; i < adj[x].size(); ++i) {
    int y = adj[x][i].first;
    if (y != f || ok) {
      if (!~dfn[y]) {
        tarjan(y, x);
        low[x] = min(low[x], low[y]);
      } else {
        low[x] = min(low[x], dfn[y]);
      }
    } else {
      ok = true;
    }
  }
  if (low[x] == dfn[x]) {
    while (1) {
      int y = sta[top--];
      id[y] = bcct;
      if (y == x) {
        break;
      }
    }
    ++bcct;
  }
}

void dfs(int x, int f) {
  father[0][x] = f;
  for (int i = 1; (1 << i) <= bcct; ++i) {
    father[i][x] = ~father[i - 1][x] ? father[i - 1][father[i - 1][x]] : -1;
  }
  for (int i = 0; i < bccadj[x].size(); ++i) {
    int y = bccadj[x][i].first;
    if (y != f) {
      fid[y] = bccadj[x][i].second;
      depth[y] = depth[x] + 1;
      dfs(y, x);
    }
  }
}

int get_lca(int x, int y) {
  if (depth[x] < depth[y]) {
    swap(x, y);
  }
  for (int i = 18; ~i; --i) {
    if (depth[x] - (1 << i) >= depth[y]) {
      x = father[i][x];
    }
  }
  if (x == y) {
    return x;
  }
  for (int i = 18; ~i; --i) {
    if (father[i][x] != father[i][y]) {
      x = father[i][x];
      y = father[i][y];
    }
  }
  return father[0][x];
}

int find(int x) {
  return anc[x] == x ? x : anc[x] = find(anc[x]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 0, x, y; i < m; ++i) {
    cin >> x >> y;
    --x;
    --y;
    adj[x].push_back(make_pair(y, i));
    adj[y].push_back(make_pair(x, i));
    ex[i] = x;
    ey[i] = y;
  }
  for (int i = 0; i < n; ++i) {
    dfn[i] = low[i] = id[i] = -1;
  }
  for (int i = 0; i < n; ++i) {
    if (!~dfn[i]) {
      tarjan(i, -1);
    }
  }
  for (int i = 0; i < m; ++i) {
    ex[i] = id[ex[i]];
    ey[i] = id[ey[i]];
  }
  for (int i = 0; i < n; ++i) {
    for (int e = 0; e < adj[i].size(); ++e) {
      int j = adj[i][e].first;
      if (i < j && id[i] != id[j]) {
        bccadj[id[i]].push_back(make_pair(id[j], adj[i][e].second));
        bccadj[id[j]].push_back(make_pair(id[i], adj[i][e].second));
      }
    }
  }
  for (int i = 0; i < bcct; ++i) {
    father[0][i] = -1;
  }
  for (int i = 0; i < bcct; ++i) {
    if (!~father[0][i]) {
      depth[i] = 1;
      dfs(i, -1);
    }
  }
  for (int i = 0; i < bcct; ++i) {
    anc[i] = i;
  }
  cin >> q;
  for (int i = 0, x, y; i < q; ++i) {
    cin >> x >> y;
    --x;
    --y;
    x = id[x];
    y = id[y];
    int lca = get_lca(x, y);
    for (; depth[x] > depth[lca]; x = find(father[0][x])) {
      int e = fid[x];
      result[e] = ex[e] == x ? 1 : 2;
      anc[x] = find(father[0][x]);
    }
    for (; depth[y] > depth[lca]; y = find(father[0][y])) {
      int e = fid[y];
      result[e] = ex[e] == y ? 2 : 1;
      anc[y] = find(father[0][y]);
    }
  }
  for (int i = 0; i < m; ++i) {
    cout << (result[i] == 0 ? 'B' : result[i] == 1 ? 'R' : 'L');
  }
  cout << '\n';
  return 0;
}
