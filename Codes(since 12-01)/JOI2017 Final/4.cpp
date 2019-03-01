#include<bits/stdc++.h>

using namespace std;

const int N = 5e2 + 10, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
const long long inf = 1e18;

bool cmin(long long& x, long long y) {
  return x > y ? x = y, true : false;
}

int h, w, n, x[N * N], y[N * N], near[N][N];
long long a, b, c, d[N][N][5];
bool visit[N][N][5];

struct node_t {
  int x, y, type;
  long long d;

  node_t() {}
  node_t(int x, int y, int type, long long d): x(x), y(y), type(type), d(d) {}

  bool operator < (const node_t& a) const {
    return d > a.d;
  }
};

int main() {
  scanf("%d%d%lld%lld%lld%d", &h, &w, &a, &b, &c, &n);
  queue<pair<int, int>> que;
  memset(near, -1, sizeof near);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
    que.emplace(x[i], y[i]);
    near[x[i]][y[i]] = 0;
  }
  while (!que.empty()) {
    pair<int, int> now = que.front();
    que.pop();
    for (int i = 0; i < 4; ++i) {
      int newx = now.first + dx[i];
      int newy = now.second + dy[i];
      if (newx >= 0 && newx <= h && newy >= 0 && newy <= w) {
        if (!~near[newx][newy]) {
          near[newx][newy] = near[now.first][now.second] + 1;
          que.emplace(newx, newy);
        }
      }
    }
  }
  for (int i = 0; i <= h; ++i) {
    for (int j = 0; j <= w; ++j) {
      for (int k = 0; k < 5; ++k) {
        d[i][j][k] = inf;
      }
    }
  }
  priority_queue<node_t> p_que;
  p_que.emplace(x[1], y[1], 4, 0);
  d[x[1]][y[1]][4] = 0;
  while (!p_que.empty()) {
    node_t now = p_que.top();
    p_que.pop();
    if (!visit[now.x][now.y][now.type]) {
      visit[now.x][now.y][now.type] = true;
      if (now.type != 4) {
        if (cmin(d[now.x][now.y][4], now.d + b + near[now.x][now.y] * c)) {
          p_que.emplace(now.x, now.y, 4, d[now.x][now.y][4]);
        }
        int newx = now.x + dx[now.type];
        int newy = now.y + dy[now.type];
        if (newx >= 0 && newx <= h && newy >= 0 && newy <= w) {
          if (cmin(d[newx][newy][now.type], now.d + a)) {
            p_que.emplace(newx, newy, now.type, d[newx][newy][now.type]);
          }
        }
      } else {
        for (int i = 0; i < 4; ++i) {
          int newx = now.x + dx[i];
          int newy = now.y + dy[i];
          if (newx >= 0 && newx <= h && newy >= 0 && newy <= w) {
            if (cmin(d[newx][newy][4], now.d + c)) {
              p_que.emplace(newx, newy, 4, d[newx][newy][4]);
            }
            if (cmin(d[newx][newy][i], now.d + a)) {
              p_que.emplace(newx, newy, i, d[newx][newy][i]);
            }
          }
        }
      }
    }
  }
  printf("%lld\n", d[x[n]][y[n]][4]);
  return 0;
}
