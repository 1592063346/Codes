#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

int n;

struct point {
  int x, y;

  point () {}
  point (int x, int y): x(x), y(y) {}

  point operator + (point a) {
    return point (x + a.x, y + a.y);
  }

  point operator - (point a) {
    return point (x - a.x, y - a.y);
  }

  bool operator < (const point& a) const {
    return x == a.x ? y < a.y : x < a.x;
  }
} points[N];

int main() {
  scanf("%d%*I64d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &points[i].x, &points[i].y);
  }
  function<long long (point, point)> cross = [&] (point a, point b) {
    return (long long) a.x * b.y - (long long) a.y * b.x;
  };
  function<vector<point> (point*)> convex_hull = [&] (point* p) {
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
    if (convex.size() > 1) {
      convex.pop_back();
    }
    return convex;
  };
  vector<point> convex = convex_hull(points);
  long long area = 0;
  point a, b, c;
  for (int i = 0; i < convex.size(); ++i) {
    function<int (int)> next_pos = [&] (int pos) {
      return (pos + 1) % convex.size();
    };
    int k = next_pos(i);
    for (int j = next_pos(i); j != i; j = next_pos(j)) {
      for (; cross(convex[j] - convex[i], convex[next_pos(k)] - convex[k]) >= 0; k = next_pos(k));
      if (abs(cross(convex[j] - convex[i], convex[k] - convex[i])) > area) {
        area = abs(cross(convex[j] - convex[i], convex[k] - convex[i]));
        a = convex[i];
        b = convex[j];
        c = convex[k];
      }
    }
  }
  point ans_a = a + (c - b);
  point ans_b = b + (a - c);
  point ans_c = c + (b - a);
  printf("%d %d\n", ans_a.x, ans_a.y);
  printf("%d %d\n", ans_b.x, ans_b.y);
  printf("%d %d\n", ans_c.x, ans_c.y);
  return 0;
}
