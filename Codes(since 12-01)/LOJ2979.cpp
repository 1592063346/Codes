#include<bits/stdc++.h>

using namespace std;

const int N = 305, max_node = 20010, inf = 0x3f3f3f3f;

struct edge {
  int to, cap, flow, cost;

  edge () {}
  edge (int to, int cap, int flow, int cost): to(to), cap(cap), flow(flow), cost(cost) {}
};

int n, m, node_cnt, l[N][11], r[N][11], idl[N][11], idr[N][11], s, t, d[max_node], cur[max_node];
bool inq[max_node], visit[max_node];
vector<int> graph[max_node];
vector<edge> edges;

void add_edge(int u, int v, int cap, int cost) {
  edges.emplace_back(v, cap, 0, cost);
  edges.emplace_back(u, 0, 0, -cost);
  graph[u].push_back(edges.size() - 2);
  graph[v].push_back(edges.size() - 1);
}

bool bfs() {
  memset(d, 0x3f, sizeof d);
  memset(cur, 0, sizeof cur);
  memset(inq, false, sizeof inq);
  memset(visit, false, sizeof visit);
  queue<int> que;
  que.push(s);
  d[s] = 0;
  inq[s] = true;
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    inq[x] = false;
    for (auto v : graph[x]) {
      edge& e = edges[v];
      if (e.flow < e.cap && d[e.to] > d[x] + e.cost) {
        d[e.to] = d[x] + e.cost;
        if (!inq[e.to]) {
          que.push(e.to);
          inq[e.to] = true;
        }
      }
    }
  }
  return d[t] != inf;
}

pair<int, int> dfs(int u, int a) {
  if (u == t || !a) {
    return {a, 0};
  } else {
    visit[u] = true;
    pair<int, int> result (0, 0);
    for (int& i = cur[u]; i < graph[u].size(); ++i) {
      edge& e = edges[graph[u][i]];
      if (d[e.to] == d[u] + e.cost && !visit[e.to]) {
        pair<int, int> x = dfs(e.to, min(e.cap - e.flow, a));
        e.flow += x.first;
        edges[graph[u][i] ^ 1].flow -= x.first;
        result.first += x.first;
        result.second += x.second + x.first * e.cost;
        a -= x.first;
        if (!a) {
          break;
        }
      }
    }
    return result;
  }
}

pair<int, int> solve() {
  pair<int, int> result (0, 0);
  while (bfs()) {
    pair<int, int> x = dfs(s, inf);
    result.first += x.first;
    result.second += x.second;
  }
  return result;
}

#define lo (o<<1)
#define ro (o<<1|1)

struct seg_t {
  int id[N << 2][2], from;

  void build(int l, int r, int o) {
    id[o][0] = ++node_cnt;
    id[o][1] = ++node_cnt;
    if (l == r) {
      ::add_edge(id[o][0], idr[l][from], inf, -l * 2);
      ::add_edge(id[o][1], idr[l][from], inf, l * 2);
    } else {
      int mid = l + r >> 1;
      build(l, mid, lo);
      build(mid + 1, r, ro);
      ::add_edge(id[o][0], id[lo][0], inf, 0);
      ::add_edge(id[o][0], id[ro][0], inf, 0);
      ::add_edge(id[o][1], id[lo][1], inf, 0);
      ::add_edge(id[o][1], id[ro][1], inf, 0);
    }
  }

  void add_edge(int l, int r, int o, int ql, int qr, int source, int cost, bool type) {
    if (ql <= l && r <= qr) {
      ::add_edge(source, id[o][type], 1, cost);
    } else {
      int mid = l + r >> 1;
      if (ql <= mid) {
        add_edge(l, mid, lo, ql, qr, source, cost, type);
      } if (qr > mid) {
        add_edge(mid + 1, r, ro, ql, qr, source, cost, type);
      }
    }
  }
} seg_tree[11];

int main() {
  scanf("%d%d", &n, &m);
  s = ++node_cnt;
  t = ++node_cnt;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &l[i][j]);
      ++l[i][j];
      idl[i][j] = ++node_cnt;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &r[i][j]);
      ++r[i][j];
      idr[i][j] = ++node_cnt;
    }
  }
  for (int i = 1; i <= m; ++i) {
    seg_tree[i].from = i;
    seg_tree[i].build(1, n, 1);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      add_edge(s, idl[i][j], 1, 0);
      add_edge(idr[i][j], t, 1, 0);
      if (l[i][j] <= i) {
        seg_tree[j].add_edge(1, n, 1, l[i][j], min(r[i][j], i), idl[i][j], i * 2, 0);
      }
      if (r[i][j] > i) {
        seg_tree[j].add_edge(1, n, 1, max(l[i][j], i + 1), r[i][j], idl[i][j], -i * 2, 1);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      add_edge(idr[i][j], idr[i][j == 1 ? m : j - 1], inf, 1);
      add_edge(idr[i][j], idr[i][j == m ? 1 : j + 1], inf, 1);
    }
  }
  pair<int, int> answer = solve();
  if (answer.first == n * m) {
    printf("%d\n", answer.second);
  } else {
    puts("no solution");
  }
  return 0;
}
