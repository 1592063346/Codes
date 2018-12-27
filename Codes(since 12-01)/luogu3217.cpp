#include<bits/stdc++.h>

using namespace std;

const int N = 1505;

void cmax(long long& x, long long y) {
  if (x < y) {
    x = y;
  }
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

long long dot(point a, point b) {
  return (long long) a.x * b.x + (long long) a.y * b.y;
}

long long cross(point a, point b) {
  return (long long) a.x * b.y - (long long) a.y * b.x;
}

long long area(point a, point b, point c, point d) {
  return abs(cross(b - a, c - a));
}

long long dist2(point a, point b) {
  return dot(a - b, a - b);
}

struct info_t {
  int x, y, len;
  vector<int> id;

  info_t () {}
  info_t (int x, int y, int len): x(x), y(y), len(len) {}

  bool operator < (const info_t& a) const {
    if (a.len == len) {
      return x == a.x ? y < a.y : x < a.x;
    } else {
      return len < a.len;
    }
  }

  bool operator == (const info_t& a) const {
    return len == a.len && x == a.x && y == a.y;
  }
};

int n;

int main() {
  scanf("%d", &n);
  vector<info_t> lines;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &points[i].x, &points[i].y);
    for (int j = 1; j < i; ++j) {
      lines.emplace_back(points[i].x + points[j].x, points[i].y + points[j].y, dist2(points[i], points[j]));
      lines.back().id = {i, j};
    }
  }
  sort(lines.begin(), lines.end());
  long long answer = 0;
  for (int i = 0, j; i < lines.size(); i = j) {
    for (j = i; j < lines.size() && lines[j] == lines[i]; ++j);
    for (int a = i; a < j; ++a) {
      for (int b = i; b < a; ++b) {
        cmax(answer, area(points[lines[a].id[0]], points[lines[a].id[1]], points[lines[b].id[0]], points[lines[b].id[1]]));
      }
    }
  }
  printf("%lld\n", answer);
  return 0;
}
