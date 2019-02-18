#include<bits/stdc++.h>

using namespace std;

const int N = 2e4 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, len_l, len_r, node_cnt, ch[N][10], father[N], number[N][2010], f[2010][N], best[2010][N];
char str_l[N], str_r[N];

void get_fail() {
  queue<int> que;
  for (int i = 0; i < 10; ++i) {
    if (ch[0][i]) {
      que.push(ch[0][i]);
    }
  }
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (int i = 0; i < 10; ++i) {
      int& u = ch[x][i];
      if (!u) {
        u = ch[father[x]][i];
      } else {
        father[u] = ch[father[x]][i];
        for (int j = 0; j <= n; ++j) {
          number[u][j] += number[father[u]][j];
        }
        que.push(u);
      }
    }
  }
}

void insert(int p, int c, int from, bool limit_l, bool limit_r, bool all_zero) {
  if (!all_zero) {
    if (!ch[from][c - '0']) {
      ch[from][c - '0'] = ++node_cnt;
    }
    from = ch[from][c - '0'];
  }
  if ((!limit_l && !limit_r) || p == len_l) {
    ++number[from][len_l - p];
    return;
  }
  int l = limit_l ? str_l[p + 1] : '0';
  int r = limit_r ? str_r[p + 1] : '9';
  for (int i = l; i <= r; ++i) {
    insert(p + 1, i, from, limit_l & (i == l), limit_r & (i == r), all_zero & (i == '0'));
  }
}

int main() {
  scanf("%s%s%d", str_l + 1, str_r + 1, &n);
  len_l = strlen(str_l + 1);
  len_r = strlen(str_r + 1);
  if (len_r - len_l) {
    for (int i = len_l; i; --i) {
      str_l[i + len_r - len_l] = str_l[i];
    }
    for (int i = 1; i <= len_r - len_l; ++i) {
      str_l[i] = '0';
    }
    len_l = len_r;
  }
  for (int i = str_l[1]; i <= str_r[1]; ++i) {
    insert(1, i, 0, i == str_l[1], i == str_r[1], i == '0');
  }
  get_fail();
  for (int i = 1; i <= node_cnt; ++i) {
    for (int j = 1; j <= n; ++j) {
      number[i][j] += number[i][j - 1];
    }
  }
  memset(f, 0xc0, sizeof f);
  f[0][0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= node_cnt; ++j) {
      for (int k = 0; k < 10; ++k) {
        int go = ch[j][k];
        cmax(f[i + 1][go], f[i][j] + number[go][n - i - 1]);
      }
    }
  }
  int answer = 0;
  for (int i = 0; i <= node_cnt; ++i) {
    cmax(answer, f[n][i]);
  }
  printf("%d\n", answer);
  for (int i = 0; i <= node_cnt; ++i) {
    if (f[n][i] == answer) {
      best[n][i] = true;
    }
  }
  for (int i = n - 1; ~i; --i) {
    for (int j = 0; j <= node_cnt; ++j) {
      for (int k = 0; k < 10; ++k) {
        int go = ch[j][k];
        if (f[i + 1][go] == f[i][j] + number[go][n - i - 1]) {
          best[i][j] |= best[i + 1][go];
        }
      }
    }
  }
  int u = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 10; ++j) {
      int go = ch[u][j];
      if (f[i + 1][go] == f[i][u] + number[go][n - i - 1] && best[i + 1][go]) {
        printf("%d", j);
        u = go;
        break;
      }
    }
  }
  return puts(""), 0;
}
