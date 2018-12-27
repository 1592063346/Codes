#include<bits/stdc++.h>
#include "rts.h"

using namespace std;

const int N = 3e5 + 10;

#define lo ch[o][0]
#define ro ch[o][1]

int ch[N][2], l[N], r[N], pa[N], id[N];
bool visit[N];

bool is_root(int o) {
  int p = pa[o];
  return ch[p][0] ^ o && ch[p][1] ^ o;
}

int side(int o, int p) {
  return ch[p][1] == o;
}

void push_up(int o) {
  l[o] = r[o] = o;
  if (lo) {
    l[o] = l[lo];
  }
  if (ro) {
    r[o] = r[ro];
  }
}

void rotate(int o) {
  int p = pa[o], to = side(o, p), topa = side(p, pa[p]), ano_ch = ch[o][to ^ 1];
  pa[o] = pa[p];
  if (!is_root(p)) {
    ch[pa[p]][topa] = o;
  }
  pa[ano_ch] = p;
  ch[p][to] = ano_ch;
  pa[p] = o;
  ch[o][to ^ 1] = p;
  push_up(p);
  push_up(o);
}

void splay(int o) {
  while (!is_root(o)) {
    int p = pa[o];
    if (!is_root(p)) {
      if (side(o, p) == side(p, pa[p])) {
        rotate(p);
      }
    }
    rotate(o);
  }
}

void access(int o) {
  for (int p = 0; o; p = o, o = pa[o]) {
    splay(o);
    ro = p;
    push_up(o);
  }
}

void link(int u, int v) {
  pa[u] = v;
}

int find_root(int o) {
  for (; !is_root(o); o = pa[o]);
  return o;
}

void play(int n, int T, int dataType) {
  l[1] = r[1] = 1;
  visit[1] = true;
  for (int i = 2; i <= n; ++i) {
    id[i] = i;
  }
  random_shuffle(id + 2, id + n + 1);
  int l_node = 1, r_node = 1;
  for (int i = 2; i <= n; ++i) {
    int goal = id[i];
    if (!visit[goal]) {
      if (dataType ^ 3) {
        int o = find_root(1), go = explore(o, goal);
        while (go ^ goal) {
          if (go == r[lo]) {
            o = lo;
          } else if (go == l[ro]) {
            o = ro;
          } else {
            if (!visit[go]) {
              l[go] = r[go] = go;
              visit[go] = true;
              link(go, o);
              o = go;
            } else {
              o = find_root(go);
            }
          }
          go = explore(o, goal);
        }
        access(o);
      } else {
        int go = explore(l_node, goal);
        if (visit[go]) {
          while (r_node ^ goal) {
            r_node = explore(r_node, goal);
            visit[r_node] = true;
          }
        } else {
          visit[go] = true;
          l_node = go;
          while (l_node ^ goal) {
            l_node = explore(l_node, goal);
            visit[l_node] = true;
          }
        }
      }
    }
  }
}
