#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

int n, m, q, f[N], x[N];
vector<int> adj[3][N], go[N];
bool can[N][N], odd[N];
char color[N];

int main() {
  scanf("%d%d%d%s", &n, &m, &q, color + 1);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    go[x].push_back(y);
    go[y].push_back(x);
  }

  function<int (int)> find = [&] (int u) {
    if (f[u] == u) {
      return u;
    } else {
      int father = f[u];
      f[u] = find(f[u]);
      x[u] ^= x[father];
      return f[u];
    }
  };

  function<void (int, int)> merge = [&] (int i, int j) {
    int u = find(i), v = find(j);
    if (u != v) {
      f[u] = v;
      x[u] = x[i] ^ x[j] ^ 1;
      odd[v] |= odd[u];
    } else if (x[i] ^ x[j] ^ 1) {
      odd[u] = true;
    }
  };

  for (int i = 1; i <= n; ++i) {
    f[i] = i;
    x[i] = 0;
    odd[i] = false;
  }
  for (int i = 1; i <= n; ++i) {
    if (color[i] == '0') {
      for (auto j : go[i]) {
        if (color[j] == '0') {
          if (find(i) != find(j)) {
            adj[0][i].push_back(j);
            adj[0][j].push_back(i);
          }
          merge(i, j);
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (f[i] == i && odd[i]) {
      adj[0][i].push_back(i);
    }
  }

  for (int i = 1; i <= n; ++i) {
    f[i] = i;
    x[i] = 0;
    odd[i] = false;
  }
  for (int i = 1; i <= n; ++i) {
    if (color[i] == '1') {
      for (auto j : go[i]) {
        if (color[j] == '1') {
          if (find(i) != find(j)) {
            adj[1][i].push_back(j);
            adj[1][j].push_back(i);
          }
          merge(i, j);
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (f[i] == i && odd[i]) {
      adj[1][i].push_back(i);
    }
  }

  for (int i = 1; i <= n; ++i) {
    f[i] = i;
  }
  for (int i = 1; i <= n; ++i) {
    for (auto j : go[i]) {
      if (j > i && color[j] != color[i] && find(i) != find(j)) {
        adj[2][i].push_back(j);
        adj[2][j].push_back(i);
        merge(i, j);
      }
    }
  }

  queue<pair<int, int>> que;
  for (int i = 1; i <= n; ++i) {
    can[i][i] = true;
    que.emplace(i, i);
    for (auto j : go[i]) {
      if (color[j] == color[i] && !can[i][j]) {
        can[i][j] = can[j][i] = true;
        que.emplace(i, j);
      }
    }
  }
  while (!que.empty()) {
    pair<int, int> x = que.front();
    que.pop();
    for (int k = 0; k < 3; ++k) {
      for (auto i : adj[k][x.first]) {
        for (auto j : adj[k][x.second]) {
          if (!can[i][j]) {
            can[i][j] = can[j][i] = true;
            que.emplace(i, j);
          }
        }
      }
    }
  }
  while (q--) {
    int x, y;
    scanf("%d%d", &x, &y);
    puts(can[x][y] ? "YES" : "NO");
  }
  return 0;
}
