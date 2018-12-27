#include<bits/stdc++.h>

using namespace std;

#define rg register

template<typename T> inline bool checkMax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}

template<typename T> inline bool checkMin(T& a, const T& b) {
  return a > b ? a = b, true : false;
}

const int N = 1e5 + 10;

struct Edge {
  Edge* next;
  int to;
  Edge () {}
  Edge (Edge* next, int to): next(next), to(to) {}
} *first[N], pool[N << 1], *pis = pool;

inline void add(int u, int v) {
  first[u] = new (pis++) Edge (first[u], v);
  first[v] = new (pis++) Edge (first[v], u);
}

int n, q, logv[N << 1], dep[N], d[N << 1][20], id[N << 1][20], pos[N], len, dfn[2][N][20], dfn_p[2][N][20], dfn_cnt;

inline void dfs(int u, int pa) {
  pos[u] = ++len;
  dfn[0][u][0] = dfn[1][u][0] = ++dfn_cnt;
  dfn_p[0][u][0] = dfn_p[1][u][0] = u;
  d[len][0] = dep[u], id[len][0] = u;
  for (Edge* now = first[u]; now; now = now->next) {
    if (now->to ^ pa) {
      dep[now->to] = dep[u] + 1;
      dfs(now->to, u);
      d[++len][0] = dep[u], id[len][0] = u;
    }
  }
}

void rmq_init() {
  for (rg int i = 2; i <= len; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (rg int j = 1; (1 << j) <= len; ++j) {
    for (rg int i = 1; i + (1 << j) - 1 <= len; ++i) {
      int vl = d[i][j - 1], vr = d[i + (1 << j - 1)][j - 1];
      d[i][j] = min(vl, vr);
      id[i][j] = vl <= vr ? id[i][j - 1] : id[i + (1 << j - 1)][j - 1];
    }
  }
  for (rg int j = 1; (1 << j) <= n; ++j) {
    for (rg int i = 1; i + (1 << j) - 1 <= n; ++i) {
      int vl = dfn[0][i][j - 1], vr = dfn[0][i + (1 << j - 1)][j - 1];
      dfn[0][i][j] = min(vl, vr);
      dfn_p[0][i][j] = vl <= vr ? dfn_p[0][i][j - 1] : dfn_p[0][i + (1 << j - 1)][j - 1];
      vl = dfn[1][i][j - 1], vr = dfn[1][i + (1 << j - 1)][j - 1];
      dfn[1][i][j] = max(vl, vr);
      dfn_p[1][i][j] = vl >= vr ? dfn_p[1][i][j - 1] : dfn_p[1][i + (1 << j - 1)][j - 1];
    }
  }
}

inline int get_lca(int u, int v) {
  int l = pos[u], r = pos[v];
  if (l > r) {
    swap(l, r);
  }
  int k = logv[r - l + 1];
  return d[l][k] <= d[r - (1 << k) + 1][k] ? id[l][k] : id[r - (1 << k) + 1][k];
}

inline int query(int l, int r, int type) {
  int k = logv[r - l + 1];
  if (type == 0) {
    return dfn[0][l][k] <= dfn[0][r - (1 << k) + 1][k] ? dfn_p[0][l][k] : dfn_p[0][r - (1 << k) + 1][k];
  } else {
    return dfn[1][l][k] >= dfn[1][r - (1 << k) + 1][k] ? dfn_p[1][l][k] : dfn_p[1][r - (1 << k) + 1][k];
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (rg int i = 2; i <= n; ++i) {
    int x; scanf("%d", &x);
    add(i, x);
  }
  dfs(1, 0);
  rmq_init();
  for (rg int i = 1; i <= q; ++i) {
    int l, r; scanf("%d%d", &l, &r);
    int ansp, ansd;
    int p = query(l, r, 0);
    if (p == l) {
      int sec = query(p + 1, r, 0);
      int best = query(p + 1, r, 1);
      ansp = p, ansd = dep[get_lca(sec, best)];
    } else if (p == r) {
      int sec = query(l, p - 1, 0);
      int best = query(l, p - 1, 1);
      ansp = p, ansd = dep[get_lca(sec, best)];
    } else {
      int sec1 = query(l, p - 1, 0), sec2 = query(p + 1, r, 0);
      int best1 = query(l, p - 1, 1), best2 = query(p + 1, r, 1);
      int sec = dfn[0][sec1][0] < dfn[0][sec2][0] ? sec1 : sec2;
      int best = dfn[0][best1][0] > dfn[0][best2][0] ? best1 : best2;
      ansp = p, ansd = dep[get_lca(sec, best)];
    }
    p = query(l, r, 1);
    if (p == l) {
      int sec = query(p + 1, r, 1);
      int best = query(p + 1, r, 0);
      if (dep[get_lca(sec, best)] > ansd) {
        ansp = p, ansd = dep[get_lca(sec, best)];
      }
    } else if (p == r) {
      int sec = query(l, p - 1, 1);
      int best = query(l, p - 1, 0);
      if (dep[get_lca(sec, best)] > ansd) {
        ansp = p, ansd = dep[get_lca(sec, best)];
      }
    } else {
      int sec1 = query(l, p - 1, 1), sec2 = query(p + 1, r, 1);
      int best1 = query(l, p - 1, 0), best2 = query(p + 1, r, 0);
      int sec = dfn[0][sec1][0] > dfn[0][sec2][0] ? sec1 : sec2;
      int best = dfn[0][best1][0] < dfn[0][best2][0] ? best1 : best2;
      if (dep[get_lca(sec, best)] > ansd) {
        ansp = p, ansd = dep[get_lca(sec, best)];
      }
    }
    printf("%d %d\n", ansp, ansd);
  }
  return 0;
}
