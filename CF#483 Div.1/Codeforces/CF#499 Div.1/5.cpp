#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, inf = 1e9;

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

int n, m, k, l0, r0, l1, r1, l2, r2, type, t_root, c[3][2];

struct state {
  int v[3], l[3], r[3], ch[2], value;

  state () {
    value = 1;
  }

  bool operator < (const state& a) const {
    return v[type] < a.v[type];
  }
} info[N];

#define lo info[o].ch[0]
#define ro info[o].ch[1]

void push_up(int u, int v) {
  for (int i = 0; i < 3; ++i) {
    cmin(info[u].l[i], info[v].l[i]);
    cmax(info[u].r[i], info[v].r[i]);
  }
  info[u].value += info[v].value;
}

int build(int l, int r, int opt) {
  type = opt;
  int o = l + r >> 1;
  nth_element(info + l, info + o, info + r + 1);
  for (int i = 0; i < 3; ++i) {
    info[o].l[i] = info[o].r[i] = info[o].v[i];
  }
  if (l < o) {
    lo = build(l, o - 1, (opt + 1) % 3);
    push_up(o, lo);
  }
  if (r > o) {
    ro = build(o + 1, r, (opt + 1) % 3);
    push_up(o, ro);
  }
  return o;
}

bool not_including(int o) {
  for (int i = 0; i < 3; ++i) {
    if (info[o].r[i] < c[i][0] || c[i][1] < info[o].l[i]) {
      return true;
    }
  }
  return false;
}

bool including_all(int o) {
  for (int i = 0; i < 3; ++i) {
    if (c[i][0] <= info[o].l[i] && info[o].r[i] <= c[i][1]) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

bool including_one(int o) {
  for (int i = 0; i < 3; ++i) {
    if (c[i][0] <= info[o].v[i] && info[o].v[i] <= c[i][1]) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

int query(int o) {
  if (not_including(o)) {
    return 0;
  } else if (including_all(o)) {
    return info[o].value;
  } else {
    int result = including_one(o);
    if (lo) {
      result += query(lo);
    }
    if (ro) {
      result += query(ro);
    }
    return result;
  }
}

int main() {
  scanf("%*d%*d%*d%d%d%d", &n, &m, &k);
  l0 = l1 = l2 = inf;
  for (int i = 1; i <= n; ++i) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    cmin(l0, x);
    cmin(l1, y);
    cmin(l2, z);
    cmax(r0, x);
    cmax(r1, y);
    cmax(r2, z);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &info[i].v[0], &info[i].v[1], &info[i].v[2]);
    if (info[i].v[0] >= l0 && info[i].v[0] <= r0 && info[i].v[1] >= l1 && info[i].v[1] <= r1 && info[i].v[2] >= l2 && info[i].v[2] <= r2) {
      return puts("INCORRECT"), 0;
    }
  }
  puts("CORRECT");
  t_root = build(1, m, 0);
  for (int i = 1; i <= k; ++i) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    if (x >= l0 && x <= r0 && y >= l1 && y <= r1 && z >= l2 && z <= r2) {
      puts("OPEN");
    } else {
      c[0][0] = min(l0, x);
      c[1][0] = min(l1, y);
      c[2][0] = min(l2, z);
      c[0][1] = max(r0, x);
      c[1][1] = max(r1, y);
      c[2][1] = max(r2, z);
      puts(query(t_root) ? "CLOSED" : "UNKNOWN");
    }
  }
  return 0;
}
