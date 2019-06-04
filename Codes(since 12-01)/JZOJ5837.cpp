#include<bits/stdc++.h>

using namespace std;

const int N = 567890, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int x, int y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

int n, q, ta, tb, t, a, b, p[N];

struct node_t {
  int sump, k0, b0, k1, b1;

  node_t operator + (node_t a) {
    node_t result;
    result.sump = (sump + a.sump) % mod;
    result.k0 = mul(k0, a.k0);
    result.b0 = (mul(b0, a.k0) + a.b0) % mod;
    result.k1 = (mul(k0, a.k1) + k1) % mod;
    result.b1 = ((b1 + mul(b0, a.k1)) % mod + a.b1) % mod;
    return result;
  }
} node[N << 2];

void reset(int x, int y) {
  node[x].sump = p[y];
  node[x].k0 = (p[y] + mul(1 - p[y] + mod, t)) % mod;
  node[x].b0 = p[y];
  node[x].k1 = mul(node[x].k0, p[y + 1]);
  node[x].b1 = mul(node[x].b0, p[y + 1]);
}

void build(int l, int r, int x) {
  if (l == r) {
    reset(x, l);
  } else {
    int mid = l + r >> 1;
    build(l, mid, x << 1);
    build(mid + 1, r, x << 1 | 1);
    node[x] = node[x << 1] + node[x << 1 | 1];
  }
}

void modify(int l, int r, int x, int p) {
  if (l == r) {
    reset(x, l);
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, x << 1, p);
    } else {
      modify(mid + 1, r, x << 1 | 1, p);
    }
    node[x] = node[x << 1] + node[x << 1 | 1];
  }
}

node_t query(int l, int r, int x, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return node[x];
  } else {
    int mid = l + r >> 1;
    if (qr <= mid) {
      return query(l, mid, x << 1, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, x << 1 | 1, ql, qr);
    } else {
      return query(l, mid, x << 1, ql, qr) + query(mid + 1, r, x << 1 | 1, ql, qr);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q >> ta >> tb >> a >> b;
  t = mul(ta, qpow(tb, mod - 2));
  for (int i = 1, x, y; i <= n; ++i) {
    cin >> x >> y;
    p[i] = mul(x, qpow(y, mod - 2));
  }
  build(1, n, 1);
  while (q--) {
    int opt, x, y, z;
    cin >> opt;
    if (opt == 1) {
      cin >> x >> y >> z;
      p[x] = mul(y, qpow(z, mod - 2));
      modify(1, n, 1, x);
      if (x - 1) {
        modify(1, n, 1, x - 1);
      }
    } else {
      cin >> x >> y;
      node_t result = query(1, n, 1, x, y);
      int answer = 0;
      add(answer, mul(a, result.sump));
      add(answer, mul(b, result.sump));
      add(answer, mul(b, result.b1));
      sub(answer, mul(b, mul(result.b0, p[y + 1])));
      cout << answer << '\n';
    }
  }
  return 0;
}
