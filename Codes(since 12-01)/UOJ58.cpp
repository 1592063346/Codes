#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, M = 2100;

int n, m, q, a[N], v[N], w[N], sta[N], father[N], logv[N], de[20][N], id[20][N], firstp[N], block[N], number[N], total, tt, ttt;
long long answer[N], result;
bool visit[N];
vector<int> adj[N];

struct info_t {
  int u, v, id;

  info_t() {}
  info_t(int u, int v, int id): u(u), v(v), id(id) {}

  bool operator < (const info_t& a) const {
    return block[u] == block[a.u] ? block[v] == block[a.v] ? id < a.id : block[v] < block[a.v] : block[u] < block[a.u];
  }
};

vector<info_t> events, queries;

void dfs(int u, int p, int d) {
  firstp[u] = ++total;
  id[0][total] = u;
  de[0][total] = d;
  for (auto v : adj[u]) {
    if (v != p) {
      father[v] = u;
      dfs(v, u, d + 1);
      if (tt >= M) {
        ++ttt;
        while (tt) {
          block[sta[tt--]] = ttt;
        }
      }
      ++total;
      id[0][total] = u;
      de[0][total] = d;
    }
  }
  sta[++tt] = u;
}

void rmq_init() {
  for (int i = 2; i <= total; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= total; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= total; ++j) {
      int d1 = de[i - 1][j], d2 = de[i - 1][j + (1 << i - 1)];
      de[i][j] = min(d1, d2);
      id[i][j] = d1 < d2 ? id[i - 1][j] : id[i - 1][j + (1 << i - 1)];
    }
  }
}

int get_lca(int u, int v) {
  u = firstp[u];
  v = firstp[v];
  if (u > v) {
    swap(u, v);
  }
  int k = logv[v - u + 1];
  return de[k][u] < de[k][v - (1 << k) + 1] ? id[k][u] : id[k][v - (1 << k) + 1];
}

void get_all_blocks() {
  dfs(1, 0, 0);
  while (tt) {
    block[sta[tt--]] = ttt;
  }
}

void update(int u) {
  if (!visit[u]) {
    result += (long long) w[++number[a[u]]] * v[a[u]];
  } else {
    result -= (long long) w[number[a[u]]--] * v[a[u]];
  }
  visit[u] = !visit[u];
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &v[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &w[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  get_all_blocks();
  rmq_init();
  for (int i = 1; i <= q; ++i) {
    int opt, u, v;
    scanf("%d%d%d", &opt, &u, &v);
    if (opt == 0) {
      events.emplace_back(u, v, i);
      answer[i] = -1;
    } else {
      queries.emplace_back(u, v, i);
    }
  }
  sort(queries.begin(), queries.end());
  int pu = 1, pv = 1, pt = -1;
  for (int i = 0; i < queries.size(); ++i) {
    int lca = get_lca(queries[i].u, pu);
    for (int x = pu; x != lca; x = father[x]) {
      update(x);
    }
    for (int x = queries[i].u; x != lca; x = father[x]) {
      update(x);
    }
    lca = get_lca(queries[i].v, pv);
    for (int x = pv; x != lca; x = father[x]) {
      update(x);
    }
    for (int x = queries[i].v; x != lca; x = father[x]) {
      update(x);
    }
    pu = queries[i].u;
    pv = queries[i].v;
    for (; pt + 1 < events.size() && events[pt + 1].id < queries[i].id; ++pt) {
      if (visit[events[pt + 1].u]) {
        result -= (long long) w[number[a[events[pt + 1].u]]--] * v[a[events[pt + 1].u]];
        result += (long long) w[++number[events[pt + 1].v]] * v[events[pt + 1].v];
      }
      int old = a[events[pt + 1].u];
      a[events[pt + 1].u] = events[pt + 1].v;
      events[pt + 1].v = old;
    }
    for (; pt >= 0 && events[pt].id > queries[i].id; --pt) {
      if (visit[events[pt].u]) {
        result -= (long long) w[number[a[events[pt].u]]--] * v[a[events[pt].u]];
        result += (long long) w[++number[events[pt].v]] * v[events[pt].v];
      }
      int old = a[events[pt].u];
      a[events[pt].u] = events[pt].v;
      events[pt].v = old;
    }
    lca = get_lca(queries[i].u, queries[i].v);
    update(lca);
    answer[queries[i].id] = result;
    update(lca);
  }
  for (int i = 1; i <= q; ++i) {
    if (~answer[i]) {
      printf("%lld\n", answer[i]);
    }
  }
  return 0;
}
