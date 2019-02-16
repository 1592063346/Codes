#include<bits/stdc++.h>

using namespace std;

const int N = 250, inf = 0x3f3f3f3f, tvalue = 1e6, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int tt, n, m, k, tran[N], c[N][N], a[N][N];
pair<int, int> f[N][1 << 5];
bool inq[N];

pair<int, int> operator + (const pair<int, int>& x, const pair<int, int>& y) {
  return {x.first + y.first, x.second + y.second};
}

pair<int, int> operator - (const pair<int, int>& x, const pair<int, int>& y) {
  return {x.first - y.first, x.second - y.second};
}

bool cmin(pair<int, int>& x, pair<int, int> y) {
  return x > y ? x = y, true : false;
}

void update(int s, int mid) {
  queue<int> que;
  for (int i = 0; i < n * m; ++i) {
    if (f[i][s].first != n * m + 1) {
      que.push(i);
      inq[i] = true;
    }
  }
  while (!que.empty()) {
    int t = que.front();
    int x = t / m;
    int y = t % m;
    inq[t] = false;
    que.pop();
    for (int d = 0; d < 4; ++d) {
      int newx = x + dx[d];
      int newy = y + dy[d];
      if (~newx && ~newy && newx < n && newy < m && ~c[newx][newy]) {
        int newt = newx * m + newy;
        if (cmin(f[newt][s], f[t][s] + pair<int, int>(1, tvalue + (a[newx][newy] > mid ? 1 : -1)))) {
          if (!inq[newt]) {
            inq[newt] = true;
            que.push(newt);
          }
        }
      }
    }
  }
}

int main() {
  srand(233);
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &c[i][j]);
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &a[i][j]);
      }
    }
    pair<int, int> answer = {n * m + 1, 0};
    for (int ttt = 1; ttt <= 100; ++ttt) {
      for (int i = 1; i <= n * m; ++i) {
        tran[i] = rand() % 5;
      }
      int l = 0, r = 1e6, min_total;
      while (l != r) {
        int mid = l + r >> 1;
        for (int s = 0; s < 1 << 5; ++s) {
          for (int i = 0; i < n * m; ++i) {
            f[i][s] = {n * m + 1, 0};
          }
        }
        for (int i = 0; i < n * m; ++i) {
          if (~c[i / m][i % m]) {
            f[i][1 << tran[c[i / m][i % m]]] = {1, tvalue + (a[i / m][i % m] > mid ? 1 : -1)};
          }
        }
        for (int s = 1; s < 1 << 5; ++s) {
          for (int i = 0; i < n * m; ++i) {
            for (int s1 = s; s1; s1 = (s1 - 1) & s) {
              cmin(f[i][s], f[i][s1] + f[i][s ^ s1] - pair<int, int>(1, tvalue + (a[i / m][i % m] > mid ? 1 : -1)));
            }
          }
          update(s, mid);
        }
        pair<int, int> result = {n * m + 1, 0};
        for (int i = 0; i < n * m; ++i) {
          cmin(result, f[i][(1 << 5) - 1]);
        }
        min_total = result.first;
        if (result.second <= result.first * tvalue) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      cmin(answer, {min_total, l});
    }
    if (answer.first == n * m + 1) {
      puts("-1 -1");
    } else {
      printf("%d %d\n", answer.first, answer.second);
    }
  }
  return 0;
}
