#include<bits/stdc++.h>

using namespace std;

const int N = 5e6 + 10;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

struct edge_t {
  int next, to;

  edge_t() {}
  edge_t(int next, int to): next(next), to(to) {}
} edges1[N], edges2[N];

int n, m, d, dfn[N], low[N], dfn_cnt, scc[N], kinds[N], s[N], f[N], top, scc_cnt, f1[N], e1, f2[N], e2;
bool open[100010][55], appeared[N];

void add1(int u, int v) {
  edges1[++e1] = edge_t(f1[u], v);
  f1[u] = e1;
}

void add2(int u, int v) {
  edges2[++e2] = edge_t(f2[u], v);
  f2[u] = e2;
}

int id(int x, int y) {
  return (x - 1) * d + y;
}

void tarjan(int u) {
  dfn[u] = low[u] = ++dfn_cnt;
  s[++top] = u;
  for (int i = f1[u]; i; i = edges1[i].next) {
    int v = edges1[i].to;
    if (!dfn[v]) {
      tarjan(v);
      cmin(low[u], low[v]);
    } else if (!scc[v]) {
      cmin(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    ++scc_cnt;
    int old = top;
    for (int x = -1; x != u; --top) {
      scc[x = s[top]] = scc_cnt;
      if (open[x / d + 1][x % d] && !appeared[x / d + 1]) {
        appeared[x / d + 1] = true;
        ++kinds[scc_cnt];
      }
    }
    for (int i = top + 1; i <= old; ++i) {
      appeared[s[i] / d + 1] = false;
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &d);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    for (int j = 0; j < d; ++j) {
      add1(id(x, j), id(y, (j + 1) % d));
    }
  }
  for (int i = 1; i <= n; ++i) {
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar());
    for (int t = 0; isdigit(ch); ch = getchar()) {
      open[i][t++] = ch - '0';
    }
  }
  tarjan(0);
  for (int i = 0; i < n * d; ++i) {
    for (int j = f1[i]; j; j = edges1[j].next) {
      int v = edges1[j].to;
      if (scc[i] != scc[v]) {
        add2(scc[i], scc[v]);
      }
    }
  }
  for (int i = 1; i <= scc_cnt; ++i) {
    for (int j = f2[i]; j; j = edges2[j].next) {
      int v = edges2[j].to;
      cmax(f[i], f[v]);
    }
    f[i] += kinds[i];
  }
  printf("%d\n", f[scc[0]]);
  return 0;
}
