#include<bits/stdc++.h>

using namespace std;

const int N = 123456;
const long long llinf = 1e18;

struct edge_t {
  int foo, bar, x;

  bool operator < (const edge_t& a) const {
    return foo < a.foo;
  }
} edges[N];

int n, m, q, a[N], b[N];
long long pre_a[N], suf_b[N], w_c[N], value[N], suf[N];
multiset<long long> sa, sb, sc;

class segment_t {
 public:
  long long a[N << 2], tag[N << 2];

  void mark(int x, long long y) {
    a[x] += y;
    tag[x] += y;
  }

  void push(int x) {
    if (tag[x]) {
      mark(x << 1, tag[x]);
      mark(x << 1 | 1, tag[x]);
      tag[x] = 0;
    }
  }

  void pull(int x) {
    a[x] = min(a[x << 1], a[x << 1 | 1]);
  }

  void modify(int l, int r, int x, int ql, int qr, int y) {
    if (ql <= l && r <= qr) {
      mark(x, y);
    } else {
      push(x);
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

  long long query(int l, int r, int x, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return a[x];
    } else {
      push(x);
      int mid = l + r >> 1;
      long long result = llinf;
      if (ql <= mid) {
        result = min(result, query(l, mid, x << 1, ql, qr));
      }
      if (qr > mid) {
        result = min(result, query(mid + 1, r, x << 1 | 1, ql, qr));
      }
      return result;
    }
  }
} tree;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i < n; ++i) {
    cin >> b[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> edges[i].foo >> edges[i].bar >> edges[i].x;
    pre_a[edges[i].foo] += edges[i].x;
    suf_b[edges[i].bar] += edges[i].x;
  }
  sort(edges + 1, edges + 1 + m);
  for (int i = 1; i <= n; ++i) {
    pre_a[i] += pre_a[i - 1];
  }
  for (int i = 1; i <= n; ++i) {
    pre_a[i] += a[i];
    sa.insert(pre_a[i]);
  }
  for (int i = n; i; --i) {
    suf_b[i] += suf_b[i + 1];
  }
  for (int i = n; i; --i) {
    suf_b[i] += b[i - 1];
    sb.insert(suf_b[i]);
  }
  for (int i = 1; i <= n; ++i) {
    tree.modify(1, n, 1, i, i, b[i - 1]);
  }
  for (int i = 1, j = 1; i <= n; ++i) {
    while (j <= m && edges[j].foo <= i) {
      tree.modify(1, n, 1, 1, edges[j].bar, edges[j].x);
      ++j;
    }
    w_c[i] = tree.query(1, n, 1, 1, n) + a[i];
    sc.insert(w_c[i]);
  }
  while (q--) {
    int p, w;
    cin >> p >> w;
    sa.erase(sa.find(pre_a[p]));
    sc.erase(sc.find(w_c[p]));
    pre_a[p] += w - a[p];
    w_c[p] += w - a[p];
    a[p] = w;
    sa.insert(pre_a[p]);
    sc.insert(w_c[p]);
    cout << min(*sa.begin(), min(*sb.begin(), *sc.begin())) << '\n';
  }
  return 0;
}
