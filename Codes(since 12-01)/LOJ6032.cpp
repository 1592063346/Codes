#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m, tt, f[N], h[N], father[N][20], ch[N][2], be_true[N], be_false[N], dp[N][2];
vector<pair<int, int>> events[N];
pair<int, int> board[N];

int find(int x) {
  return f[x] == x ? x : f[x] = find(f[x]);
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d", &n, &m);
    int all = (n << 1) - 1;
    for (int i = 1; i <= all; ++i) {
      f[i] = i;
      events[i].clear();
    }
    for (int i = 1; i < n; ++i) {
      scanf("%d", &board[i].first);
      board[i].second = i;
    }
    sort(board + 1, board + n);
    memset(h, 0, sizeof h);
    memset(ch, 0, sizeof ch);
    memset(father, 0, sizeof father);
    for (int i = 1; i < n; ++i) {
      int x = find(board[i].second), y = find(board[i].second + 1);
      f[x] = father[x][0] = n + i;
      f[y] = father[y][0] = n + i;
      ch[n + i][0] = x;
      ch[n + i][1] = y;
      h[n + i] = board[i].first;
    }
    for (int j = 1; (1 << j) <= all; ++j) {
      for (int i = 1; i <= all; ++i) {
        father[i][j] = father[father[i][j - 1]][j - 1];
      }
    }
    for (int i = 1; i <= m; ++i) {
      int x, y, z;
      scanf("%d%d%d", &x, &y, &z);
      for (int j = 18; ~j; --j) {
        if (father[x][j] && h[father[x][j]] <= y) {
          x = father[x][j];
        }
      }
      events[x].emplace_back(y, z);
    }
    for (int i = 1; i <= all; ++i) {
      sort(events[i].begin(), events[i].end());
      int q = events[i].size();
      be_true[0] = 0;
      be_false[q + 1] = 0;
      for (int j = 1; j <= q; ++j) {
        be_true[j] = be_true[j - 1] + events[i][j - 1].second;
      }
      for (int j = q; j; --j) {
        be_false[j] = be_false[j + 1] + !events[i][j - 1].second;
      }
      int maxv = 0;
      for (int j = 0; j <= q; ++j) {
        maxv = max(maxv, be_true[j] + be_false[j + 1]);
      }
      int l = ch[i][0], r = ch[i][1];
      dp[i][0] = max(dp[l][0] + dp[r][0] + be_false[1], dp[l][1] + dp[r][1] + maxv);
      dp[i][1] = dp[l][1] + dp[r][1] + be_true[q];
    }
    printf("%d\n", max(dp[all][0], dp[all][1]));
  }
  return 0;
}
