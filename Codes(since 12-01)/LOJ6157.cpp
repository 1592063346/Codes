#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

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

int tt, n, m, father[N], value[N];
vector<int> adj[N];

int find(int x) {
  if (father[x] == x) {
    return x;
  } else {
    int p = find(father[x]);
    value[x] ^= value[father[x]];
    return father[x] = p;
  }
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
      father[i] = i;
      value[i] = 0;
    }
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    bool impossible = false;
    while (m--) {
      int s, t, w;
      scanf("%d%d%d", &s, &t, &w);
      int x = find(s), y = find(t);
      if (x != y) {
        value[x] = w ^ value[s] ^ value[t];
        father[x] = y;
      } else {
        if (w != (value[s] ^ value[t])) {
          impossible = true;
        }
      }
    }
    if (impossible) {
      puts("Impossible");
    } else {
      int minv = 1 << 16, maxv = 0;
      for (int i = 1; i <= n; ++i) {
        for (auto j : adj[i]) {
          if (find(i) != find(j)) {
            puts("No");
            goto next_test_case;
          } else {
            cmin(minv, value[i] ^ value[j]);
            cmax(maxv, value[i] ^ value[j]);
          }
        }
      }
      printf("%d %d\n", minv, maxv);
    }
    next_test_case: continue;
  }
  return 0;
}
