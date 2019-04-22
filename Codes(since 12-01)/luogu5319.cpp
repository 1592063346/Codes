#include<bits/stdc++.h>

using namespace std;

const int N = 2345;
const double inf = 1e18, eps = 1e-5;

bool cmax(double& x, double y) {
  if (x < y) {
    return x = y, true;
  } else {
    return false;
  }
}

int n, m, tt, where, ch[N][10], father[N], pre[N][N], number[N];
double value[N], w[N], f[N][N];
string t;

bool check(double x, bool way = false) {
  for (int i = 1; i <= tt; ++i) {
    w[i] = value[i] - number[i] * x;
  }
  f[0][0] = 0;
  fill(f[0] + 1, f[0] + 1 + tt, -inf);
  for (int i = 0; i < n; ++i) {
    fill(f[i + 1], f[i + 1] + 1 + tt, -inf);
    for (int j = 0; j <= tt; ++j) {
      for (int k = 0; k < 10; ++k) {
        if (t[i] == '.' || t[i] == '0' + k) {
          if (cmax(f[i + 1][ch[j][k]], f[i][j] + w[ch[j][k]]) && way) {
            pre[i + 1][ch[j][k]] = j;
          }
        }
      }
    }
  }
  double answer = -inf;
  for (int i = 0; i <= tt; ++i) {
    if (cmax(answer, f[n][i]) && way) {
      where = i;
    }
  }
  return answer > 0;
}

void print(int x, int y) {
  if (x) {
    print(x - 1, pre[x][y]);
    for (int i = 0; i < 10; ++i) {
      if (ch[pre[x][y]][i] == y && (t[x - 1] == '.' || t[x - 1] == '0' + i)) {
        cout << i;
        return;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> t;
  for (int i = 0; i < m; ++i) {
    string x;
    double y;
    cin >> x >> y;
    y = log(y);
    int l = x.length(), u = 0;
    for (int j = 0; j < l; ++j) {
      if (!ch[u][x[j] - '0']) {
        ch[u][x[j] - '0'] = ++tt;
      }
      u = ch[u][x[j] - '0'];
    }
    number[u] = 1;
    value[u] = y;
  }
  queue<int> q;
  for (int i = 0; i < 10; ++i) {
    if (ch[0][i]) {
      q.push(ch[0][i]);
    }
  }
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = 0; i < 10; ++i) {
      int& y = ch[x][i];
      if (!y) {
        y = ch[father[x]][i];
      } else {
        father[y] = ch[father[x]][i];
        number[y] += number[father[y]];
        value[y] += value[father[y]];
        q.push(y);
      }
    }
  }
  double l = 0, r = log(1e9);
  while (r - l > eps) {
    double mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  check(l, true);
  print(n, where);
  return 0;
}
