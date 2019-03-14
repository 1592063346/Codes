#include<bits/stdc++.h>

using namespace std;

const int M = 1e3 + 10, N = 2e5 + 10, dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

int n, m, a[M][M], lim[N], father[N], rev[N], ch[N][2], addv[N << 2], minv[N << 2], mins[N << 2];
bool appeared[N];
pair<int, int> p[N];
map<int, bool> linked[N];

bool is_root(int u) {
  return !(ch[father[u]][0] == u) && !(ch[father[u]][1] == u);
}

int side(int f, int u) {
  return ch[f][1] == u;
}

void reverse(int u) {
  rev[u] = !rev[u];
  swap(ch[u][0], ch[u][1]);
}

void push(int u) {
  if (rev[u]) {
    if (ch[u][0]) {
      reverse(ch[u][0]);
    }
    if (ch[u][1]) {
      reverse(ch[u][1]);
    }
    rev[u] = 0;
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
}

void splay(int u) {
  vector<int> pstack(1, u);
  for (int i = u; !is_root(i); i = father[i]) {
    pstack.push_back(father[i]);
  }
  for (; pstack.size(); pstack.pop_back()) {
    push(pstack.back());
  }
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
    ch[u][1] = x;
  }
}

int find_root(int u) {
  access(u);
  splay(u);
  for (; ch[u][0]; u = ch[u][0]);
  splay(u);
  return u;
}

void make_root(int u) {
  access(u);
  splay(u);
  reverse(u);
}

void split(int u, int v) {
  make_root(u);
  access(v);
  splay(v);
}

void link(int u, int v) {
  make_root(u);
  father[u] = v;
}

void cut(int u, int v) {
  split(u, v);
  father[u] = ch[v][0] = 0;
}

bool check(int v) {
  vector<int> nodes;
  bool ok = true;
  for (int i = 0; i < 4; ++i) {
    int newx = p[v].first + dx[i], newy = p[v].second + dy[i];
    if (newx >= 1 && newx <= n && newy >= 1 && newy <= m) {
      int u = find_root(a[newx][newy]);
      if (appeared[u]) {
        ok = false;
      } else {
        appeared[u] = true;
        nodes.push_back(u);
      }
    }
  }
  for (auto v : nodes) {
    appeared[v] = false;
  }
  return ok;
}

void add(int o, int v) {
  addv[o] += v;
  minv[o] += v;
}

void push_down(int o) {
  if (addv[o]) {
    add(o << 1, addv[o]);
    add(o << 1 | 1, addv[o]);
    addv[o] = 0;
  }
}

void push_up(int o) {
  minv[o] = min(minv[o << 1], minv[o << 1 | 1]);
  mins[o] = 0;
  if (minv[o << 1] == minv[o]) {
    mins[o] += mins[o << 1];
  }
  if (minv[o << 1 | 1] == minv[o]) {
    mins[o] += mins[o << 1 | 1];
  }
}

void build(int l, int r, int o) {
  if (l == r) {
    mins[o] = 1;
  } else {
    int mid = l + r >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
    push_up(o);
  }
}

void modify(int l, int r, int o, int ql, int qr, int v) {
  if (ql <= l && r <= qr) {
    add(o, v);
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr, v);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    } else {
      modify(l, mid, o << 1, ql, qr, v);
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    }
    push_up(o);
  }
}

pair<int, int> query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return {minv[o], mins[o]};
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (qr <= mid) {
      return query(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      pair<int, int> x = query(l, mid, o << 1, ql, qr);
      pair<int, int> y = query(mid + 1, r, o << 1 | 1, ql, qr);
      if (x.first == y.first) {
        return {x.first, x.second + y.second};
      } else {
        return x.first < y.first ? x : y;
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &a[i][j]);
      p[a[i][j]] = {i, j};
    }
  }
  int all = n * m;
  for (int i = all, j = all; i; --i) {
    for (; j > 1 && check(j - 1); --j) {
      for (int k = 0; k < 4; ++k) {
        int newx = p[j - 1].first + dx[k], newy = p[j - 1].second + dy[k];
        if (newx >= 1 && newx <= n && newy >= 1 && newy <= m) {
          if (a[newx][newy] >= j - 1 && a[newx][newy] <= i) {
            link(a[newx][newy], j - 1);
            linked[a[newx][newy]][j - 1] = true;
          }
        }
      }
    }
    lim[i] = j;
    for (int k = 0; k < 4; ++k) {
      int newx = p[i].first + dx[k], newy = p[i].second + dy[k];
      if (newx >= 1 && newx <= n && newy >= 1 && newy <= m) {
        if (a[newx][newy] <= i && a[newx][newy] >= j && linked[i][a[newx][newy]]) {
          cut(i, a[newx][newy]);
        }
      }
    }
  }
  build(1, all, 1);
  long long answer = 0;
  for (int i = 1, j = 1; i <= all; ++i) {
    modify(1, all, 1, lim[i], i, 1);
    for (int j = 0; j < 4; ++j) {
      int newx = p[i].first + dx[j], newy = p[i].second + dy[j];
      if (newx >= 1 && newx <= n && newy >= 1 && newy <= m) {
        if (a[newx][newy] < i && lim[i] <= a[newx][newy]) {
          modify(1, all, 1, lim[i], a[newx][newy], -1);
        }
      }
    }
    pair<int, int> result = query(1, all, 1, lim[i], i);
    answer += (result.first == 1) * result.second;
  }
  printf("%lld\n", answer);
  return 0;
}
