#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m, logv[N], dd[20][N], id[20][N], first[N], afirst[N], depth[N], t, tt;
vector<int> adj[N];

void dfs(int u, int p, int d) {
  depth[u] = d;
  first[u] = ++t;
  afirst[t] = u;
  id[0][t] = u;
  dd[0][t] = d;
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v != p) {
      dfs(v, u, d + 1);
      ++t;
      id[0][t] = u;
      dd[0][t] = d;
    }
  }
}

void rmq_init() {
  for (int i = 2; i <= t; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= t; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= t; ++j) {
      int d1 = dd[i - 1][j], d2 = dd[i - 1][j + (1 << i - 1)];
      dd[i][j] = min(d1, d2);
      id[i][j] = d1 < d2 ? id[i - 1][j] : id[i - 1][j + (1 << i - 1)];
    }
  }
}

int get_lca(int u, int v) {
  u = first[u];
  v = first[v];
  if (u > v) {
    swap(u, v);
  }
  int k = logv[v - u + 1];
  return dd[k][u] < dd[k][v - (1 << k) + 1] ? id[k][u] : id[k][v - (1 << k) + 1];
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
    }
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    t = 0;
    dfs(1, 0, 1);
    rmq_init();
    while (m--) {
      int a, b;
      vector<pair<int, int> > s;
      scanf("%d", &a);
      while (a--) {
        scanf("%d", &b);
        s.push_back(make_pair(first[b], 0));
      }
      scanf("%d", &a);
      while (a--) {
        scanf("%d", &b);
        s.push_back(make_pair(first[b], 1));
      }
      sort(s.begin(), s.end());
      int answer = 0;
      for (int i = 0; i + 1 < s.size(); ++i) {
        if (s[i].second != s[i + 1].second) {
          int u = afirst[s[i].first], v = afirst[s[i + 1].first];
          answer = max(answer, depth[get_lca(u, v)]);
        }
      }
      printf("%d\n", answer);
    }
  }
  return 0;
}
