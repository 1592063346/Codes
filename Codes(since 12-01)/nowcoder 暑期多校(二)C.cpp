#include<bits/stdc++.h>

using namespace std;

const int N = 54321;
const double inf = 1e18;

struct point_t {
  int x, y, id;

  point_t() {
  }

  point_t(int x, int y): x(x), y(y) {
  }

  point_t operator - (point_t a) {
    return point_t(x - a.x, y - a.y);
  }

  bool operator < (const point_t& a) const {
    return x < a.x;
  }
} p[N << 1];

long long cross(point_t a, point_t b) {
  return (long long) a.x * b.y - (long long) a.y * b.x;
}

int n, q;
double answer[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.setf(ios::fixed);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i].x >> p[i].y;
  }
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    answer[i] = inf;
    cin >> p[n + i].x >> p[n + i].y;
    p[n + i].id = i;
  }
  n += q;
  auto solve = [&] () {
    int foo;
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; ++i) {
      if (!p[i].id) {
        foo = p[i].y;
        break;
      }
    }
    for (int i = 1; i <= n; ++i) {
      p[i].y -= foo;
    }
    vector<point_t> up;
    int maxy = -1;
    for (int i = 1; i <= n; ++i) {
      if (p[i].id) {
        if (!up.size() || p[i].y > maxy) {
          continue;
        } else {
          int l = 0, r = up.size() - 1;
          while (l != r) {
            int mid = l + r >> 1;
            if (cross(up[mid + 1] - up[mid], p[i] - up[mid]) >= 0) {
              r = mid;
            } else {
              l = mid + 1;
            }
          }
          answer[p[i].id] = min(answer[p[i].id], (double) (up[l].y - p[i].y) / (up[l].x - p[i].x));
        }
      } else {
        int j;
        while ((j = up.size()) > 1 && cross(up[j - 1] - up[j - 2], p[i] - up[j - 2]) >= 0) {
          up.pop_back();
        }
        up.push_back(p[i]);
        maxy = max(maxy, p[i].y);
      }
    }
  };
  solve();
  for (int i = 1; i <= n; ++i) {
    p[i].x = -p[i].x;
    p[i].y = -p[i].y;
  }
  solve();
  for (int i = 1; i <= q; ++i) {
    if (answer[i] < 0) {
      cout << setprecision(10) << -answer[i] << '\n';
    } else {
      cout << "No cross" << '\n';
    }
  }
  return 0;
}
