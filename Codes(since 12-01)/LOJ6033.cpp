#include<bits/stdc++.h>

using namespace std;

const int N = 1e2 + 10, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int n, m, t, visit[N][N];
pair<int, int> go[N][N];
vector<pair<int, int>> answer;
char grid[N][N];

bool find(int x, int y) {
  visit[x][y] = t;
  for (int i = 0; i < 4; ++i) {
    int a = x + dx[i], b = y + dy[i];
    if (a >= 1 && a <= n && b >= 1 && b <= m && grid[a][b] == '.' && visit[a][b] != t) {
      visit[a][b] = t;
      if (!go[a][b].first || find(go[a][b].first, go[a][b].second)) {
        go[a][b] = {x, y};
        go[x][y] = {a, b};
        return true;
      }
    }
  }
  return false;
}

void dfs(int x, int y) {
  visit[x][y] = t;
  answer.emplace_back(x, y);
  for (int i = 0; i < 4; ++i) {
    int a = x + dx[i], b = y + dy[i];
    if (a >= 1 && a <= n && b >= 1 && b <= m && grid[a][b] == '.' && visit[a][b] != t) {
      visit[a][b] = t;
      dfs(go[a][b].first, go[a][b].second);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", grid[i] + 1);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (grid[i][j] == '.' && !go[i][j].first) {
        ++t;
        find(i, j);
      }
    }
  }
  ++t;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (grid[i][j] == '.' && !go[i][j].first && visit[i][j] != t) {
        dfs(i, j);
      }
    }
  }
  sort(answer.begin(), answer.end());
  printf("%d\n", answer.size());
  for (auto x : answer) {
    printf("%d %d\n", x.first, x.second);
  }
  return 0;
}
