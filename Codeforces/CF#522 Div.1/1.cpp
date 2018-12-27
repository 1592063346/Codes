#include<bits/stdc++.h>

using namespace std;

const double eps = 1e-12;

double a, b, c, x1, y1, x2, y2;

template<typename T> inline bool checkMin(T& a, const T& b) {
  return a > b ? a = b, true : false;
}

inline double squ(double x) {
  return x * x;
}

inline double dist_s(double x1, double y1, double x2, double y2) {
  return sqrt(squ(x2 - x1) + squ(y2 - y1));
}

inline double dist_d(double x1, double y1, double x2, double y2) {
  return fabs(x2 - x1) + fabs(y2 - y1);
}

int main() {
  scanf("%lf%lf%lf%lf%lf%lf%lf", &a, &b, &c, &x1, &y1, &x2, &y2);
  double ans = dist_d(x1, y1, x2, y2);
  if (fabs(a) > eps) {
    double px1 = (-c - b * y1) / a;
    double px2 = (-c - b * y2) / a;
    checkMin(ans, dist_d(x1, y1, px1, y1) + dist_s(px1, y1, px2, y2) + dist_d(px2, y2, x2, y2));
  }
  if (fabs(b) > eps) {
    double py1 = (-c - a * x1) / b;
    double py2 = (-c - a * x2) / b;
    checkMin(ans, dist_d(x1, y1, x1, py1) + dist_s(x1, py1, x2, py2) + dist_d(x2, py2, x2, y2));
  }
  if (fabs(a) > eps && fabs(b) > eps) {
    double px1 = (-c - b * y1) / a;
    double px2 = (-c - b * y2) / a;
    double py1 = (-c - a * x1) / b;
    double py2 = (-c - a * x2) / b;
    checkMin(ans, dist_d(x1, y1, px1, y1) + dist_s(px1, y1, x2, py2) + dist_d(x2, py2, x2, y2));
    checkMin(ans, dist_d(x1, y1, x1, py1) + dist_s(x1, py1, px2, y2) + dist_d(px2, y2, x2, y2));
  }
  printf("%.10lf\n", ans);
  return 0;
}
