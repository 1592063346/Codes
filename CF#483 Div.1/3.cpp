#include<bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10, inf = 0x3f3f3f3f;

int n, from[N], to[N], id[10][10][10][10], aid[720][4], tt, f[10][N][720];

struct info_t {
  int a, b, state;

  info_t () {}
  info_t (int a, int b, int state): a(a), b(b), state(state) {}
};

void add(int a, int b, int c, int d) {
  id[a][b][c][d] = ++tt;
  aid[tt][0] = a;
  aid[tt][1] = b;
  aid[tt][2] = c;
  aid[tt][3] = d;
}

int popcount(int s) {
  int result = 0;
  for (int i = 0; i < 4; ++i) {
    result += aid[s][i] != 9;
  }
  return result;
}

int insert(int s, int x) {
  vector<int> pos;
  for (int i = 0, from = 1; i < 4; ++i) {
    if (aid[s][i] == 9) {
      break;
    }
    from += aid[s][i];
    pos.push_back(from);
  }
  pos.push_back(x);
  sort(pos.begin(), pos.end());
  int a, b, c, d;
  a = pos.size() > 0 ? pos[0] - 1 : 9;
  b = pos.size() > 1 ? pos[1] - pos[0] : 9;
  c = pos.size() > 2 ? pos[2] - pos[1] : 9;
  d = pos.size() > 3 ? pos[3] - pos[2] : 9;
  return id[a][b][c][d];
}

int erase(int s, int x) {
  vector<int> pos;
  for (int i = 0, from = 1; i < 4; ++i) {
    if (aid[s][i] == 9) {
      break;
    }
    from += aid[s][i];
    if (from == x) {
      x = -1;
    } else {
      pos.push_back(from);
    }
  }
  sort(pos.begin(), pos.end());
  int a, b, c, d;
  a = pos.size() > 0 ? pos[0] - 1 : 9;
  b = pos.size() > 1 ? pos[1] - pos[0] : 9;
  c = pos.size() > 2 ? pos[2] - pos[1] : 9;
  d = pos.size() > 3 ? pos[3] - pos[2] : 9;
  return id[a][b][c][d];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &from[i], &to[i]);
  }
  add(9, 9, 9, 9);
  for (int i = 0; i <= 8; ++i) {
    add(i, 9, 9, 9);
    for (int j = 0; j <= 8 - i; ++j) {
      add(i, j, 9, 9);
      for (int k = 0; k <= 8 - i - j; ++k) {
        add(i, j, k, 9);
        for (int l = 0; l <= 8 - i - j - k; ++l) {
          add(i, j, k, l);
        }
      }
    }
  }
  queue<info_t> que;
  int empty_pos = id[9][9][9][9];
  memset(f, 0x3f, sizeof f);
  f[1][0][empty_pos] = 0;
  que.push(info_t(1, 0, empty_pos));
  while (!que.empty()) {
    info_t x = que.front();
    que.pop();
    int now = f[x.a][x.b][x.state];
    if (x.a > 1 && f[x.a - 1][x.b][x.state] == inf) {
      f[x.a - 1][x.b][x.state] = now + 1;
      que.push(info_t(x.a - 1, x.b, x.state));
    }
    if (x.a < 9 && f[x.a + 1][x.b][x.state] == inf) {
      f[x.a + 1][x.b][x.state] = now + 1;
      que.push(info_t(x.a + 1, x.b, x.state));
    }
    if (x.b < n && popcount(x.state) < 4 && from[x.b + 1] == x.a && f[x.a][x.b + 1][insert(x.state, to[x.b + 1])] == inf) {
      f[x.a][x.b + 1][insert(x.state, to[x.b + 1])] = now + 1;
      que.push(info_t(x.a, x.b + 1, insert(x.state, to[x.b + 1])));
    }
    for (int i = 0, from = 1; i < 4; ++i) {
      if (aid[x.state][i] == 9) {
        break;
      }
      from += aid[x.state][i];
      if (from == x.a && f[x.a][x.b][erase(x.state, x.a)] == inf) {
        f[x.a][x.b][erase(x.state, x.a)] = now + 1;
        que.push(info_t(x.a, x.b, erase(x.state, x.a)));
        break;
      }
    }
  }
  int answer = inf;
  for (int i = 1; i <= 9; ++i) {
    answer = min(answer, f[i][n][empty_pos]);
  }
  printf("%d\n", answer);
  return 0;
}
