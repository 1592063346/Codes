#include<bits/stdc++.h>

using namespace std;

const int N = 5e2 + 10, inf = 0x3f3f3f3f, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

int n, w, h, go[N][N][4], f[10][10][N * N];
vector<int> mem[N * N];
char grid[N][N];

bool cmin(int& x, int y) {
  return x > y ? x = y, true : false;
}

int dfs(int x, int y, int opt) {
  if (go[x][y][opt]) {
    return go[x][y][opt];
  }
  go[x][y][opt] = -1;
  int oldopt = opt;
  if (grid[x][y] == 'C') {
    opt = (opt + 1) % 4;
  }
  if (grid[x][y] == 'A') {
    opt = (opt + 3) % 4;
  }
  int newx = x + dx[opt];
  int newy = y + dy[opt];
  if (!~newx || !~newy || newx >= h || newy >= w || grid[newx][newy] == 'x') {
    return go[x][y][oldopt] = x * w + y;
  } else {
    return go[x][y][oldopt] = dfs(newx, newy, opt);
  }
}

void update(int l, int r) {
  queue<int> que1, que2;
  for (int i = 0; i < h * w; ++i) {
    if (f[l][r][i] < inf) {
      mem[f[l][r][i]].push_back(i);
    }
  }
  for (int i = 0; i < h * w; ++i) {
    for (; mem[i].size(); mem[i].pop_back()) {
      que1.push(mem[i].back());
    }
  }
  while (!que1.empty() || !que2.empty()) {
    int t;
    if (que1.empty() || (!que2.empty() && f[l][r][que1.front()] > f[l][r][que2.front()])) {
      t = que2.front();
      que2.pop();
    } else {
      t = que1.front();
      que1.pop();
    }
    int x = t / w;
    int y = t % w;
    for (int opt = 0; opt < 4; ++opt) {
      if (~go[x][y][opt]) {
        int newt = go[x][y][opt];
        if (cmin(f[l][r][newt], f[l][r][t] + 1)) {
          que2.push(newt);
        }
      }
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &w, &h);
  for (int i = 0; i < h; ++i) {
    scanf("%s", grid[i]);
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (grid[i][j] != 'x') {
        for (int k = 0; k < 4; ++k) {
          dfs(i, j, k);
        }
      }
    }
  }
  memset(f, 0x3f, sizeof f);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (isdigit(grid[i][j])) {
        int id = grid[i][j] - '0';
        f[id][id][i * w + j] = 0;
      }
    }
  }
  for (int len = 0; len < n; ++len) {
    for (int l = 1; l + len <= n; ++l) {
      int r = l + len;
      for (int i = 0; i < h * w; ++i) {
        for (int p = l; p < r; ++p) {
          cmin(f[l][r][i], f[l][p][i] + f[p + 1][r][i]);
        }
      }
      update(l, r);
    }
  }
  int answer = inf;
  for (int i = 0; i < h * w; ++i) {
    cmin(answer, f[1][n][i]);
  }
  printf("%d\n", answer == inf ? -1 : answer);
  return 0;
}
