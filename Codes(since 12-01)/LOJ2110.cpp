#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10, inf = 0x3f3f3f3f;

int n, m, p, id[N], aid[1 << 10], f[N][1 << 10], g[1 << 10];
vector<pair<int, int>> graph[N];
vector<int> nodes[N];
bool inq[N];

bool cmin(int& x, int y) {
  return x > y ? x = y, true : false;
}

void update(int s) {
  queue<int> que;
  for (int i = 1; i <= n; ++i) {
    if (f[i][s] < inf) {
      que.push(i);
      inq[i] = true;
    }
  }
  while (!que.empty()) {
    int x = que.front();
    inq[x] = false;
    que.pop();
    for (auto e : graph[x]) {
      if (cmin(f[e.first][s], f[x][s] + e.second)) {
        if (!inq[e.first]) {
          inq[e.first] = true;
          que.push(e.first);
        }
      }
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &p);
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }
  memset(f, 0x3f, sizeof f);
  for (int i = 0; i < p; ++i) {
    int x, d;
    scanf("%d%d", &x, &d);
    id[d] = i;
    aid[1 << i] = d;
    nodes[x].push_back(d);
    f[d][1 << i] = 0;
  }
  for (int s = 1; s < 1 << p; ++s) {
    for (int i = 1; i <= n; ++i) {
      for (int s1 = s; s1; s1 = (s1 - 1) & s) {
        cmin(f[i][s], f[i][s1] + f[i][s ^ s1]);
      }
    }
    update(s);
  }
  memset(g, 0x3f, sizeof g);
  for (int i = 1; i <= p; ++i) {
    if (nodes[i].size()) {
      int s = 0;
      for (auto u : nodes[i]) {
        s |= 1 << id[u];
      }
      g[s] = f[aid[s & -s]][s];
    }
  }
  for (int s = 1; s < 1 << p; ++s) {
    for (int s1 = s; s1; s1 = (s1 - 1) & s) {
      cmin(g[s], g[s1] + g[s ^ s1]);
    }
    if (g[s] < inf) {
      cmin(g[s], f[aid[s & -s]][s]);
    }
  }
  printf("%d\n", g[(1 << p) - 1]);
  return 0;
}
