#include<bits/stdc++.h>

using namespace std;

const int N = 100005;

struct node_t {
  int l, r, sum;
};

int type, n, q, tt, last, dfn_tt, node_tt, root[N], ch[N][26], father[N], len[N], diff[N], top[N], dfn[N], size[N];
vector<int> adj[N];
string s, t;

namespace p_segment_t {
int tt;
node_t node[N * 200];

int modify(int l, int r, int x, int y, int w) {
  int z = ++node_tt;
  node[z] = node[x];
  node[z].sum += w;
  if (l != r) {
    int mid = l + r >> 1;
    if (y <= mid) {
      node[z].l = modify(l, mid, node[x].l, y, w);
    } else {
      node[z].r = modify(mid + 1, r, node[x].r, y, w);
    }
  }
  return z;
}

int query(int l, int r, int x, int ql, int qr) {
  if (!x) {
    return 0;
  } else if (ql <= l && r <= qr) {
    return node[x].sum;
  } else {
    int mid = l + r >> 1, result = 0;
    if (ql <= mid) {
      result += query(l, mid, node[x].l, ql, qr);
    }
    if (qr > mid) {
      result += query(mid + 1, r, node[x].r, ql, qr);
    }
    return result;
  }
}
}

namespace segment_t {
int a[N << 2];

void modify(int l, int r, int x, int y, int z) {
  a[x] = max(a[x], z);
  if (l != r) {
    int mid = l + r >> 1;
    if (y <= mid) {
      modify(l, mid, x << 1, y, z);
    } else {
      modify(mid + 1, r, x << 1 | 1, y, z);
    }
  }
}

int query(int l, int r, int x, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return a[x];
  } else {
    int mid = l + r >> 1, result = 0;
    if (ql <= mid) {
      result = max(result, query(l, mid, x << 1, ql, qr));
    }
    if (qr > mid) {
      result = max(result, query(mid + 1, r, x << 1 | 1, ql, qr));
    }
    return result;
  }
}
}

int new_node(int from) {
  len[++tt] = len[from] + 2;
  return tt;
}

void extend(int i, int c) {
  int p = last;
  while (t[i - 1 - len[p]] - 'a' != c) {
    p = father[p];
  }
  if (!ch[p][c]) {
    int np = new_node(p), q = father[p];
    while (t[i - 1 - len[q]] - 'a' != c) {
      q = father[q];
    }
    father[np] = ch[q][c];
    diff[np] = len[np] - len[father[np]];
    top[np] = diff[np] == diff[father[np]] ? top[father[np]] : np;
    ch[p][c] = np;
  }
  last = ch[p][c];
}

void dfs(int x) {
  size[x] = 1;
  dfn[x] = ++dfn_tt;
  for (auto y : adj[x]) {
    dfs(y);
    size[x] += size[y];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> type >> n >> q >> s;
  tt = 1;
  father[0] = 1;
  len[1] = -1;
  t.push_back('z' + 1);
  for (int i = 0; i < n; ++i) {
    t.push_back(s[i]);
    extend(i + 1, s[i] - 'a');
  }
  for (int i = 2; i <= tt; ++i) {
    adj[max(father[i], 1)].push_back(i);
  }
  dfs(1);
  int here = 0;
  for (int i = 1; i <= n; ++i) {
    root[i] = root[i - 1];
    while (t[i - 1 - len[here]] != t[i]) {
      here = father[here];
    }
    here = ch[here][t[i] - 'a'];
    for (int x = here; x > 1; x = father[top[x]]) {
      int last = segment_t::query(1, dfn_tt, 1, dfn[x], dfn[x] + size[x] - 1) - len[x] + 1;
      if (last > 0) {
        root[i] = p_segment_t::modify(1, n, root[i], last, -1);
      }
      root[i] = p_segment_t::modify(1, n, root[i], i - len[top[x]] + 1, 1);
    }
    segment_t::modify(1, dfn_tt, 1, dfn[here], i);
  }
  int answer = 0;
  while (q--) {
    int l, r;
    cin >> l >> r;
    l ^= type * answer;
    r ^= type * answer;
    cout << (answer = p_segment_t::query(1, n, root[r], l, r)) << '\n';
  }
  cerr << node_tt << '\n';
  return 0;
}
