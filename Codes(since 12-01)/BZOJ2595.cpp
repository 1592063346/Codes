#include<bits/stdc++.h>

using namespace std;

const int N = 15, inf = 0x3f3f3f3f, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int n, m, k, a[N][N], id[N][N], f[N * N][1 << N];
pair<int, int> pre[N * N][1 << N];
bool inq[N * N], choice[N][N];

bool cmin(int& x, int y) {
  return x > y ? x = y, true : false;
}

void update(int s) {
  queue<int> que;
  for (int i = 0; i < n * m; ++i) {
    if (f[i][s] < inf) {
      que.push(i);
      inq[i] = true;
    }
  }
  while (!que.empty()) {
    int x = que.front() / m;
    int y = que.front() % m;
    int t = que.front();
    inq[t] = false;
    que.pop();
    for (int c = 0; c < 4; ++c) {
      int newx = x + dx[c];
      int newy = y + dy[c];
      int newt = newx * m + newy;
      if (~newx && ~newy && newx < n && newy < m) {
        if (cmin(f[newt][s], f[t][s] + a[newx][newy])) {
          pre[newt][s] = {t, s};
          if (!inq[newt]) {
            inq[newt] = true;
            que.push(newt);
          }
        }
      }
    }
  }
}

void restore(int t, int s) {
  if (!s) {
    return;
  }
  choice[t / m][t % m] = true;
  restore(pre[t][s].first, pre[t][s].second);
  if (pre[t][s].second && s != pre[t][s].second) {
    restore(pre[t][s].first, s ^ pre[t][s].second);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  memset(f, 0x3f, sizeof f);
  int endp;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      id[i][j] = i * m + j;
      scanf("%d", &a[i][j]);
      if (!a[i][j]) {
        f[id[i][j]][1 << k++] = 0;
        endp = id[i][j];
      }
    }
  }
  for (int s = 1; s < 1 << k; ++s) {
    for (int i = 0; i < n * m; ++i) {
      for (int s1 = s; s1; s1 = (s1 - 1) & s) {
        if (cmin(f[i][s], f[i][s1] + f[i][s ^ s1] - a[i / m][i % m])) {
          pre[i][s] = {i, s1};
        }
      }
    }
    update(s);
  }
  printf("%d\n", f[endp][(1 << k) - 1]);
  restore(endp, (1 << k) - 1);
  for (int i = 0; i < n; ++i, puts("")) {
    for (int j = 0; j < m; ++j) {
      if (!a[i][j]) {
        printf("x");
      } else {
        printf(choice[i][j] ? "o" : "_");
      }
    }
  }
  return 0;
}
