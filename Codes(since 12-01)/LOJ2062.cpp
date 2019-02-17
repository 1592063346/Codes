#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, M = 316;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, m, q, newp, a[N], dfn[N], edfn[N], adfn[N], low[N], h[N], inblock[N], t, dfn_cnt, times[N], number[2][N], answer[N];
vector<int> pstack, graph[N], new_graph[N];

void add_edge(int u, int v) {
  new_graph[u].push_back(v);
  new_graph[v].push_back(u);
}

void tarjan(int u, int father) {
  dfn[u] = low[u] = ++dfn_cnt;
  pstack.push_back(u);
  for (auto v : graph[u]) {
    if (v != father) {
      if (!dfn[v]) {
        tarjan(v, u);
        cmin(low[u], low[v]);
        if (low[v] >= dfn[u]) {
          add_edge(u, ++newp);
          while (1) {
            int x = pstack.back();
            pstack.pop_back();
            add_edge(newp, x);
            if (x == v) {
              break;
            }
          }
        }
      } else if (dfn[v] < dfn[u]) {
        cmin(low[u], dfn[v]);
      }
    }
  }
}

void dfs(int u, int father) {
  if (u <= n) {
    dfn[u] = ++dfn_cnt;
    adfn[dfn_cnt] = u;
  }
  for (auto v : new_graph[u]) {
    if (v != father) {
      dfs(v, u);
    }
  }
  if (u <= n) {
    edfn[u] = dfn_cnt;
  }
}

void add(int opt, int c) {
  ++number[opt][inblock[c]];
}

void del(int opt, int c) {
  --number[opt][inblock[c]];
}

void update_color(int c, int type) {
  if (times[c]) {
    del(times[c] & 1, c);
  }
  times[c] += type;
  if (times[c]) {
    add(times[c] & 1, c);
  }
}

int query_color(int opt, int r) {
  int up = max(0, inblock[r] - 1), result = 0;
  for (int i = 1; i <= up; ++i) {
    result += number[opt][i];
  }
  for (int i = up * M + 1; i <= r; ++i) {
    result += (times[i] && (times[i] & 1) == opt);
  }
  return result;
}

struct query_t {
  int l, r, opt, y, id;

  query_t() {}
  query_t(int l, int r, int opt, int y, int id): l(l), r(r), opt(opt), y(y), id(id) {}
};

int main() {
  scanf("%d%d", &n, &m);
  newp = n;
  for (int i = 1; i <= n; ++i) {
    inblock[i] = (i - 1) / M + 1;
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    h[++t] = a[i];
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(h + 1, h + 1 + t, a[i]) - h;
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  tarjan(1, 0);
  dfn_cnt = 0;
  dfs(1, 0);
  scanf("%d", &q);
  vector<query_t> queries;
  for (int i = 1; i <= q; ++i) {
    int opt, x, y;
    scanf("%d%d%d", &opt, &x, &y);
    y = upper_bound(h + 1, h + 1 + t, y) - h - 1;
    queries.emplace_back(dfn[x], edfn[x], opt, y, i);
  }
  sort(queries.begin(), queries.end(), [&] (const query_t& a, const query_t& b) {
    return inblock[a.l] == inblock[b.l] ? a.r < b.r : inblock[a.l] < inblock[b.l];
  });
  int ql = 1, qr = 0;
  for (auto que : queries) {
    for (; qr < que.r; update_color(a[adfn[++qr]], 1));
    for (; qr > que.r; update_color(a[adfn[qr--]], -1));
    for (; ql < que.l; update_color(a[adfn[ql++]], -1));
    for (; ql > que.l; update_color(a[adfn[--ql]], 1));
    answer[que.id] = query_color(que.opt, que.y);
  }
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
