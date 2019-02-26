#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, inf = 0x3f3f3f3f, dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

bool cmin(int& x, int y) {
  return x > y ? x = y, true : false;
}

struct query_t {
  int x1, y1, x2, y2, id;

  query_t() {}
  query_t(int x1, int y1, int x2, int y2, int id): x1(x1), y1(y1), x2(x2), y2(y2), id(id) {}
} queries[N], tmp[N];

int n, m, q, answer[N];
vector<vector<int>> w[N];
vector<int> dist[N];
vector<bool> visit[N];

struct node_t {
  int x, y, d;

  node_t() {}
  node_t(int x, int y, int d): x(x), y(y), d(d) {}

  bool operator < (const node_t& a) const {
    return d > a.d;
  }
};

void dijkstra(int xl, int xr, int yl, int yr, int ql, int qr, vector<pair<int, int>>& sources) {
  for (auto p : sources) {
    for (int i = xl; i <= xr; ++i) {
      for (int j = yl; j <= yr; ++j) {
        visit[i][j] = false;
        dist[i][j] = inf;
      }
    }
    priority_queue<node_t> que;
    que.emplace(p.first, p.second, 0);
    dist[p.first][p.second] = 0;
    while (!que.empty()) {
      node_t u = que.top();
      que.pop();
      if (visit[u.x][u.y]) {
        continue;
      }
      for (int i = 0; i < 4; ++i) {
        int newx = u.x + dx[i];
        int newy = u.y + dy[i];
        if (newx >= xl && newx <= xr && newy >= yl && newy <= yr) {
          if (cmin(dist[newx][newy], dist[u.x][u.y] + w[u.x][u.y][i])) {
            que.emplace(newx, newy, dist[newx][newy]);
          }
        }
      }
    }
    for (int i = ql; i <= qr; ++i) {
      cmin(answer[queries[i].id], dist[queries[i].x1][queries[i].y1] + dist[queries[i].x2][queries[i].y2]);
    }
  }
}

void solve(int xl, int xr, int yl, int yr, int ql, int qr) {
  if (xr - xl < yr - yl) {
    int midy = yl + yr >> 1;
    vector<pair<int, int>> sources;
    for (int i = xl; i <= xr; ++i) {
      sources.emplace_back(i, midy);
    }
    dijkstra(xl, xr, yl, yr, ql, qr, sources);
    int tl = ql, tr = qr;
    for (int i = ql; i <= qr; ++i) {
      if (queries[i].y1 < midy && queries[i].y2 < midy) {
        tmp[tl++] = queries[i];
      } else if (queries[i].y1 > midy && queries[i].y2 > midy) {
        tmp[tr--] = queries[i];
      }
    }
    for (int i = ql; i <= qr; ++i) {
      queries[i] = tmp[i];
    }
    if (ql < tl) {
      solve(xl, xr, yl, midy - 1, ql, tl - 1);
    }
    if (tr < qr) {
      solve(xl, xr, midy + 1, yr, tr + 1, qr);
    }
  } else {
    int midx = xl + xr >> 1;
    vector<pair<int, int>> sources;
    for (int i = yl; i <= yr; ++i) {
      sources.emplace_back(midx, i);
    }
    dijkstra(xl, xr, yl, yr, ql, qr, sources);
    int tl = ql, tr = qr;
    for (int i = ql; i <= qr; ++i) {
      if (queries[i].x1 < midx && queries[i].x2 < midx) {
        tmp[tl++] = queries[i];
      } else if (queries[i].x1 > midx && queries[i].x2 > midx) {
        tmp[tr--] = queries[i];
      }
    }
    for (int i = ql; i <= qr; ++i) {
      queries[i] = tmp[i];
    }
    if (ql < tl) {
      solve(xl, midx - 1, yl, yr, ql, tl - 1);
    }
    if (tr < qr) {
      solve(midx + 1, xr, yl, yr, tr + 1, qr);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  vector<int> empty_vec(4);
  for (int i = 1; i <= n; ++i) {
    w[i].resize(m + 1, empty_vec);
    visit[i].resize(m + 1, false);
    dist[i].resize(m + 1, 0);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j < m; ++j) {
      scanf("%d", &w[i][j][0]);
      w[i][j + 1][2] = w[i][j][0];
    }
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &w[i][j][1]);
      w[i + 1][j][3] = w[i][j][1];
    }
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d%d%d", &queries[i].x1, &queries[i].y1, &queries[i].x2, &queries[i].y2);
    queries[i].id = i;
  }
  memset(answer, 0x3f, sizeof answer);
  solve(1, n, 1, m, 1, q);
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
