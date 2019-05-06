#include<bits/stdc++.h>

using namespace std;

const int N = 234567;
const long long llinf = 1e18;

int n, m, a[N], b[N];
long long sum[N], dp[N];

class segment_t {
 public:
  long long minv[N << 2];

  void insert(int l, int r, int x, int p, long long y, bool add = false) {
    if (l == r) {
      if (add) {
        minv[x] += y;
      } else {
        minv[x] = y;
      }
    } else {
      int mid = l + r >> 1;
      if (p <= mid) {
        insert(l, mid, x << 1, p, y, add);
      } else {
        insert(mid + 1, r, x << 1 | 1, p, y, add);
      }
      minv[x] = min(minv[x << 1], minv[x << 1 | 1]);
    }
  }

  long long query(int l, int r, int x, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return minv[x];
    } else {
      int mid = l + r >> 1;
      if (qr <= mid) {
        return query(l, mid, x << 1, ql, qr);
      } else if (ql > mid) {
        return query(mid + 1, r, x << 1 | 1, ql, qr);
      } else {
        return min(query(l, mid, x << 1, ql, qr), query(mid + 1, r, x << 1 | 1, ql, qr));
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  vector<pair<int, int>> points;
  points.emplace_back(-1, 0);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    points.emplace_back(a[i], 0);
  }
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
    points.emplace_back(b[i], 1);
  }
  sort(points.begin(), points.end());
  for (int i = 1; i <= n + m; ++i) {
    sum[i] = sum[i - 1] + points[i].first;
  }
  int l = 1, r = 1;
  segment_t foo, bar;
  while (points[r].second == points[l].second) {
    ++r;
  }
  --r;
  foo.insert(0, n + m - 1, 1, 0, (long long) points[r].first * r - sum[r]);
  bar.insert(0, n + m - 1, 1, 0, (long long) points[r].first * r - sum[r]);
  for (int i = 1; i <= r; ++i) {
    dp[i] = llinf;
    foo.insert(0, n + m - 1, 1, i, llinf);
    bar.insert(0, n + m - 1, 1, i, llinf);
  }
  for (int i = r + 1, lastl, lastr; i <= n + m; ++i) {
    if (points[i].second != points[i - 1].second) {
      lastl = l;
      lastr = r;
      l = r = i;
      while (r <= n + m && points[r].second == points[l].second) {
        ++r;
      }
      --r;
    }
    dp[i] = dp[i - 1] + points[i].first - points[lastr].first;
    long long other = sum[i] - sum[lastr] - (long long) (i - lastr) * points[l].first;
    long long x = foo.query(0, n + m - 1, 1, max(lastl - 1, 2 * lastr - i), lastr - 1);
    dp[i] = min(dp[i], x + other + (long long) (i - lastr) * (points[l].first - points[lastr].first));
    if (lastl - 1 < 2 * lastr - i) {
      long long y = bar.query(0, n + m - 1, 1, lastl - 1, 2 * lastr - i - 1);
      dp[i] = min(dp[i], y + other + (long long) lastr * (points[l].first - points[lastr].first));
    }
    if (i == n + m) {
      cout << dp[i] << '\n';
    } else {
      foo.insert(0, n + m - 1, 1, i, dp[i] + sum[i]);
      foo.insert(0, n + m - 1, 1, i - 1, -sum[r] + (long long) (r - i + 1) * points[r].first, true);
      bar.insert(0, n + m - 1, 1, i, dp[i] + sum[i]);
      bar.insert(0, n + m - 1, 1, i - 1, -sum[r] + (long long) (r - i + 1) * points[r].first - (long long) (i - 1) * (points[r + 1].first - points[r].first), true);
    }
  }
  return 0;
}
