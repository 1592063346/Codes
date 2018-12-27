#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n, m, k, ch[N][2], pa[N], size[N], virtual_size[N], value[N], rev_tag[N], type[N];
long long f_l[N], f_r[N], virtual_f[N], w[N];
char cmd[3];

#define lo ch[o][0]
#define ro ch[o][1]

bool is_root(int o) {
  int p = pa[o];
  return ch[p][0] ^ o && ch[p][1] ^ o;
}

int side(int o, int p) {
  return ch[p][1] == o;
}

void reverse(int o) {
  int p = pa[o];
  if (is_root(o) && p) {
    virtual_f[p] -= f_l[o];
    virtual_f[p] += f_r[o];
  }
  swap(lo, ro);
  swap(f_l[o], f_r[o]);
  rev_tag[o] ^= 1;
}

void push_up(int o) {
  w[o] = w[lo] + w[ro] + value[o];
  size[o] = size[lo] + size[ro] + virtual_size[o] + type[o];
  f_l[o] = f_l[lo] + f_l[ro] + virtual_f[o] + (size[ro] + virtual_size[o] + type[o]) * (w[lo] + value[o]);
  f_r[o] = f_r[lo] + f_r[ro] + virtual_f[o] + (size[lo] + virtual_size[o] + type[o]) * (w[ro] + value[o]);
}

void push_down(int o) {
  if (rev_tag[o]) {
    if (lo) {
      reverse(lo);
    }
    if (ro) {
      reverse(ro);
    }
    rev_tag[o] = 0;
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

void push(int o) {
  if (!is_root(o)) {
    push(pa[o]);
  }
  push_down(o);
}

void splay(int o) {
  push(o);
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
    virtual_size[o] += size[ro];
    virtual_f[o] += f_l[ro];
    ro = p;
    virtual_size[o] -= size[ro];
    virtual_f[o] -= f_l[ro];
    push_up(o);
  }
}

void make_root(int o) {
  access(o);
  splay(o);
  reverse(o);
}

void split(int u, int v) {
  make_root(u);
  access(v);
  splay(v);
}

void link(int u, int v) {
  make_root(u);
  make_root(v);
  pa[u] = v;
  virtual_size[v] += size[u];
  virtual_f[v] += f_l[u];
  push_up(v);
}

void cut(int u, int v) {
  split(u, v);
  int l_ch = ch[v][0];
  ch[v][0] = pa[l_ch] = 0;
  push_up(v);
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    ++n;
    ::w[n] = value[n] = w;
    link(u, n);
    link(v, n);
  }
  for (int i = 1; i <= k; ++i) {
    int u, v, w;
    scanf("%s", cmd);
    if (*cmd == 'L') {
      scanf("%d%d%d", &u, &v, &w);
      ++n;
      ::w[n] = value[n] = w;
      link(u, n);
      link(v, n);
    } else if (*cmd == 'C') {
      scanf("%d%d", &u, &v);
      split(u, v);
      int linked = ch[v][0];
      if (ch[linked][1]) {
        linked = ch[linked][1];
      }
      cut(u, linked);
      cut(v, linked);
    } else if (*cmd == 'F') {
      scanf("%d", &u);
      make_root(u);
      type[u] ^= 1;
      push_up(u);
    } else {
      scanf("%d", &u);
      make_root(u);
      printf("%lld\n", f_l[u]);
    }
  }
  return 0;
}
