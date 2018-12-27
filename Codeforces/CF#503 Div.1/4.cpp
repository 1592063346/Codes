#include<bits/stdc++.h>

using namespace std;

const int N = 2010;
const double eps = 1e-10;

int n, pos[N], rank_pos[N];
long long s;

bool same(double x, double y) {
  return fabs(x - y) < eps;
}

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
} points[N];

long long cross(point a, point b) {
  return (long long) a.x * b.y - (long long) a.y * b.x;
}

double area(point a, point b, point c) {
  return abs(cross(b - a, c - a)) * 0.5;
}

void print_solution(point a, point b, point c) {
  puts("Yes");
  printf("%d %d\n", a.x, a.y);
  printf("%d %d\n", b.x, b.y);
  printf("%d %d\n", c.x, c.y);
}

int main() {
  scanf("%d%I64d\n", &n, &s);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &points[i].x, &points[i].y);
  }
  sort(points + 1, points + 1 + n);
  for (int i = 1; i <= n; ++i) {
    pos[i] = rank_pos[i] = i;
  }
  vector<pair<double, pair<int, int>>> lines;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      double angle = atan2((points[j] - points[i]).y, (points[j] - points[i]).x);
      lines.emplace_back(angle, make_pair(i, j));
    }
  }
  sort(lines.begin(), lines.end());
  for (auto line : lines) {
    int a = line.second.first, b = line.second.second;
    if (rank_pos[a] > rank_pos[b]) {
      swap(a, b);
    }
    if (rank_pos[a] > 1) {
      int l = 1, r = rank_pos[a] - 1;
      while (l <= r) {
        int mid = l + r >> 1;
        double tarea = area(points[a], points[b], points[pos[mid]]);
        if (same(tarea, s)) {
          return print_solution(points[a], points[b], points[pos[mid]]), 0;
        } else if (tarea > s) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
    }
    if (rank_pos[b] < n) {
      int l = rank_pos[b] + 1, r = n;
      while (l <= r) {
        int mid = l + r >> 1;
        double tarea = area(points[a], points[b], points[pos[mid]]);
        if (same(tarea, s)) {
          return print_solution(points[a], points[b], points[pos[mid]]), 0;
        } else if (tarea > s) {
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
    }
    swap(rank_pos[a], rank_pos[b]);
    swap(pos[rank_pos[a]], pos[rank_pos[b]]);
  }
  return puts("No"), 0;
}
