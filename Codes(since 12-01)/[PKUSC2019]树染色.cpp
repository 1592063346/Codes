#include<bits/stdc++.h>

using namespace std;

const int N = 234567, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, m, k, root[N], tt, all;
vector<int> adj[N], ban[N];

struct node_t {
  int l, r, atag, mtag, value, sum;

  node_t() {
  }

  node_t(int value, int sum): value(value), sum(sum) {
    l = r = 0;
    atag = 0;
    mtag = 1;
  }
} nodes[N * 70];

int new_root() {
  nodes[++tt] = node_t(1, m % mod);
  return tt;
}

int new_node(int len, int x) {
  nodes[++tt] = node_t(nodes[x].value, mul(nodes[x].value, len));
  return tt;
}

void pull(int l, int r, int x) {
  int mid = l + r >> 1, ll = nodes[x].l, rr = nodes[x].r;
  nodes[x].sum = 0;
  add(nodes[x].sum, ll ? nodes[ll].sum : mul(mid - l + 1, nodes[x].value));
  add(nodes[x].sum, rr ? nodes[rr].sum : mul(r - mid, nodes[x].value));
}

void mul_tag(int x, int y) {
  if (x) {
    nodes[x].atag = mul(nodes[x].atag, y);
    nodes[x].mtag = mul(nodes[x].mtag, y);
    nodes[x].value = mul(nodes[x].value, y);
    nodes[x].sum = mul(nodes[x].sum, y);
  }
}

void add_tag(int x, int y, int len) {
  if (x) {
    add(nodes[x].atag, y);
    add(nodes[x].value, y);
    add(nodes[x].sum, mul(len, y));
  }
}

void push(int l, int r, int x) {
  int mid = l + r >> 1;
  int& ll = nodes[x].l;
  int& rr = nodes[x].r;
  if (nodes[x].mtag != 1) {
    mul_tag(ll, nodes[x].mtag);
    mul_tag(rr, nodes[x].mtag);
  }
  if (nodes[x].atag != 0) {
    add_tag(ll, nodes[x].atag, mid - l + 1);
    add_tag(rr, nodes[x].atag, r - mid);
  }
  if (!ll) {
    ll = new_node(mid - l + 1, x);
    nodes[ll].atag = nodes[x].atag;
    nodes[ll].mtag = nodes[x].mtag;
  }
  if (!rr) {
    rr = new_node(r - mid, x);
    nodes[rr].atag = nodes[x].atag;
    nodes[rr].mtag = nodes[x].mtag;
  }
  nodes[x].mtag = 1;
  nodes[x].atag = 0;
}

int merge(int l, int r, int x, int y) {
  if (!nodes[x].l && !nodes[x].r) {
    swap(x, y);
    mul_tag(x, mod - 1);
    add_tag(x, all, r - l + 1);
    mul_tag(x, nodes[y].value);
  } else if (!nodes[y].l && !nodes[y].r) {
    mul_tag(x, (all - nodes[y].value + mod) % mod);
  } else {
    push(l, r, x);
    push(l, r, y);
    int mid = l + r >> 1;
    nodes[x].l = merge(l, mid, nodes[x].l, nodes[y].l);
    nodes[x].r = merge(mid + 1, r, nodes[x].r, nodes[y].r);
    pull(l, r, x);
  }
  return x;
}

void reset(int l, int r, int& x, int f, int p) {
  if (l == r) {
    nodes[x].value = nodes[x].sum = 0;
  } else {
    push(l, r, x);
    int mid = l + r >> 1;
    if (p <= mid) {
      reset(l, mid, nodes[x].l, x, p);
    } else {
      reset(mid + 1, r, nodes[x].r, x, p);
    }
    pull(l, r, x);
  }
}

void dfs(int x, int f) {
  root[x] = new_root();
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
      all = nodes[root[y]].sum;
      root[x] = merge(1, m, root[x], root[y]);
    }
  }
  for (auto y : ban[x]) {
    reset(1, m, root[x], 0, y);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  for (int i = 1, x, y; i <= k; ++i) {
    cin >> x >> y;
    ban[x].push_back(y);
  }
  dfs(1, 0);
  cout << nodes[root[1]].sum << '\n';
  return 0;
}
