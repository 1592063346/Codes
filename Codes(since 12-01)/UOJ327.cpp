#include<bits/stdc++.h>
#include "mythological.h"

using namespace std;

const int N = 1e5 + 10;

int anc[N][20], id[N], dist[N];
map<int, int> ch[N];

void init(int n, int m, int* a, int type) {
  int u = 0;
  a[0] = -1;
  for (int i = 1; i <= n; ++i) {
    if (a[i] == a[u]) {
      u = anc[u][0];
    } else {
      int& go = ch[u][a[i]];
      if (!go) {
        go = i;
        dist[go] = dist[u] + 1;
        anc[go][0] = u;
        for (int j = 1; (1 << j) <= n; ++j) {
          anc[go][j] = anc[anc[go][j - 1]][j - 1];
        }
      }
      u = ch[u][a[i]];
    }
    id[i] = u;
  }
}

int get_lca(int u, int v) {
  if (dist[u] < dist[v]) {
    swap(u, v);
  }
  for (int i = 18; ~i; --i) {
    if (dist[u] - (1 << i) >= dist[v]) {
      u = anc[u][i];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 18; ~i; --i) {
    if (anc[u][i] != anc[v][i]) {
      u = anc[u][i];
      v = anc[v][i];
    }
  }
  return anc[u][0];
}

int query(int l, int r) {
  int u = id[l - 1], v = id[r], lca = get_lca(u, v);
  return r - l + 1 - (dist[u] + dist[v] - (dist[lca] << 1));
}
