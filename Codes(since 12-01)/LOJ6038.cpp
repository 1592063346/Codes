#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

int type, n, q, lastans, f[N];
pair<int, int> dir[N];

int find(int x) {
  return f[x] == x ? x : f[x] = find(f[x]);
}

#define lo ch[o][0]
#define ro ch[o][1]

int ch[N][2], pa[N], size[N], rev_tag[N];

bool isroot(int o) {
  int p = pa[o];
  return ch[p][0] ^ o && ch[p][1] ^ o;
}

int side(int o, int p) {
  return ch[p][1] == o;
}

void reverse(int o) {
  swap(lo, ro);
  rev_tag[o] ^= 1;
}

void push_up(int o) {
  size[o] = size[lo] + size[ro] + 1;
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
  int p = pa[o], to = side(o, p), topa = side(p, pa[p]);
  int ano_ch = ch[o][to ^ 1];
  pa[o] = pa[p];
  if (!isroot(p)) {
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
  if (!isroot(o)) {
    push(pa[o]);
  }
  push_down(o);
}

void splay(int o) {
  push(o);
  while (!isroot(o)) {
    int p = pa[o];
    if (!isroot(p)) {
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

void make_root(int o) {
  access(o);
  splay(o);
  reverse(o);
}

void link(int u, int v) {
  make_root(u);
  pa[u] = v;
}

void debug(int o) {
  if (!o) {
    return;
  }
  debug(lo);
  printf("%d ", o);
  debug(ro);
}

int query(int u, int v) {
  make_root(u);
  access(v);
  splay(v);
  return size[v] - 1;
}

void merge(int u, int v) {
  link(u, v);
  int x = find(u), y = find(v);
  f[x] = y;
  vector<pair<int, pair<int, int> > > sorted;
  sorted.emplace_back(query(dir[x].first, dir[x].second), make_pair(dir[x].first, dir[x].second));
  sorted.emplace_back(query(dir[x].first, dir[y].first), make_pair(dir[x].first, dir[y].first));
  sorted.emplace_back(query(dir[x].first, dir[y].second), make_pair(dir[x].first, dir[y].second));
  sorted.emplace_back(query(dir[x].second, dir[y].first), make_pair(dir[x].second, dir[y].first));
  sorted.emplace_back(query(dir[x].second, dir[y].second), make_pair(dir[x].second, dir[y].second));
  sorted.emplace_back(query(dir[y].first, dir[y].second), make_pair(dir[y].first, dir[y].second));
  sort(sorted.begin(), sorted.end());
  dir[y] = sorted.back().second;
}

int best_path(int u) {
  int x = find(u);
  return max(query(u, dir[x].first), query(u, dir[x].second));
}

int main() {
  scanf("%d%d%d", &type, &n, &q);
  for (int i = 1; i <= n; ++i) {
    f[i] = i;
    size[i] = 1;
    dir[i] = pair<int, int> (i, i);
  }
  for (int i = 1; i <= q; ++i) {
    int opt, u, v;
    scanf("%d", &opt);
    if (opt == 1) {
      scanf("%d%d", &u, &v);
      u ^= type * lastans;
      v ^= type * lastans;
      merge(u, v);
    } else {
      scanf("%d", &u);
      u ^= type * lastans;
      printf("%d\n", lastans = best_path(u));
    }
  }
  return 0;
}
