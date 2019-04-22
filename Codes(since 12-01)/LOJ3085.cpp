#include<bits/stdc++.h>

using namespace std;

const int N = 745678;

struct point_t {
  double x, y;

  point_t() {
  }

  point_t(double x, double y): x(x), y(y) {
  }

  point_t operator + (point_t a) {
    return point_t(x + a.x, y + a.y);
  }

  point_t operator - (point_t a) {
    return point_t(x - a.x, y - a.y);
  }

  point_t operator * (double a) {
    return point_t(x * a, y * a);
  }
};

double cross(point_t a, point_t b) {
  return a.x * b.y - a.y * b.x;
}

point_t get_intersection(point_t a, point_t b, point_t c, point_t d) {
  point_t u = a - c, v = b - a, w = d - c;
  double t = cross(w, u) / cross(v, w);
  return a + v * t;
}

int n, a, b, c, k, x0, x1, y00[N], y11[N], g[N], h[N], tt;
double values[N];
set<pair<int, int>> points;

struct info_t {
  int foo;
  double x, yl, yr;

  info_t() {
  }

  info_t(int foo, double x, double yl, double yr = 0): foo(foo), x(x), yl(yl), yr(yr) {
  }

  bool operator < (const info_t& a) const {
    return x == a.x ? foo > a.foo : x < a.x;
  }
};

class fenwick_t {
 public:
  int n, a[N];

  fenwick_t() {
  }

  fenwick_t(int n): n(n) {
    fill(a, a + n + 1, 0);
  }

  void add(int p, int x) {
    for (; p <= n; p += p & -p) {
      a[p] += x;
    }
  }

  void add(int l, int r, int x) {
    add(l, x);
    add(r + 1, -x);
  }

  int sum(int p) {
    int result = 0;
    for (; p; p -= p & -p) {
      result += a[p];
    }
    return result;
  }
};

int find(double x) {
  return lower_bound(values + 1, values + 1 + tt, x) - values;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> a >> b >> c >> x0 >> x1;
  for (int i = 0; i < n; ++i) {
    cin >> y00[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> y11[i];
  }
  vector<info_t> events;
  for (int i = n - 1; ~i; --i) {
    for (auto p : points) {
      if (y11[i] < p.first) {
        break;
      }
      point_t a(x0, y00[i]);
      point_t b(x1, y11[i]);
      point_t c(x0, y00[p.second]);
      point_t d(x1, p.first);
      point_t x = get_intersection(a, b, c, d);
      events.emplace_back(0, x.x + x.y, x.x - x.y);
      values[++tt] = x.x - x.y;
    }
    points.emplace(y11[i], i);
  }
  int bar = tt;
  cin >> k;
  for (int i = 0, p, q, r; i < k; ++i) {
    cin >> p >> q >> r;
    int x = p + q;
    int y = p - q;
    events.emplace_back(1, x - r, y - r, y + r);
    events.emplace_back(-1, x + r, y - r, y + r);
    values[++tt] = y - r;
    values[++tt] = y + r;
  }
  sort(values + 1, values + 1 + tt);
  tt = unique(values + 1, values + 1 + tt) - values - 1;
  sort(events.begin(), events.end());
  fenwick_t bit(tt);
  int sumc = 0;
  for (auto e : events) {
    if (e.foo) {
      bit.add(find(e.yl), find(e.yr), e.foo);
    } else {
      sumc += (bit.sum(find(e.yl)) > 0) * c;
    }
  }
  int answer0 = a * bar + sumc, answer1 = b * bar + sumc, t = 0;
  for (auto p : points) {
    g[t] = p.second;
    h[p.second] = t++;
  }
  for (int i = 0; i < n; ++i) {
    if (i != g[i]) {
      int p = h[i];
      swap(g[i], g[p]);
      swap(h[g[i]], h[g[p]]);
      answer1 += a - b;
    }
  }
  cout << min(answer0, answer1) << ' ' << max(answer0, answer1) << '\n';
  return 0;
}
