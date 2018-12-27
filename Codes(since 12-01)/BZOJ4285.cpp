#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, q, f[N][20], dfn[N], dep[N], size[N], dfn_cnt, event_cnt, ans[N * 5];
vector<int> graph[N];

inline void dfs(int u, int pa) {
  size[u] = 1;
  dfn[u] = ++dfn_cnt;
  for (int i = 1; (1 << i) <= n; ++i) {
    f[u][i] = f[f[u][i - 1]][i - 1];
  }
  for (int i = 0; i < graph[u].size(); ++i) {
    int v = graph[u][i];
    if (v ^ pa) {
      f[v][0] = u;
      dep[v] = dep[u] + 1;
      dfs(v, u);
      size[u] += size[v];
    }
  }
}

inline int getlca(int u, int v) {
  if (dep[u] < dep[v]) {
    swap(u, v);
  }
  for (int i = 19; ~i; --i) {
    if (dep[u] - (1 << i) >= dep[v]) {
      u = f[u][i];
    }
  }
  if (u == v) {
    return u;
  } else {
    for (int i = 19; ~i; --i) {
      if (f[u][i] ^ f[v][i]) {
        u = f[u][i];
        v = f[v][i];
      }
    }
    return f[u][0];
  }
}

inline int jump(int u, int d) {
  for (int i = 19; ~i; --i) {
    if (d >= (1 << i)) {
      u = f[u][i];
      d -= 1 << i;
    }
  }
  return u;
}

int c[N], tag[N], now;

inline void modify(int p, int value) {
  for (; p <= n; p += p & -p) {
    if (tag[p] ^ now) {
      tag[p] = now;
      c[p] = value;
    } else {
      c[p] += value;
    }
  }
}

inline int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    if (tag[p] == now) {
      result += c[p];
    }
  }
  return result;
}

inline int query(int l, int r) {
  return query(r) - query(l - 1);
}

struct event {
  int type, x, y, l, r, opt, id, _time;
  event () {}
  event (int type, int x, int y, int l, int r, int opt, int id, int _time): type(type), x(x), y(y), l(l), r(r), opt(opt), id(id), _time(_time) {}
  bool operator < (const event& a) const {
    if (x == a.x) {
      return _time < a._time;
    } else {
      return x < a.x;
    }
  }
} events[N * 6], tmp[N * 6];

inline void cdq(int l, int r) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1, p1 = l - 1, p2 = mid;
  for (int i = l; i <= r; ++i) {
    if (events[i]._time <= mid) {
      tmp[++p1] = events[i];
    } else {
      tmp[++p2] = events[i];
    }
  }
  for (int i = l; i <= r; ++i) {
    events[i] = tmp[i];
  }
  cdq(l, mid);
  cdq(mid + 1, r);
  ++now;
  p1 = l, p2 = mid + 1;
  for (int i = l; i <= r; ++i) {
    if (p2 > r || (p1 <= mid && events[p1] < events[p2])) {
      if (events[p1].type == 0 && events[p1]._time <= mid) {
        modify(events[p1].y, events[p1].opt);
      } else if (events[p1].type == 1 && events[p1]._time > mid) {
        ans[events[p1].id] += events[p1].opt * query(events[p1].l, events[p1].r);
      }
      tmp[i] = events[p1++];
    } else {
      if (events[p2].type == 0 && events[p2]._time <= mid) {
        modify(events[p2].y, events[p2].opt);
      } else if (events[p2].type == 1 && events[p2]._time > mid) {
        ans[events[p2].id] += events[p2].opt * query(events[p2].l, events[p2].r);
      }
      tmp[i] = events[p2++];
    }
  }
  for (int i = l; i <= r; ++i) {
    events[i] = tmp[i];
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs(1, 0);
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    ++event_cnt, events[event_cnt] = event (0, dfn[u], dfn[v], 0, 0, 1, 0, event_cnt);
    ++event_cnt, events[event_cnt] = event (0, dfn[v], dfn[u], 0, 0, 1, 0, event_cnt);
  }
  scanf("%d", &q);
  int query_cnt = 0;
  for (int i = 1; i <= q; ++i) {
    int type, u, v;
    scanf("%d%d%d", &type, &u, &v);
    if (type == 3) {
      ++query_cnt;
      if (dep[u] > dep[v]) {
        swap(u, v);
      }
      int lca = getlca(u, v);
      if (lca == u) {
        int x = jump(v, dep[v] - dep[u] - 1);
        ++event_cnt, events[event_cnt] = event (1, dfn[v] - 1, 0, 1, dfn[x] - 1, -1, query_cnt, event_cnt);
        ++event_cnt, events[event_cnt] = event (1, dfn[v] - 1, 0, dfn[x] + size[x], n, -1, query_cnt, event_cnt);
        ++event_cnt, events[event_cnt] = event (1, dfn[v] + size[v] - 1, 0, 1, dfn[x] - 1, 1, query_cnt, event_cnt);
        ++event_cnt, events[event_cnt] = event (1, dfn[v] + size[v] - 1, 0, dfn[x] + size[x], n, 1, query_cnt, event_cnt);
      } else {
        ++event_cnt, events[event_cnt] = event (1, dfn[v] - 1, 0, dfn[u], dfn[u] + size[u] - 1, -1, query_cnt, event_cnt);
        ++event_cnt, events[event_cnt] = event (1, dfn[v] + size[v] - 1, 0, dfn[u], dfn[u] + size[u] - 1, 1, query_cnt, event_cnt);
      }
    } else {
      ++event_cnt, events[event_cnt] = event (0, dfn[u], dfn[v], 0, 0, type == 1 ? 1 : -1, 0, event_cnt);
      ++event_cnt, events[event_cnt] = event (0, dfn[v], dfn[u], 0, 0, type == 1 ? 1 : -1, 0, event_cnt);
    }
  }
  cdq(1, event_cnt);
  for (int i = 1; i <= query_cnt; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
