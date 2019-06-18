#include<bits/stdc++.h>

using namespace std;

const int N = 123456;
const long long llinf = 1e18;

int n, m, tt, a[N], heavy[N], dfn[N], maxd[N];
vector<int> adj[N];
long long dp0[N];

class segment_t {
  long long a[N << 2], tag[N << 2];

 public:
  segment_t() {
    fill(a, a + (N << 2), llinf);
    memset(tag, 0, sizeof tag);
  }

  void mark(int x, long long y) {
    tag[x] += y;
    a[x] += y;
  }

  void push(int x) {
    if (tag[x]) {
      mark(x << 1, tag[x]);
      mark(x << 1 | 1, tag[x]);
      tag[x] = 0;
    }
  }

  void modify(int l, int r, int x, int ql, int qr, long long y) {
    if (ql <= l && r <= qr) {
      mark(x, y);
    } else {
      int mid = l + r >> 1;
      push(x);
      if (ql <= mid) {
        modify(l, mid, x << 1, ql, qr, y);
      }
      if (qr > mid) {
        modify(mid + 1, r, x << 1 | 1, ql, qr, y);
      }
      a[x] = min(a[x << 1], a[x << 1 | 1]);
    }
  }

  void modify(int l, int r, int x, int p, long long y) {
    if (l == r) {
      a[x] = min(a[x], y);
    } else {
      int mid = l + r >> 1;
      push(x);
      if (p <= mid) {
        modify(l, mid, x << 1, p, y);
      } else {
        modify(mid + 1, r, x << 1 | 1, p, y);
      }
      a[x] = min(a[x << 1], a[x << 1 | 1]);
    }
  }

  long long query(int l, int r, int x, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return a[x];
    } else {
      int mid = l + r >> 1;
      long long result = llinf;
      push(x);
      if (ql <= mid) {
        result = min(result, query(l, mid, x << 1, ql, qr));
      }
      if (qr > mid) {
        result = min(result, query(mid + 1, r, x << 1 | 1, ql, qr));
      }
      return result;
    }
  }
};

void dfs(int x, int f) {
  maxd[x] = -1;
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
      if (maxd[y] > maxd[x]) {
        heavy[x] = y;
        maxd[x] = maxd[y];
      }
    }
  }
  ++maxd[x];
}

bool check(int k) {
  segment_t tree;
  auto dp = [&] (int x, int y) {
    return !y ? dp0[x] : tree.query(1, n, 1, dfn[x] + y - 1, dfn[x] + y - 1);
  };
  function<void (int, int)> dfs = [&] (int x, int f) {
    dp0[x] = a[x];
    dfn[x] = ++tt;
    if (maxd[x]) {
      dfs(heavy[x], x);
      dp0[x] += min(dp(heavy[x], 0), tree.query(1, n, 1, dfn[heavy[x]], dfn[heavy[x]] + min(maxd[heavy[x]], k - 1)));
      tree.modify(1, n, 1, dfn[x], dp(heavy[x], 0));
    } else {
      tree.modify(1, n, 1, dfn[x], 0);
    }
    for (auto y : adj[x]) {
      if (y != f && y != heavy[x]) {
        dfs(y, x);
        dp0[x] += min(dp(y, 0), tree.query(1, n, 1, dfn[y], dfn[y] + min(maxd[y], k - 1)));
        vector<long long> foo;
        vector<pair<int, long long>> bar;
        for (int j = 1; j <= min(maxd[y] + 2, k); ++j) {
          int l = 1, r = min(j, k - j + 1);
          if (l > r) {
            break;
          }
          long long t = dp(y, j - 1);
          foo.push_back(t + tree.query(1, n, 1, dfn[x] + l - 1, dfn[x] + r - 1));
          if (!bar.size() || (bar.size() && t < bar.back().second)) {
            bar.emplace_back(j - 1, t);
          }
        }
        long long last = 0;
        for (auto p : bar) {
          int l = p.first + 1, r = min(maxd[x] + 1, k - p.first);
          if (l <= r) {
            tree.modify(1, n, 1, dfn[x] + l - 1, dfn[x] + r - 1, p.second - last);
            last = p.second;
          }
        }
        for (int i = 0; i < foo.size(); ++i) {
          tree.modify(1, n, 1, dfn[x] + i, foo[i]);
        }
      }
    }
  };
  tt = 0;
  dfs(1, 0);
  return min(dp(1, 0), tree.query(1, n, 1, dfn[1], dfn[1] + min(maxd[1], k - 1))) <= m;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  long long all = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    all += a[i];
  }
  if (all <= m) {
    cout << 0 << '\n';
    exit(0);
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(1, 0);
  int l = 1, r = n;
  while (l != r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << l << '\n';
  return 0;
}
