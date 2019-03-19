#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, inf = 0x3f3f3f3f;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, m, a[N], g[N][2], father[N], ch[N][2];
vector<int> adj[N];

struct matrix_t {
  int a[4][4];

  matrix_t() {
    memset(a, 0xc0, sizeof a);
  }

  void init(int a0, int a1) {
    a[0][0] = a[0][1] = a0;
    a[1][0] = a1;
    a[1][1] = -inf;
  }

  matrix_t operator * (const matrix_t& b) const {
    matrix_t result;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 2; ++k) {
          cmax(result.a[i][j], a[i][k] + b.a[k][j]);
        }
      }
    }
    return result;
  }

  int query() {
    int result = -inf;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        cmax(result, a[i][j]);
      }
    }
    return result;
  }
} f[N];

bool is_root(int u) {
  return ch[father[u]][0] != u && ch[father[u]][1] != u;
}

int side(int f, int u) {
  return ch[f][1] == u;
}

void pull(int u) {
  f[u].init(g[u][0], g[u][1]);
  if (ch[u][0]) {
    f[u] = f[ch[u][0]] * f[u];
  }
  if (ch[u][1]) {
    f[u] = f[u] * f[ch[u][1]];
  }
}

void rotate(int u) {
  int f = father[u], s1 = side(f, u), s2 = side(father[f], f), ano = ch[u][!s1];
  father[u] = father[f];
  if (!is_root(f)) {
    ch[father[f]][s2] = u;
  }
  father[ano] = f;
  ch[f][s1] = ano;
  father[f] = u;
  ch[u][!s1] = f;
  pull(f);
  pull(u);
}

void splay(int u) {
  for (; !is_root(u); rotate(u)) {
    if (!is_root(father[u])) {
      if (side(father[u], u) == side(father[father[u]], father[u])) {
        rotate(father[u]);
      } else {
        rotate(u);
      }
    }
  }
}

void access(int u) {
  for (int x = 0; u; x = u, u = father[u]) {
    splay(u);
    if (ch[u][1]) {
      g[u][0] += f[ch[u][1]].query();
      g[u][1] += max(f[ch[u][1]].a[0][0], f[ch[u][1]].a[0][1]);
    }
    ch[u][1] = x;
    if (ch[u][1]) {
      g[u][0] -= f[ch[u][1]].query();
      g[u][1] -= max(f[ch[u][1]].a[0][0], f[ch[u][1]].a[0][1]);
    }
    pull(u);
  }
}

void dfs(int u, int p) {
  g[u][1] = a[u];
  for (auto v : adj[u]) {
    if (v != p) {
      father[v] = u;
      dfs(v, u);
      g[u][0] += max(g[v][0], g[v][1]);
      g[u][1] += g[v][0];
    }
  }
  pull(u);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 0);
  while (m--) {
    int x, y;
    scanf("%d%d", &x, &y);
    access(x);
    splay(x);
    g[x][1] += y - a[x];
    a[x] = y;
    pull(x);
    splay(1);
    printf("%d\n", f[1].query());
  }
  return 0;
}
