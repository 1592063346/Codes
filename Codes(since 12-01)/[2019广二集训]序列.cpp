#include<bits/stdc++.h>

using namespace std;

const int N = 234567;

struct query_t {
  int d, k, id;

  bool operator < (const query_t& a) const {
    return d < a.d;
  }
} queries[N * 5];

int n, m, q, last, t, tt, arr[N], a[N], size[N], father[N], len[N], ed[N], pos[N], answer[N * 5];
map<int, int> ch[N], adj[N];
map<int, vector<int>> events;

int new_node(int from) {
  len[++tt] = len[from] + 1;
  return tt;
}

int extend(int c, int i) {
  int p = last, np = new_node(p);
  ed[np] = i;
  while (p && !ch[p][c]) {
    ch[p][c] = np;
    p = father[p];
  }
  if (!p) {
    father[np] = 1;
  } else {
    int q = ch[p][c];
    if (len[p] + 1 == len[q]) {
      father[np] = q;
    } else {
      int nq = new_node(p);
      ch[nq] = ch[q];
      ed[nq] = ed[q];
      father[nq] = father[q];
      father[np] = father[q] = nq;
      while (p && ch[p][c] == q) {
        ch[p][c] = nq;
        p = father[p];
      }
    }
  }
  return last = np;
}

void dfs(int x) {
  arr[++t] = x;
  size[x] = 1;
  for (auto y : adj[x]) {
    dfs(y.second);
    size[x] += size[y.second];
  }
}

namespace splay {
int root, ch[N][2], father[N], foo[N], bar[N];

int side(int x) {
  int f = father[x];
  return ch[f][1] == x;
}

void pull(int x) {
  foo[x] = foo[ch[x][0]] + foo[ch[x][1]] + 1;
  bar[x] = bar[ch[x][0]] + bar[ch[x][1]] + (pos[x] != 0);
}

void rotate(int x) {
  int f = father[x], to = side(x), ano = ch[x][!to], tof = side(f);
  father[x] = father[f];
  ch[father[f]][tof] = x;
  father[ano] = f;
  ch[f][to] = ano;
  father[f] = x;
  ch[x][!to] = f;
  pull(f);
  pull(x);
}

void splay(int x, int y) {
  while (father[x] != y) {
    int f = father[x];
    if (father[f] != y) {
      if (side(x) == side(f)) {
        rotate(f);
      } else {
        rotate(x);
      }
    }
    rotate(x);
  }
  if (!y) {
    root = x;
  }
}

int build(int x, int y) {
  if (x > y) {
    return 0;
  }
  int mid = arr[x + y >> 1];
  ch[mid][0] = build(x, (x + y >> 1) - 1);
  ch[mid][1] = build((x + y >> 1) + 1, y);
  if (ch[mid][0]) {
    father[ch[mid][0]] = mid;
  }
  if (ch[mid][1]) {
    father[ch[mid][1]] = mid;
  }
  pull(mid);
  return mid;
}

int find_rank(int x) {
  splay(x, 0);
  return foo[ch[x][0]] + 1;
}

int find_kth(int x, int k) {
  if (foo[ch[x][0]] + 1 == k) {
    return x;
  } else if (foo[ch[x][0]] >= k) {
    return find_kth(ch[x][0], k);
  } else {
    return find_kth(ch[x][1], k - foo[ch[x][0]] - 1);
  }
}

int find_answer(int x, int k) {
  if (bar[ch[x][0]] + 1 == k) {
    return pos[x] ? x : find_answer(ch[x][1], 1);
  } else if (bar[ch[x][0]] >= k) {
    return find_answer(ch[x][0], k);
  } else {
    return find_answer(ch[x][1], k - bar[ch[x][0]] - (bool) pos[x]);
  }
}

int split(int p) {
  int x = find_kth(root, p - 1);
  splay(x, 0);
  int y = ch[x][1];
  father[y] = ch[x][1] = 0;
  pull(x);
  return y;
}

int split(int l, int r) {
  int x = find_kth(root, l - 1), y = find_kth(root, r + 1);
  splay(x, 0);
  splay(y, x);
  int z = ch[y][0];
  father[z] = ch[y][0] = 0;
  pull(y);
  pull(x);
  return z;
}
}

void move(int u) {
  int f = father[u], l = splay::find_rank(u), r = l + size[u] - 1;
  int x = splay::split(l, r), y = splay::split(splay::find_rank(f) + 1), z = x;
  while (splay::ch[z][1]) {
    z = splay::ch[z][1];
  }
  splay::father[y] = z;
  splay::ch[z][1] = y;
  splay::father[x] = splay::root;
  splay::ch[splay::root][1] = x;
  while (z) {
    splay::pull(z);
    z = splay::father[z];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  len[0] = -1;
  last = new_node(0);
  for (int i = n; i; --i) {
    pos[extend(a[i], i)] = i;
  }
  for (int i = 2; i <= tt; ++i) {
    int c = a[ed[i] + len[father[i]]];
    adj[father[i]][c] = i;
  }
  for (int i = 2; i <= tt; ++i) {
    int c = a[ed[i] + len[father[i]]];
    if (adj[father[i]].size() > 1) {
      events[m - c].push_back(i);
    }
  }
  arr[++t] = tt + 1;
  dfs(1);
  arr[++t] = tt + 2;
  splay::root = splay::build(1, t);
  for (int i = 1; i <= q; ++i) {
    cin >> queries[i].d >> queries[i].k;
    queries[i].id = i;
  }
  sort(queries + 1, queries + 1 + q);
  map<int, vector<int>>::iterator here = events.begin();
  for (int i = 1; i <= q; ++i) {
    while (here != events.end() && here->first <= queries[i].d) {
      for (auto x : here->second) {
        move(x);
      }
      ++here;
    }
    answer[queries[i].id] = pos[splay::find_answer(splay::root, queries[i].k)];
  }
  for (int i = 1; i <= q; ++i) {
    cout << answer[i] << '\n';
  }
  return 0;
}
