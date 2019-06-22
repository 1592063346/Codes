#include<bits/stdc++.h>

using namespace std;

const double eps = 1e-10;

const int N = 234;

int n, m, ch[N][26], id[N][N], father[N];
vector<pair<int, int>> adj[N];
string sw, sp;
double a[N][N], dp[N][N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.setf(ios::fixed);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    string c;
    cin >> x >> y >> c;
    adj[x].emplace_back(y, c[0] - 'a');
  }
  cin >> sw >> sp;
  int lenw = sw.length(), lenp = sp.length(), x = 0;
  for (int i = 0; i < lenw; ++i) {
    ch[x][sw[i] - 'a'] = i + 1;
    x = ch[x][sw[i] - 'a'];
  }
  for (int i = 1; i <= lenw; ++i) {
    for (int j = 0; j < 26; ++j) {
      if (!ch[i][j]) {
        ch[i][j] = ch[father[i]][j];
      } else {
        father[ch[i][j]] = ch[father[i]][j];
      }
    }
  }
  int tt = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= lenw; ++j) {
      id[i][j] = tt++;
    }
  }
  auto gauss = [&] () {
    for (int i = 0; i < tt; ++i) {
      if (fabs(a[i][i]) < eps) {
        int t = i;
        for (int j = i + 1; j < tt; ++j) {
          if (fabs(a[j][i]) > fabs(a[t][i])) {
            t = j;
          }
        }
        if (fabs(a[t][i]) < eps) {
          cout << -1 << '\n';
          exit(0);
        }
        for (int j = i; j <= tt; ++j) {
          swap(a[i][j], a[t][j]);
        }
      }
      for (int j = i + 1; j < tt; ++j) {
        double coef = a[j][i] / a[i][i];
        for (int k = i; k <= tt; ++k) {
          a[j][k] -= a[i][k] * coef;
        }
      }
    }
    for (int i = tt - 1; ~i; --i) {
      for (int j = i + 1; j < tt; ++j) {
        a[i][tt] -= a[i][j] * a[j][tt];
      }
      a[i][tt] /= a[i][i];
    }
  };
  for (int i = lenp - 1; ~i; --i) {
    memset(a, 0, sizeof a);
    for (int j = 1; j <= n; ++j) {
      a[id[j][lenw]][id[j][lenw]] = 1;
      int degree = adj[j].size();
      for (int k = 0; k < lenw; ++k) {
        int here = id[j][k];
        a[here][here] = 1;
        a[here][tt] = 1;
        for (auto e : adj[j]) {
          if (e.second == sp[i] - 'a') {
            a[here][tt] += dp[e.first][ch[k][e.second]][i + 1] / degree;
          } else {
            a[here][id[e.first][ch[k][e.second]]] -= 1.0 / degree;
          }
        }
      }
    }
    gauss();
    for (int j = 1; j <= n; ++j) {
      for (int k = 0; k <= lenw; ++k) {
        dp[j][k][i] = a[id[j][k]][tt];
      }
    }
  }
  cout << setprecision(10) << dp[1][0][0] << '\n';
  return 0;
}
