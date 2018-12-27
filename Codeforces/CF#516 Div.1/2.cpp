#include<bits/stdc++.h>

using namespace std;

#define X first
#define Y second
#define mp make_pair
#define rg register

typedef pair<int, int> pii;

const int N = 2e3 + 10, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int n, m, r, c, a, b, tag[N][N];
pii used[N][N];
char s[N][N];

struct State {
  int x, y;
  State () {}
  State (int x, int y): x(x), y(y) {}
  bool operator < (const State& a) const {
    return used[x][y].X + used[x][y].Y > used[a.x][a.y].X + used[a.x][a.y].Y;
  }
};

int main() {
  scanf("%d%d%d%d%d%d", &n, &m, &r, &c, &a, &b);
  for (rg int i = 1; i <= n; ++i) {
    scanf("%s", s[i] + 1);
  }
  tag[r][c] = 1;
  priority_queue<State> Q;
  Q.push(State (r, c));
  int ans = 1;
  while (!Q.empty()) {
    State o = Q.top(); Q.pop();
    int x = o.x, y = o.y;
    for (rg int i = 0; i < 4; ++i) {
      int new_x = x + dx[i], new_y = y + dy[i];
      if (tag[new_x][new_y]) {
        continue;
      }
      if (new_x < 1 || new_y < 1 || new_x > n || new_y > m || s[new_x][new_y] == '*') {
        continue;
      }
      if (used[x][y].X + (i == 3) > a) {
        continue;
      }
      if (used[x][y].Y + (i == 1) > b) {
        continue;
      }
      ++ans;
      tag[new_x][new_y] = 1;
      used[new_x][new_y] = pii(used[x][y].X + (i == 3), used[x][y].Y + (i == 1));
      Q.push(State (new_x, new_y));
    }
  }
  printf("%d\n", ans);
  return 0;
}
