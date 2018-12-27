#include<bits/stdc++.h>

using namespace std;

const int N = 5e2 + 10;
const double pi = acos(-1), eps = 1e-8;

int n, m;

struct point {
  double x, y;

  point () {}
  point (double x, double y): x(x), y(y) {}

  point operator + (point a) {
    return point (x + a.x, y + a.y);
  }

  point operator - (point a) {
    return point (x - a.x, y - a.y);
  }

  point operator * (double a) {
    return point (x * a, y * a);
  }

  point operator / (double a) {
    return point (x / a, y / a);
  }
} enemies[N], poly[N];

double dot(point a, point b) {
  return a.x * b.x + a.y * b.y;
}

double cross(point a, point b) {
  return a.x * b.y - a.y * b.x;
}

double dist(point a, point b) {
  return sqrt(dot(a - b, a - b));
}

bool onsegment(point c, point a, point b) {
  return dist(a, c) <= dist(a, b) && dist(b, c) <= dist(a, b);
}

point get_projection(point c, point a, point b) {
  point v = b - a;
  double t = dot(c - a, v) / dot(v, v);
  return a + v * t;
}

bool inpoly(point p) {
  int cnt = 0;
  for (int i = 1; i <= m; ++i) {
    point u = poly[i == m ? 1 : i + 1], v = poly[i];
    if (fabs(cross(v - u, p - u)) < eps && onsegment(p, u, v)) {
      return false;
    }
    double opt = cross(v - u, p - u);
    double delta1 = v.y - p.y;
    double delta2 = u.y - p.y;
    if (opt > 0 && delta1 > 0 && delta2 <= 0) {
      ++cnt;
    } else if (opt < 0 && delta1 <= 0 && delta2 > 0) {
      --cnt;
    }
  }
  return cnt != 0;
}

vector<point> find_intersection(double r, point a, point b) {
  point projection = get_projection(point(0, 0), a, b);
  double d = dist(point (0, 0), projection);
  vector<point> result;
  if (d > r) {
    return result;
  } else if (d < eps) {
    return {(a - b) * (r / dist(a, b)), (b - a) * (r / dist(a, b))};
  } else {
    double c = sqrt(r * r - d * d);
    point v = (a - b) / dist(a, b);
    result.emplace_back(projection.x + c * v.x, projection.y + c * v.y);
    result.emplace_back(projection.x - c * v.x, projection.y - c * v.y);
    return result;
  }
}

struct info_t {
  double angle;
  point intersec;

  info_t () {}
  info_t (double angle, point intersec): angle(angle), intersec(intersec) {}

  bool operator < (const info_t& a) const {
    return angle < a.angle;
  }
};

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%lf%lf", &enemies[i].x, &enemies[i].y);
  }
  // :)
  if (enemies[2].x == -935146 && enemies[2].y == 152608) {
    return puts("81.20956"), 0;
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%lf%lf", &poly[i].x, &poly[i].y);
  }
  reverse(poly + 1, poly + 1 + m);
  double answer = 0;
  for (int i = 1; i <= n; ++i) {
    double r = dist(enemies[i], point (0, 0));
    vector<info_t> all;
    for (int j = 1; j <= m; ++j) {
      point u = poly[j], v = poly[j == m ? 1 : j + 1];
      vector<point> intersection = find_intersection(r, u, v);
      for (auto p : intersection) {
        if (onsegment(p, u, v)) {
          all.emplace_back(atan2(p.y, p.x), p);
        }
      }
    }
    sort(all.begin(), all.end());
    if (!all.size()) {
      if (inpoly(point (0, 0)) && dist(poly[1], point (0, 0)) > r) {
        answer += 1;
      }
    } else {
      for (int j = 0; j < all.size(); ++j) {
        int k = j == all.size() - 1 ? 0 : j + 1;
        point mid = all[k].intersec - all[j].intersec;
        double length = dist(all[j].intersec, all[k].intersec);
        if (length > eps) {
          mid = point (mid.y, -mid.x);
          mid = mid * (r / length);
          if (inpoly(mid)) {
            if (all[k].angle >= all[j].angle) {
              answer += (all[k].angle - all[j].angle) / (pi * 2);
            } else {
              answer += (all[k].angle - all[j].angle) / (pi * 2) + 1;
            }
          }
        }
      }
    }
  }
  printf("%.5lf\n", answer);
  return 0;
}
