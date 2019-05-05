#include<bits/stdc++.h>

using namespace std;

const int N = 123456;
const long long llinf = 1e18;

int n, v, a[N];
vector<int> adj[N];
long long answer, adjsum[N], maxpre_f[N][105], g[N][105];

void dfs(int x, int f) {
  for (int i = 0; i < adj[x].size(); ++i) {
    int y = adj[x][i];
    if (y != f) {
      dfs(y, x);
      for (int j = 0; j <= v; ++j) {
        answer = max(answer, maxpre_f[y][v - j] + g[x][j]);
        if (j < v) {
          answer = max(answer, maxpre_f[y][v - j - 1] + g[x][j] + adjsum[x] - a[y]);
        }
        g[x][j] = max(g[x][j], g[y][j]);
        if (j) {
          g[x][j] = max(g[x][j], g[y][j - 1] + adjsum[y] - a[x]);
        }
        if (j < v) {
          answer = max(answer, adjsum[x] + g[x][j]);
        }
      }
    }
  }
  fill(g[x], g[x] + v + 1, 0);
  for (int i = adj[x].size() - 1; ~i; --i) {
    int y = adj[x][i];
    if (y != f) {
      for (int j = 0; j <= v; ++j) {
        answer = max(answer, maxpre_f[y][v - j] + g[x][j]);
        if (j < v) {
          answer = max(answer, maxpre_f[y][v - j - 1] + g[x][j] + adjsum[x] - a[y]);
        }
        g[x][j] = max(g[x][j], g[y][j]);
        if (j) {
          g[x][j] = max(g[x][j], g[y][j - 1] + adjsum[y] - a[x]);
        }
        if (j < v) {
          answer = max(answer, adjsum[x] + g[x][j]);
        }
      }
    }
  }
  if (f) {
    for (int i = v; i; --i) {
      for (int j = 0; j < adj[x].size(); ++j) {
        int y = adj[x][j];
        if (y != f) {
          maxpre_f[x][i] = max(maxpre_f[x][i], max(maxpre_f[y][i], maxpre_f[y][i - 1] + adjsum[x] - a[y]));
        }
      }
    }
    maxpre_f[x][1] = max(maxpre_f[x][1], adjsum[x]);
    for (int i = 1; i <= v; ++i) {
      maxpre_f[x][i] = max(maxpre_f[x][i], maxpre_f[x][i - 1]);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> v;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
    adjsum[x] += a[y];
    adjsum[y] += a[x];
  }
  dfs(1, 0);
  cout << answer << '\n';
  return 0;
}
