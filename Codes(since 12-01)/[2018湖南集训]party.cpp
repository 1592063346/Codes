#include<bits/stdc++.h>

using namespace std;

const int N = 300005;

using bitset_t = bitset<1005>;

int n, m, q, tt, dfn[N], top[N], a[N], size[N], heavy[N], father[N], sub[N], depth[N];
vector<int> adj[N];

namespace segment_t {
bitset_t a[N << 2];

void modify(int l, int r, int x, int y, int z) {
  a[x].set(z);
  if (l != r) {
    int mid = l + r >> 1;
    if (y <= mid) {
      modify(l, mid, x << 1, y, z);
    } else {
      modify(mid + 1, r, x << 1 | 1, y, z);
    }
  }
}

bitset_t query(int l, int r, int x, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return a[x];
  } else {
    int mid = l + r >> 1;
    bitset_t result;
    if (ql <= mid) {
      result = result | query(l, mid, x << 1, ql, qr);
    }
    if (qr > mid) {
      result = result | query(mid + 1, r, x << 1 | 1, ql, qr);
    }
    return result;
  }
}
}

using segment_t::modify;
using segment_t::query;

void dfs(int x) {
  sub[x] = 1;
  for (auto y : adj[x]) {
    father[y] = x;
    depth[y] = depth[x] + 1;
    dfs(y);
    sub[x] += sub[y];
    if (sub[y] > sub[heavy[x]]) {
      heavy[x] = y;
    }
  }
}

void dfs(int x, int t) {
  top[x] = t;
  dfn[x] = ++tt;
  if (heavy[x]) {
    dfs(heavy[x], t);
    for (auto y : adj[x]) {
      if (y != heavy[x]) {
        dfs(y, y);
      }
    }
  }
}

int get_lca(int x, int y) {
  for (; top[x] != top[y]; x = father[top[x]]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
  }
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  return x;
}

bitset_t query(int x, int y) {
  bitset_t result;
  for (; top[x] != top[y]; x = father[top[x]]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
    result = result | query(1, n, 1, dfn[top[x]], dfn[x]);
  }
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  result = result | query(1, n, 1, dfn[x], dfn[y]);
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i < 0xffff; ++i) {
    size[i] = size[i - (i & -i)] + 1;
  }
  for (int i = 2, x; i <= n; ++i) {
    cin >> x;
    adj[x].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    --a[i];
  }
  dfs(1);
  dfs(1, 1);
  for (int i = 1; i <= n; ++i) {
    modify(1, n, 1, dfn[i], a[i]);
  }
  while (q--) {
    int c;
    cin >> c;
    vector<int> nodes(c);
    vector<bitset_t> bits(c);
    for (int i = 0; i < c; ++i) {
      cin >> nodes[i];
    }
    int lca = nodes[0];
    for (int i = 1; i < c; ++i) {
      lca = get_lca(lca, nodes[i]);
    }
    for (int i = 0; i < c; ++i) {
      bits[i] = query(nodes[i], lca);
    }
    int answer = m;
    function<void (int, int, bitset_t)> dfs = [&] (int d, int x, bitset_t y) {
      if (d == c) {
        if (x) {
          answer = min(answer, (int) y.count() / x);
        }
      } else {
        dfs(d + 1, x, y);
        dfs(d + 1, x + 1, y | bits[d]);
      }
    };
    dfs(0, 0, bitset_t());
    cout << (answer * c) << '\n';
  }
  return 0;
}
