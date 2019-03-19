#include<bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

int n, q, a[N], father[N], p[N], ch[N][2], tran[N][2], s[N];
vector<int> adj[N];

void dfs(int u) {
  for (auto v : adj[u]) {
    if (v <= n) {
      dfs(v);
    }
    s[u] += a[v];
  }
  a[u] = s[u] >= 2;
  tran[u][0] = s[u] >= 2;
  tran[u][1] = s[u] >= 1;
}

bool is_root(int u) {
  return ch[father[u]][0] != u && ch[father[u]][1] != u;
}

int side(int f, int u) {
  return ch[f][1] == u;
}

void pull(int u) {
  tran[u][0] = s[u] >= 2;
  tran[u][1] = s[u] >= 1;
  if (ch[u][1]) {
    if (tran[ch[u][1]][0]) {
      tran[u][0] = tran[u][1];
    } else if (!tran[ch[u][1]][1]) {
      tran[u][1] = tran[u][0];
    }
  }
  if (ch[u][0]) {
    if (tran[u][0]) {
      tran[u][0] = tran[u][1] = tran[ch[u][0]][1];
    } else if (!tran[u][1]) {
      tran[u][0] = tran[u][1] = tran[ch[u][0]][0];
    } else {
      tran[u][0] = tran[ch[u][0]][0];
      tran[u][1] = tran[ch[u][0]][1];
    }
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
      s[u] += tran[ch[u][1]][0];
    }
    ch[u][1] = x;
    if (ch[u][1]) {
      s[u] -= tran[ch[u][1]][0];
    }
    pull(u);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    if (x) {
      p[x] = i;
      father[x] = i;
      adj[i].push_back(x);
    }
    if (y) {
      p[y] = i;
      father[y] = i;
      adj[i].push_back(y);
    }
    if (z) {
      p[z] = i;
      father[z] = i;
      adj[i].push_back(z);
    }
  }
  for (int i = 1; i <= 2 * n + 1; ++i) {
    scanf("%d", &a[n + i]);
  }
  dfs(1);
  scanf("%d", &q);
  while (q--) {
    int x;
    scanf("%d", &x);
    access(p[x]);
    splay(p[x]);
    s[p[x]] += a[x] ? -1 : 1;
    a[x] = !a[x];
    pull(p[x]);
    splay(1);
    printf("%d\n", tran[1][0]);
  }
  return 0;
}
