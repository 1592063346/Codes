#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

void cmax(pair<int, int>& x, pair<int, int> y) {
  if (x < y) {
    x = y;
  }
}

int task_id, tt, n;
pair<int, int> sumt[N], maxt[N][2];
bool answer[N];
vector<int> adj[N];

void dfs1(int u, int p) {
  sumt[u] = {0, 0};
  maxt[u][0] = {0, 0};
  maxt[u][1] = {0, 0};
  for (auto v : adj[u]) {
    if (v != p) {
      dfs1(v, u);
      sumt[u].first += sumt[v].first;
      if (sumt[v] > maxt[u][0]) {
        maxt[u][1] = maxt[u][0];
        maxt[u][0] = sumt[v];
      } else {
        cmax(maxt[u][1], sumt[v]);
      }
    }
  }
  sumt[u].second = max(sumt[u].first & 1, maxt[u][0].second - (sumt[u].first - maxt[u][0].first));
  ++sumt[u].first;
  ++sumt[u].second;
}

void dfs2(int u, int p, int restt, pair<int, int> x) {
  answer[u] = false;
  int s = restt + sumt[u].first - 1;
  pair<int, int> f = max(x, maxt[u][0]);
  if (!(s & 1) && f.second - (s - f.first) <= 0) {
    answer[u] = true;
  }
  for (auto v : adj[u]) {
    if (v != p) {
      dfs2(v, u, restt + sumt[u].first - sumt[v].first - 1, max(x, sumt[v] == maxt[u][0] ? maxt[u][1] : maxt[u][0]));
    }
  }
}

int main() {
  scanf("%d%d", &task_id, &tt);
  int cc = 0;
  while (tt--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
    }
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0, 0, {0, 0});
    for (int i = 1; i <= (task_id == 3 ? 1 : n); ++i) {
      printf("%d", (int) answer[i]);
    }
    puts("");
  }
  return 0;
}
