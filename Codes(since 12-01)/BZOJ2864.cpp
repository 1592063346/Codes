#include<bits/stdc++.h>

using namespace std;

const int N = 22, max_node = N * N * N << 1;
const double eps = 1e-10, inf = 1e9;

int n, m, cur[max_node], dis[max_node], boss_id[N], plane_id[N], s, t, node_cnt;
pair<double, double> attack_time[N][N];

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
} boss[N];

double dot(point a, point b) {
  return a.x * b.x + a.y * b.y;
}

double cross(point a, point b) {
  return a.x * b.y - a.y * b.x;
}

double dist(point a, point b) {
  return sqrt(dot(a - b, a - b));
}

double dist_to_line(point p, point a, point b) {
  return fabs(cross(p - a, b - a)) / dist(a, b);
}

point get_projection(point p, point a, point b) {
  point v = a - b;
  return a + v * (dot(v, p - a) / dot(v, v));
}

struct circle {
  point center;
  double r;

  circle () {}
  circle (point center, double r): center(center), r(r) {}

  bool is_in(point p) {
    return dist(center, p) <= r;
  }
};

pair<point, point> get_intersection(circle cir, point a, point b) {
  point projection = get_projection(cir.center, a, b);
  point v = (a - b) / dist(a, b);
  double d = dist_to_line(cir.center, a, b);
  double moved = sqrt(cir.r * cir.r - d * d);
  return make_pair(point (projection.x + moved * v.x, projection.y + moved * v.y), point (projection.x - moved * v.x, projection.y - moved * v.y));
}

struct edge {
  int to;
  double cap, flow;

  edge () {}
  edge (int to, double cap, double flow): to(to), cap(cap), flow(flow) {}
};

vector<edge> edges;
vector<int> graph[max_node];

void add_edge(int u, int v, double cap) {
  edges.push_back(edge (v, cap, 0));
  edges.push_back(edge (u, 0, 0));
  graph[u].push_back(edges.size() - 2);
  graph[v].push_back(edges.size() - 1);
}

bool bfs() {
  queue<int> que;
  que.push(s);
  memset(dis, 0, sizeof dis);
  memset(cur, 0, sizeof cur);
  dis[s] = 1;
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (int i = 0; i < graph[x].size(); ++i) {
      edge& e = edges[graph[x][i]];
      if (e.cap - e.flow > eps && !dis[e.to]) {
        dis[e.to] = dis[x] + 1;
        que.push(e.to);
      }
    }
  }
  return dis[t] > 0;
}

double dfs(int u, double a) {
  if (a < eps || u == t) {
    return a;
  }
  double flow = 0, f;
  for (int& i = cur[u]; i < graph[u].size(); ++i) {
    edge& e = edges[graph[u][i]];
    if (dis[e.to] == dis[u] + 1 && (f = dfs(e.to, min(a, e.cap - e.flow))) > eps) {
      e.flow += f;
      edges[graph[u][i] ^ 1].flow -= f;
      flow += f;
      a -= f;
      if (a < eps) {
        break;
      }
    }
  }
  return flow;
}

double dinic() {
  double flow = 0;
  for (; bfs(); flow += dfs(s, inf));
  return flow;
}

int main() {
  scanf("%d%d", &n, &m);
  s = ++node_cnt;
  t = ++node_cnt;
  for (int i = 1; i <= n; ++i) {
    boss_id[i] = ++node_cnt;
    add_edge(boss_id[i], t, inf);
    scanf("%lf%lf", &boss[i].x, &boss[i].y);
  }
  vector<double> all;
  for (int i = 1; i <= m; ++i) {
    point from, to;
    double v, r, e;
    plane_id[i] = ++node_cnt;
    scanf("%lf%lf%lf%lf%lf%lf%lf", &from.x, &from.y, &to.x, &to.y, &v, &r, &e);
    add_edge(s, plane_id[i], e);
    point vec = (to - from) / dist(from, to);
    double end_time = dist(from, to) / v;
    for (int j = 1; j <= n; ++j) {
      if (dist_to_line(boss[j], from, to) <= r) {
        pair<point, point> result = get_intersection(circle (boss[j], r), from, to);
        result.first = result.first - from;
        result.second = result.second - from;
        double t1, t2;
        if (fabs(vec.x) > eps) {
          t1 = result.first.x / vec.x;
          t2 = result.second.x / vec.x;
        } else {
          t1 = result.first.y / vec.y;
          t2 = result.second.y / vec.y;
        }
        if (t1 > t2) {
          swap(t1, t2);
        }
        t1 /= v;
        t2 /= v;
        t1 = max(t1, 0.0);
        t2 = min(t2, end_time);
        attack_time[i][j] = {t1, t2};
        all.push_back(t1);
        all.push_back(t2);
      }
    }
  }
  sort(all.begin(), all.end());
  for (int k = 0; k + 1 < all.size(); ++k) {
    double l = all[k], r = all[k + 1];
    if (r - l > eps) {
      for (int i = 1; i <= n; ++i) {
        add_edge(++node_cnt, boss_id[i], r - l);
        for (int j = 1; j <= m; ++j) {
          if (l > attack_time[j][i].first - eps && r < attack_time[j][i].second + eps) {
            add_edge(plane_id[j], node_cnt, r - l);
          }
        }
      }
    }
  }
  printf("%.6lf\n", dinic());
  return 0;
}
