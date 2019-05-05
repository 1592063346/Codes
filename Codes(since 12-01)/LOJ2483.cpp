#include<bits/stdc++.h>

using namespace std;

const int N = 123456;
const long long llinf = 1e18;

struct point_t {
  long long x, y;

  point_t() {
  }

  point_t(long long x, long long y): x(x), y(y) {
  }

  bool operator < (const point_t& a) const {
    return x == a.x ? y < a.y : x < a.x;
  }
};

double slope(point_t a, point_t b) {
  return (double) (a.y - b.y) / (a.x - b.x);
}

int n, h[N], w[N], top, tt;
point_t sta[N], foo[N];
long long s[N], dp[N];

void divide(int l, int r) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  divide(l, mid);
  tt = top = 0;
  for (int i = l; i <= mid; ++i) {
    foo[++tt] = point_t(h[i], dp[i] - s[i] + (long long) h[i] * h[i]);
  }
  sort(foo + 1, foo + 1 + tt);
  for (int i = 1; i <= tt; ++i) {
    if (i > 1 && foo[i].x == foo[i - 1].x) {
      continue;
    }
    while (top > 1 && slope(sta[top - 1], sta[top]) >= slope(sta[top - 1], foo[i])) {
      --top;
    }
    sta[++top] = foo[i];
  }
  for (int i = mid + 1; i <= r; ++i) {
    int l = 1, r = top;
    while (l != r) {
      int mid = l + r >> 1;
      if (slope(sta[mid], sta[mid + 1]) <= 2 * h[i]) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    dp[i] = min(dp[i], sta[l].y - 2ll * h[i] * sta[l].x + s[i - 1] + (long long) h[i] * h[i]);
  }
  divide(mid + 1, r);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> h[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> w[i];
    s[i] = s[i - 1] + w[i];
  }
  dp[1] = 0;
  for (int i = 2; i <= n; ++i) {
    dp[i] = llinf;
  }
  divide(1, n);
  cout << dp[n] << '\n';
  return 0;
}
