#include<bits/stdc++.h>

using namespace std;

#define rg register

typedef long long ll;

template<typename T> inline bool checkMax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}

const int N = 1e5 + 10;
const double eps = 1e-12;

int n, a[N], b[N], top;
ll times;
double p[N], m;

struct Point {
  double x, y;
  Point () {}
  Point (double x, double y): x(x), y(y) {}
} points[N], _stack[N];

inline double slope(Point a, Point b) {
  return fabs(a.x - b.x) < eps ? 1e100 : (b.y - a.y) / (b.x - a.x);
}

struct Matrix {
  double a[4][4];
  Matrix () {
    memset(a, 0, sizeof a);
  }
  Matrix operator * (const Matrix& b) const {
    Matrix res;
    for (rg int i = 0; i < 4; ++i) {
      for (rg int j = 0; j < 4; ++j) {
        for (rg int k = 0; k < 4; ++k) {
          res.a[i][j] += a[i][k] * b.a[k][j];
        }
      }
    }
    return res;
  }
} mat, trans[40];

int main() {
  scanf("%d%I64d", &n, &times);
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d%d%lf", &a[i], &b[i], &p[i]);
    points[i] = Point (-p[i], a[i] * p[i]);
    checkMax(m, p[i] * b[i]);
  }
  sort(points + 1, points + 1 + n, [] (const Point& a, const Point& b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
  });
  _stack[top = 1] = points[1];
  for (rg int i = 2; i <= n; ++i) {
    for (; top > 1 && slope(_stack[top], points[i]) >= slope(_stack[top - 1], _stack[top]); --top);
    _stack[++top] = points[i];
  }
  ll now = 0;
  trans[0].a[1][0] = 1;
  trans[0].a[1][1] = 1;
  trans[0].a[2][0] = 1;
  trans[0].a[2][2] = 1;
  trans[0].a[3][2] = 1;
  trans[0].a[3][3] = 1;
  for (rg int i = top; i && now ^ times; --i) {
    double r = i == 1 ? 1e100 : slope(_stack[i - 1], _stack[i]);
    double x = -_stack[i].x, y = _stack[i].y;
    mat.a[0][1] = y;
    mat.a[0][2] = now * x * m;
    mat.a[0][3] = x * m;
    trans[0].a[0][0] = 1 - x;
    if (now * m - mat.a[0][0] > r) {
      continue;
    }
    for (rg int j = 1; j < 34; ++j) {
      trans[j] = trans[j - 1] * trans[j - 1];
    }
    for (rg int j = 33; ~j; --j) {
      if (now + (1ll << j) >= times) {
        continue;
      }
      Matrix old = mat;
      mat = mat * trans[j];
      double k = (now + (1ll << j)) * m - mat.a[0][0];
      if (k >= r) {
        mat = old;
        continue;
      }
      now += 1ll << j;
    }
    ++now;
    mat = mat * trans[0];
  }
  printf("%.15lf\n", mat.a[0][0]);
  return 0;
}
