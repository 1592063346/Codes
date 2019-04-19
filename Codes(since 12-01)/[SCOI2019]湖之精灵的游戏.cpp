#include<bits/stdc++.h>

using namespace std;

const int N = 1234567;

int n, q, all;
long long answer[N];

struct point_t {
  int x, y;

  point_t() {
  }

  point_t(int x, int y): x(x), y(y) {
  }

  point_t operator - (point_t a) {
    return point_t(x - a.x, y - a.y);
  }

  bool operator < (const point_t& a) const {
    return x == a.x ? y < a.y : x < a.x;
  }
} p[N], convex[N];

struct info_t {
  int x, y, id;
  double angle;

  bool operator < (const info_t& a) const {
    return angle < a.angle;
  }
} queries[N];

long long cross(point_t a, point_t b) {
  return (long long) a.x * b.y - (long long) a.y * b.x;
}

void get_convex_hull() {
  sort(p, p + n);
  for (int i = 0; i < n; ++i) {
    while (all > 1 && cross(p[i] - convex[all - 2], convex[all - 1] - convex[all - 2]) >= 0) {
      --all;
    }
    convex[all++] = p[i];
  }
  int y = all;
  for (int i = n - 2; ~i; --i) {
    while (all > y && cross(p[i] - convex[all - 2], convex[all - 1] - convex[all - 2]) >= 0) {
      --all;
    }
    convex[all++] = p[i];
  }
  if (all > 1) {
    --all;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  ++n;
  for (int i = 1; i < n; ++i) {
    cin >> p[i].x >> p[i].y;
    p[i].x += p[i - 1].x;
    p[i].y += p[i - 1].y;
  }
  get_convex_hull();
  for (int i = 0; i < q; ++i) {
    cin >> queries[i].x >> queries[i].y;
    queries[i].id = i;
    queries[i].angle = atan2(queries[i].y, queries[i].x);
  }
  sort(queries, queries + q);

  function<void ()> solve = [&] () {
    vector<long long> crossv(q);
    int k = 0;
    point_t pp(queries[0].x, queries[0].y);
    while (1) {
      int pre = (k - 1 + all) % all, suf = (k + 1) % all;
      if (cross(pp, convex[k] - convex[pre]) <= 0 && cross(pp, convex[suf] - convex[k]) >= 0) {
        break;
      } else {
        k = (k + 1) % all;
      }
    }
    for (int i = 0, j = (k + 1) % all; i < q; ++i) {
      point_t pp(queries[i].x, queries[i].y);
      while (cross(pp, convex[j] - convex[k]) < 0) {
        k = (k + 1) % all;
        j = (j + 1) % all;
      }
      answer[queries[i].id] += cross(convex[k], pp);
    }
    return crossv;
  };

  solve();
  for (int i = 0; i < q; ++i) {
    queries[i].x = -queries[i].x;
    queries[i].y = -queries[i].y;
  }
  solve();
  for (int i = 0; i < q; ++i) {
    cout << abs(answer[i]) << '\n';
  }
  return 0;
}
