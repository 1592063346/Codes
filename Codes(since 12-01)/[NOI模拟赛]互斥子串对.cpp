#include<bits/stdc++.h>

using namespace std;

const int N = 234567;

int n, q, tt, last, top, ch[N][26], ed[N], father[N], len[N], pos[N];
pair<int, int> events[N];
vector<pair<int, int>> queries[N];
vector<int> adj[N];
string s;

int new_node(int from) {
  len[++tt] = len[from] + 1;
  return tt;
}

int extend(int c) {
  int p = last, np = new_node(p);
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
      memcpy(ch[nq], ch[q], sizeof ch[q]);
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
  for (auto y : adj[x]) {
    dfs(y);
    ed[x] = max(ed[x], ed[y]);
  }
}

namespace lct {
int father[N], ch[N][2], last[N], tag[N];

bool is_root(int x) {
  int f = father[x];
  return ch[f][0] != x && ch[f][1] != x;
}

int side(int x) {
  int f = father[x];
  return ch[f][1] == x;
}

void mark(int x, int y) {
  last[x] = tag[x] = y;
}

void push(int x) {
  if (tag[x]) {
    if (ch[x][0]) {
      mark(ch[x][0], tag[x]);
    }
    if (ch[x][1]) {
      mark(ch[x][1], tag[x]);
    }
    tag[x] = 0;
  }
}

void rotate(int x) {
  int f = father[x], to = side(x), ano = ch[x][!to], tof = side(f);
  father[x] = father[f];
  if (!is_root(f)) {
    ch[father[f]][tof] = x;
  }
  father[ano] = f;
  ch[f][to] = ano;
  father[f] = x;
  ch[x][!to] = f;
}

void down(int x) {
  if (!is_root(x)) {
    down(father[x]);
  }
  push(x);
}

void splay(int x) {
  down(x);
  while (!is_root(x)) {
    int f = father[x];
    if (!is_root(f)) {
      if (side(x) == side(f)) {
        rotate(f);
      } else {
        rotate(x);
      }
    }
    rotate(x);
  }
}

void access(int x, int z) {
  int y = 0;
  while (x) {
    splay(x);
    events[++top] = pair<int, int>(last[x], len[x]);
    ch[x][1] = y;
    mark(x, z);
    y = x;
    x = father[x];
  }
}
}

namespace segment_t {
unsigned long long sum[N << 2], sum2[N << 2];
int tag[N << 2];

void add(int l, int r, int x, int y) {
  tag[x] += y;
  sum[x] += (unsigned long long) (r - l + 1) * y;
  sum2[x] += (unsigned long long) (l + r) * (r - l + 1) / 2 * y;
}

void pull(int x) {
  sum[x] = sum[x << 1] + sum[x << 1 | 1];
  sum2[x] = sum2[x << 1] + sum2[x << 1 | 1];
}

void push(int l, int r, int x) {
  if (tag[x]) {
    int mid = l + r >> 1;
    add(l, mid, x << 1, tag[x]);
    add(mid + 1, r, x << 1 | 1, tag[x]);
    tag[x] = 0;
  }
}

void modify(int l, int r, int x, int ql, int qr, int y) {
  if (ql <= l && r <= qr) {
    add(l, r, x, y);
  } else {
    push(l, r, x);
    int mid = l + r >> 1;
    if (ql <= mid) {
      modify(l, mid, x << 1, ql, qr, y);
    }
    if (qr > mid) {
      modify(mid + 1, r, x << 1 | 1, ql, qr, y);
    }
    pull(x);
  }
}

unsigned long long query(int l, int r, int x, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return sum[x];
  } else {
    push(l, r, x);
    int mid = l + r >> 1;
    unsigned long long result = 0;
    if (ql <= mid) {
      result += query(l, mid, x << 1, ql, qr);
    }
    if (qr > mid) {
      result += query(mid + 1, r, x << 1 | 1, ql, qr);
    }
    return result;
  }
}

unsigned long long query2(int l, int r, int x, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return sum2[x];
  } else {
    push(l, r, x);
    int mid = l + r >> 1;
    unsigned long long result = 0;
    if (ql <= mid) {
      result += query2(l, mid, x << 1, ql, qr);
    }
    if (qr > mid) {
      result += query2(mid + 1, r, x << 1 | 1, ql, qr);
    }
    return result;
  }
}
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> s;
  len[0] = -1;
  last = new_node(0);
  for (int i = 0; i < n; ++i) {
    pos[i + 1] = extend(s[i] - 'a');
    ed[pos[i + 1]] = i + 1;
  }
  unsigned long long answer = 0;
  for (int i = 2; i <= tt; ++i) {
    adj[father[i]].push_back(i);
    answer += len[i] - len[father[i]];
  }
  if (answer & 1) {
    answer = answer * (answer + 1 >> 1);
  } else {
    answer = (answer >> 1) * (answer + 1);
  }
  dfs(1);
  for (int i = 2; i <= tt; ++i) {
    queries[ed[i]].emplace_back(ed[i] - len[i] + 1, ed[i] - len[father[i]]);
  }
  for (int i = 2; i <= tt; ++i) {
    lct::father[i] = father[i];
  }
  for (int i = 1; i <= n; ++i) {
    segment_t::modify(1, n, 1, 1, i, 1);
    lct::access(pos[i], i);
    int last = 0;
    while (top) {
      pair<int, int> info = events[top--];
      if (info.first) {
        if (info.second) {
          segment_t::modify(1, n, 1, info.first - info.second + 1, info.first - last, -1);
        }
        last = info.second;
      }
    }
    for (auto p : queries[i]) {
      int l = p.first, r = p.second;
      answer -= segment_t::query2(1, n, 1, l, r) - segment_t::query(1, n, 1, l, r) * (l - 1);
      if (r < i) {
        answer -= segment_t::query(1, n, 1, r + 1, i) * (r - l + 1);
      }
    }
  }
  cout << answer << '\n';
  return 0;
}
