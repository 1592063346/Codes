#include<bits/stdc++.h>

using namespace std;

struct point {
  int x, y;

  point() {}
  point(int x, int y): x(x), y(y) {}

  point operator + (point a) {
    return point(x + a.x, y + a.y);
  }

  point operator - (point a) {
    return point(x - a.x, y - a.y);
  }

  bool operator < (const point& a) const {
    return x == a.x ? y < a.y : x < a.x;
  }
} source;

long long cross(point a, point b) {
  return (long long) a.x * b.y - (long long) a.y * b.x;
}

int n, m, k;
vector<point> p, q, s;

vector<point> convex_hull(vector<point>& p) {
  int n = p.size();
  vector<point> result;
  sort(p.begin(), p.end());
  for (int i = 0; i < n; ++i) {
    for (int j; (j = result.size()) > 1 && cross(result[j - 1] - result[j - 2], p[i] - result[j - 2]) <= 0; result.pop_back());
    result.push_back(p[i]);
  }
  int old = result.size();
  for (int i = n - 2; ~i; --i) {
    for (int j; (j = result.size()) > old && cross(result[j - 1] - result[j - 2], p[i] - result[j - 2]) <= 0; result.pop_back());
    result.push_back(p[i]);
  }
  result.pop_back();
  return result;
}

vector<point> minkowski_sum(vector<point>& p, vector<point>& q) {
  vector<point> result(1, p[0] + q[0]);
  int n = p.size();
  int m = q.size();
  p.push_back(p[0]);
  q.push_back(q[0]);
  for (int i = 0, j = 0; i + j < n + m - 1;) {
    if (j + 1 == q.size() || (i + 1 < p.size() && cross(p[i + 1] - p[i], q[j + 1] - q[j]) > 0)) {
      result.push_back(p[++i] + q[j]);
    } else {
      result.push_back(p[i] + q[++j]);
    }
  }
  return result;
}

bool check(point d) {
  d = d - source;
  int n = s.size();
  if (cross(s[0], d) < 0 || cross(s[n - 1], d) > 0) {
    return false;
  }
  int x = upper_bound(s.begin(), s.end(), d, [&] (const point& a, const point& b) {
    return atan2(a.y, a.x) < atan2(b.y, b.x);
  }) - s.begin() - 1;
  return cross(d - s[x], s[x + 1] - d) <= 0;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  p.resize(n);
  q.resize(m);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &p[i].x, &p[i].y);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &q[i].x, &q[i].y);
    q[i].x = -q[i].x;
    q[i].y = -q[i].y;
  }
  p = convex_hull(p);
  q = convex_hull(q);
  p = minkowski_sum(p, q);
  source = p[0];
  for (int i = 1; i < p.size(); ++i) {
    s.push_back(p[i] - source);
  }
  while (k--) {
    point d;
    scanf("%d%d", &d.x, &d.y);
    printf("%d\n", check(d));
  }
  return 0;
}
