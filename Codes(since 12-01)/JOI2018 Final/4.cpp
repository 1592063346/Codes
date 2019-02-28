#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const long long inf = 1e18;

bool cmin(long long& x, long long y) {
  return x > y ? x = y, true : false;
}

int n, m, s, t, ss, tt;
long long dis_t[N], dis_ss[N], dis_tt[N], answer = inf;
pair<long long, long long> min_dist[N];
vector<pair<int, int>> graph[N];
bool visit[N], counted[N];

struct node_t {
  long long d;
  int u;

  node_t() {}
  node_t(int u, long long d): u(u), d(d) {}

  bool operator < (const node_t& a) const {
    return d > a.d;
  }
};

void dijkstra(int source, long long* d) {
  for (int i = 1; i <= n; ++i) {
    d[i] = inf;
  }
  d[source] = 0;
  memset(visit, false, sizeof visit);
  priority_queue<node_t> que;
  que.emplace(source, 0);
  while (!que.empty()) {
    int x = que.top().u;
    que.pop();
    if (!visit[x]) {
      visit[x] = true;
      for (auto v : graph[x]) {
        if (cmin(d[v.first], d[x] + v.second)) {
          que.emplace(v.first, d[v.first]);
        }
      }
    }
  }
}

pair<long long, long long> dfs(int u) {
  if (counted[u]) {
    return min_dist[u];
  }
  counted[u] = true;
  min_dist[u] = {dis_ss[u], dis_tt[u]};
  for (auto v : graph[u]) {
    if (dis_t[u] == dis_t[v.first] + v.second) {
      pair<long long, long long> go = dfs(v.first);
      cmin(answer, dis_ss[u] + go.second);
      cmin(answer, go.first + dis_tt[u]);
      cmin(min_dist[u].first, go.first);
      cmin(min_dist[u].second, go.second);
    }
  }
  return min_dist[u];
}

int main() {
  scanf("%d%d%d%d%d%d", &n, &m, &s, &t, &ss, &tt);
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }
  dijkstra(t, dis_t);
  dijkstra(ss, dis_ss);
  dijkstra(tt, dis_tt);
  dfs(s);
  printf("%lld\n", min(dis_ss[tt], answer));
  return 0;
}
