#include<bits/stdc++.h>

using namespace std;

const int N = 345678, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, q, tt, last, dfn_tt, ch[N][26], father[N], len[N], diff[N], top[N], dfn[N], size[N], answer[N * 4];
vector<int> adj[N];
vector<pair<int, int>> queries[N];
string s, t;

namespace bit {
int a[N];

void add(int x, int y) {
  while (x <= n) {
    a[x] += y;
    x += x & -x;
  }
}

int sum(int x) {
  int result = 0;
  while (x) {
    result += a[x];
    x -= x & -x;
  }
  return result;
}

int sum(int l, int r) {
  return sum(r) - sum(l - 1);
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
  cin >> n >> q >> s;
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
  for (int i = 1, x, y; i <= q; ++i) {
    cin >> x >> y;
    queries[y].emplace_back(x, i);
  }
  dfs(1);
  int here = 0;
  for (int i = 1; i <= n; ++i) {
    while (t[i - 1 - len[here]] != t[i]) {
      here = father[here];
    }
    here = ch[here][t[i] - 'a'];
    for (int x = here; x > 1; x = father[top[x]]) {
      int last = segment_t::query(1, dfn_tt, 1, dfn[x], dfn[x] + size[x] - 1) - len[x] + 1;
      if (last > 0) {
        bit::add(last, -1);
      }
      bit::add(i - len[top[x]] + 1, 1);
    }
    segment_t::modify(1, dfn_tt, 1, dfn[here], i);
    for (auto query : queries[i]) {
      answer[query.second] = bit::sum(query.first, i);
    }
  }
  int result = 0;
  for (int i = 1; i <= q; ++i) {
    add(result, mul(answer[i], i));
  }
  cout << result << '\n';
  return 0;
}
