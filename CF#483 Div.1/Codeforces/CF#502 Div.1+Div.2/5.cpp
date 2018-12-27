#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m;

struct point {
  int x, y;

  point () {}
  point (int x, int y): x(x), y(y) {}

  point operator - (point a) {
    return point (x - a.x, y - a.y);
  }

  bool operator < (const point& a) const {
    return x == a.x ? y < a.y : x < a.x;
  }
} a[N], b[N];

long long dot(point a, point b) {
  return (long long) a.x * b.x + (long long) a.y * b.y;
}

long long cross(point a, point b) {
  return (long long) a.x * b.y - (long long) a.y * b.x;
}

long long dist2(point a, point b) {
  return dot(a - b, a - b);
}

vector<point> convex_hull(point* p, int n) {
  sort(p + 1, p + 1 + n);
  vector<point> convex;
  for (int i = 1; i <= n; ++i) {
    for (int j; (j = convex.size()) > 1 && cross(convex[j - 1] - convex[j - 2], p[i] - convex[j - 2]) <= 0; convex.pop_back());
    convex.push_back(p[i]);
  }
  int old = convex.size();
  for (int i = n - 1; i; --i) {
    for (int j; (j = convex.size()) > old && cross(convex[j - 1] - convex[j - 2], p[i] - convex[j - 2]) <= 0; convex.pop_back());
    convex.push_back(p[i]);
  }
  convex.pop_back();
  return convex;
}

struct p3 {
  long long x, y, z;

  p3 () {}
  p3 (long long x, long long y, long long z): x(x), y(y), z(z) {}

  bool operator < (const p3& a) const {
    return x == a.x ? y == a.y ? z < a.z : y < a.y : x < a.x;
  }
};

long long f(point a, point b) {
  return dot(a, b) + cross(a, b);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &a[i].x, &a[i].y);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &b[i].x, &b[i].y);
  }
  vector<point> convex_a = convex_hull(a, n);
  vector<point> convex_b = convex_hull(b, m);
  if (convex_a.size() != convex_b.size()) {
    return puts("NO"), 0;
  } else {
    map<p3, int> appeared;
    for (int i = 0; i < convex_a.size(); ++i) {
      int j = i + 1 == convex_a.size() ? 0 : i + 1;
      int k = i == 0 ? convex_a.size() - 1 : i - 1;
      ++appeared[p3(dist2(convex_a[k], convex_a[i]), f(convex_a[k] - convex_a[i], convex_a[j] - convex_a[i]), dist2(convex_a[j], convex_a[i]))];
    }
    for (int i = 0; i < convex_b.size(); ++i) {
      int j = i + 1 == convex_b.size() ? 0 : i + 1;
      int k = i == 0 ? convex_b.size() - 1 : i - 1;
      --appeared[p3(dist2(convex_b[k], convex_b[i]), f(convex_b[k] - convex_b[i], convex_b[j] - convex_b[i]), dist2(convex_b[j], convex_b[i]))];
    }
    bool same = true;
    for (map<p3, int>:: iterator it = appeared.begin(); it != appeared.end(); ++it) {
      if (it->second != 0) {
        same = false;
      }
    }
    return puts(same ? "YES" : "NO"), 0;
  }
  return 0;
}
