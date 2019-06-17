#include<bits/stdc++.h>

using namespace std;

const int N = 123456;
const double inf = 1e18;

int n, tt, ll, rr, maxd[N], dfn[N];
vector<pair<int, int>> adj[N];
pair<int, int> heavy[N];

class segment_t {
  double tag[N << 2], maxv[N << 2];

 public:
  segment_t() {
    memset(tag, 0, sizeof tag);
    fill(maxv + 1, maxv + (N << 2), -inf);
  }

  void mark(int x, double y) {
    tag[x] += y;
    maxv[x] += y;
  }

  void push(int x) {
    if (abs(tag[x]) > 1e-10) {
      mark(x << 1, tag[x]);
      mark(x << 1 | 1, tag[x]);
      tag[x] = 0;
    }
  }

  void modify(int l, int r, int x, int ql, int qr, double y) {
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
      maxv[x] = max(maxv[x << 1], maxv[x << 1 | 1]);
    }
  }

  void modify(int l, int r, int x, int p, double y) {
    if (l == r) {
      maxv[x] = max(maxv[x], y);
    } else {
      push(x);
      int mid = l + r >> 1;
      if (p <= mid) {
        modify(l, mid, x << 1, p, y);
      } else {
        modify(mid + 1, r, x << 1 | 1, p, y);
      }
      maxv[x] = max(maxv[x << 1], maxv[x << 1 | 1]);
    }
  }

  double query(int l, int r, int x, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return maxv[x];
    } else {
      push(x);
      int mid = l + r >> 1;
      double result = -inf;
      if (ql <= mid) {
        result = max(result, query(l, mid, x << 1, ql, qr));
      }
      if (qr > mid) {
        result = max(result, query(mid + 1, r, x << 1 | 1, ql, qr));
      }
      return result;
    }
  }
};

void dfs(int x, int f) {
  maxd[x] = -1;
  for (auto e : adj[x]) {
    int y = e.first;
    if (y != f) {
      dfs(y, x);
      if (maxd[y] > maxd[x]) {
        maxd[x] = maxd[y];
        heavy[x] = pair<int, int>(y, e.second);
      }
    }
  }
  ++maxd[x];
}

bool check(double foo) {
  double answer = -inf;
  segment_t tree;
  function<void (int, int)> dfs = [&] (int x, int f) {
    dfn[x] = ++tt;
    tree.modify(1, n, 1, dfn[x], 0);
    if (maxd[x]) {
      dfs(heavy[x].first, x);
      tree.modify(1, n, 1, dfn[x] + 1, dfn[x] + maxd[x], heavy[x].second - foo);
    }
    for (auto e : adj[x]) {
      int y = e.first;
      if (y != f && y != heavy[x].first) {
        dfs(y, x);
        for (int t = 1; t <= maxd[y] + 1; ++t) {
          int l = max(0, ll - t), r = min(rr - t, maxd[x]);
          if (l <= r) {
            answer = max(answer, tree.query(1, n, 1, dfn[y] + t - 1, dfn[y] + t - 1) + tree.query(1, n, 1, dfn[x] + l, dfn[x] + r) + e.second - foo);
          }
        }
        for (int t = 1; t <= maxd[y] + 1; ++t) {
          tree.modify(1, n, 1, dfn[x] + t, tree.query(1, n, 1, dfn[y] + t - 1, dfn[y] + t - 1) + e.second - foo);
        }
      }
    }
    if (ll <= maxd[x]) {
      answer = max(answer, tree.query(1, n, 1, dfn[x] + ll, dfn[x] + min(maxd[x], rr)));
    }
  };
  tt = 0;
  dfs(1, 0);
  return answer >= 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.setf(ios::fixed);
  cin >> n >> ll >> rr;
  for (int i = 1, x, y, z; i < n; ++i) {
    cin >> x >> y >> z;
    adj[x].emplace_back(y, z);
    adj[y].emplace_back(x, z);
  }
  dfs(1, 0);
  double l = 1, r = 1e6;
  while (r - l > 1e-4) {
    double mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  cout << setprecision(3) << l << '\n';
  return 0;
}
