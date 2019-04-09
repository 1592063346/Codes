#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

class node_t {
 public:
  int l, r, id, x, d;

  node_t() {
  }

  node_t(int id, int x): id(id), x(x) {
    l = r = 0;
    d = 1;
  }
} nodes[N];

int merge(int x, int y) {
  if (!x || !y) {
    return x | y;
  }
  if (nodes[x].x > nodes[y].x) {
    swap(x, y);
  }
  nodes[x].r = merge(nodes[x].r, y);
  if (nodes[nodes[x].l].d < nodes[nodes[x].r].d) {
    swap(nodes[x].l, nodes[x].r);
  }
  nodes[x].d = nodes[nodes[x].r].d + 1;
  return x;
}

int remove(int x) {
  return merge(nodes[x].l, nodes[x].r);
}

int n, m, tt, a[N], root[N], f[N];
bool died[N];

int find(int x) {
  return f[x] == x ? x : f[x] = find(f[x]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    f[i] = i;
    scanf("%d", &a[i]);
    nodes[++tt] = node_t(i, a[i]);
    root[i] = tt;
  }
  scanf("%d", &m);
  while (m--) {
    char cmd[3];
    scanf("%s", cmd);
    if (*cmd == 'M') {
      int x, y;
      scanf("%d%d", &x, &y);
      if (died[x] || died[y]) {
        continue;
      }
      x = find(x);
      y = find(y);
      if (x != y) {
        f[x] = y;
        root[y] = merge(root[x], root[y]);
      }
    } else {
      int x;
      scanf("%d", &x);
      if (died[x]) {
        puts("0");
        continue;
      }
      x = find(x);
      printf("%d\n", nodes[root[x]].x);
      died[nodes[root[x]].id] = true;
      root[x] = remove(root[x]);
    }
  }
  return 0;
}
