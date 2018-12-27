#include<bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;
const double eps = 1e-10;

int n, p_total, visit[N];
double v, dist[N];
vector<pair<int, double>> graph[N];

void add_edge(int u, int v, double dis) {
  graph[u].emplace_back(v, dis);
  graph[v].emplace_back(u, dis);
}

struct point {
  int id;
  double x, y;

  point () {}
  point (double x, double y): x(x), y(y) {}

  point operator - (point a) {
    return point (x - a.x, y - a.y);
  }

  bool operator == (point a) {
    return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
  }
} s, t, normal_y (0, 1);

double dot(point a, point b) {
  return a.x * b.x + a.y * b.y;
}

double slope(point a) {
  return fabs(a.x) < eps ? (a.y < 0 ? -1e8 : 1e8) : a.y / a.x;
}

double point_dist(point a, point b) {
  return sqrt(dot(a - b, a - b));
}

struct matrix {
  point vert[4];

  bool is_in(point p) {
    return p.x >= vert[0].x && p.x <= vert[2].x && p.y >= vert[0].y && p.y <= vert[1].y;
  }
} mat[N];

struct info_t {
  int u;
  double d;

  info_t () {}
  info_t (int u, double d): u(u), d(d) {}

  bool operator < (const info_t& a) const {
    return d > a.d;
  }
};

void dijkstra(int u) {
  priority_queue<info_t> que;
  for (int i = 1; i <= p_total; ++i) {
    dist[i] = 1e9;
  }
  que.push(info_t(u, 0));
  dist[u] = 0;
  while (!que.empty()) {
    int x = que.top().u;
    que.pop();
    if (!visit[x]) {
      visit[x] = 1;
      for (auto v : graph[x]) {
        if (dist[v.first] > dist[x] + v.second) {
          dist[v.first] = dist[x] + v.second;
          que.push(info_t(v.first, dist[v.first]));
        }
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lf%lf%lf%lf", &mat[i].vert[0].x, &mat[i].vert[0].y, &mat[i].vert[3].x, &mat[i].vert[3].y);
    mat[i].vert[1] = point (mat[i].vert[0].x, mat[i].vert[3].y);
    mat[i].vert[2] = point (mat[i].vert[3].x, mat[i].vert[0].y);
    for (int j = 0; j < 4; ++j) {
      mat[i].vert[j].id = ++p_total;
    }
  }
  scanf("%lf%lf%lf%lf%lf", &s.x, &s.y, &t.x, &t.y, &v);
  if (s.x > t.x) {
    swap(s, t);
  }
  s.id = ++p_total;
  t.id = ++p_total;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 2; k < 4; ++k) {
        add_edge(mat[i].vert[j].id, mat[i].vert[k].id, point_dist(mat[i].vert[j], mat[i].vert[k]));
      }
    }
    function<void (point, double, double, int)> calc = [&] (point now, double l, double r, int i) {
      for (int j = i + 1; j <= n; ++j) {
        for (int k = 0; k < 4; k += 2) {
          double opt = slope(mat[j].vert[k] - now);
          if (opt >= l - eps && opt <= r + eps) {
            add_edge(now.id, mat[j].vert[k].id, point_dist(now, mat[j].vert[k]));
          }
          opt = slope(mat[j].vert[k + 1] - now);
          if (opt >= l - eps && opt <= r + eps) {
            add_edge(now.id, mat[j].vert[k + 1].id, point_dist(now, mat[j].vert[k + 1]));
          }
          l = now == mat[j].vert[k] ? l : max(l, slope(mat[j].vert[k] - now));
          r = now == mat[j].vert[k + 1] ? r : min(r, slope(mat[j].vert[k + 1] - now));
          if (!k && mat[j].is_in(t)) {
            double opt = slope(t - now);
            if (opt >= l - eps && opt <= r + eps) {
              add_edge(now.id, t.id, point_dist(now, t));
            }
          }
        }
      }
    };
    if (i == 1 || mat[i].vert[0].y > mat[i - 1].vert[2].y) {
      calc(mat[i].vert[0], slope(mat[i].vert[2] - mat[i].vert[0]), slope(mat[i].vert[3] - mat[i].vert[0]), i);
    }
    if (i == 1 || mat[i].vert[1].y < mat[i - 1].vert[3].y) {
      calc(mat[i].vert[1], slope(mat[i].vert[2] - mat[i].vert[1]), slope(mat[i].vert[3] - mat[i].vert[1]), i);
    }
    if (i < n && mat[i].vert[2].y > mat[i + 1].vert[0].y) {
      calc(mat[i].vert[2], -1e9, 1e9, i);
    }
    if (i < n && mat[i].vert[3].y < mat[i + 1].vert[1].y) {
      calc(mat[i].vert[3], -1e9, 1e9, i);
    }
    if (mat[i].is_in(s)) {
      for (int j = 0; j < 4; ++j) {
        add_edge(s.id, mat[i].vert[j].id, point_dist(s, mat[i].vert[j]));
      }
      if (mat[i].is_in(t)) {
        add_edge(s.id, t.id, point_dist(s, t));
      }
      calc(s, s == mat[i].vert[2] ? -1e9 : slope(mat[i].vert[2] - s), s == mat[i].vert[3] ? 1e9 : slope(mat[i].vert[3] - s), i);
    }
    if (mat[i].is_in(t)) {
      for (int j = 0; j < 4; ++j) {
        add_edge(mat[i].vert[j].id, t.id, point_dist(t, mat[i].vert[j]));
      }
    }
  }
  dijkstra(s.id);
  printf("%.8lf\n", dist[t.id] / v);
  return 0;
}
