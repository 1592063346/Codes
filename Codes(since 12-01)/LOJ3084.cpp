#include<bits/stdc++.h>

using namespace std;

const int N = 45;
const vector<int> range = {0, 1, 9, 10, 18, 19, 27, 28, 29, 30, 31, 32, 33, 34};

void cmax(long long& x, long long y) {
  if (x < y) {
    x = y;
  }
}

int tt, all, binom[5][5], power[3][5], number[N], times[N];
long long dp[N][5][5][5][2];

int id(string x) {
  if (isdigit(x[0])) {
    return x[0] - '0' + (x[1] == 'm' ? 0 : x[1] == 'p' ? 9 : 18);
  } else {
    switch (x[0]) {
     case 'E':
      return 28;
     case 'S':
      return 29;
     case 'W':
      return 30;
     case 'N':
      return 31;
     case 'Z':
      return 32;
     case 'F':
      return 33;
     case 'B':
      return 34;
    }
  }
}

void init() {
  all = 34;
  binom[0][0] = binom[1][0] = binom[1][1] = binom[2][0] = binom[2][2] = binom[3][0] = binom[3][3] = binom[4][0] = binom[4][4] = 1;
  binom[2][1] = 2;
  binom[3][1] = binom[3][2] = 3;
  binom[4][1] = binom[4][3] = 4;
  binom[4][2] = 6;
  power[1][0] = power[1][1] = power[1][2] = power[1][3] = power[1][4] = power[2][0] = 1;
  power[2][1] = 2;
  power[2][2] = 4;
  power[2][3] = 8;
  power[2][4] = 16;
}

bool in(int x, const int l, const int r) {
  return x >= l && x <= r;
}

long long solve_normal() {
  memset(dp, 0, sizeof dp);
  dp[0][0][0][0][0] = 1;
  for (int i = 1; i <= all; ++i) {
    for (int j = 0; j < 5; ++j) {
      for (int a = 0; a < 3 && j + a < 5; ++a) {
        if (a && (in(i, 1, 2) || in(i, 10, 11) || in(i, 19, 20) || in(i, 28, 34))) {
          continue;
        }
        for (int b = 0; b < 3 && j + a + b < 5; ++b) {
          if (b && (in(i, 1, 1) || in(i, 9, 10) || in(i, 18, 19) || in(i, 27, 34))) {
            continue;
          }
          for (int c = 0; c < 3 && j + a + b + c < 5; ++c) {
            if (c && (in(i, 8, 9) || in(i, 17, 18) || in(i, 26, 34))) {
              continue;
            }
            for (int op = 0; op < 2; ++op) {
              cmax(dp[i][j + a][b][c][op], dp[i - 1][j][a][b][op] * binom[number[i]][a + b + c] * power[times[i]][a + b + c]);
            }
            if (a + b + c + 2 < 5) {
              cmax(dp[i][j + a][b][c][1], dp[i - 1][j][a][b][0] * binom[number[i]][a + b + c + 2] * power[times[i]][a + b + c + 2]);
            }
            if (a + b + c + 3 < 5 && j + a + b + c + 1 < 5) {
              for (int op = 0; op < 2; ++op) {
                cmax(dp[i][j + a + 1][b][c][op], dp[i - 1][j][a][b][op] * binom[number[i]][a + b + c + 3] * power[times[i]][a + b + c + 3]);
              }
            }
            if (a + b + c + 4 < 5 && j + a + b + c + 1 < 5) {
              for (int op = 0; op < 2; ++op) {
                cmax(dp[i][j + a + 1][b][c][op], dp[i - 1][j][a][b][op] * binom[number[i]][a + b + c + 4] * power[times[i]][a + b + c + 4]);
              }
            }
          }
        }
      }
    }
  }
  return dp[all][4][0][0][1];
}

long long solve_7pairs() {
  int need = 7;
  vector<long long> f(need + 1);
  f[0] = 1;
  for (int i = 1; i <= all; ++i) {
    for (int j = need - 1; ~j; --j) {
      cmax(f[j + 1], f[j] * binom[number[i]][2] * power[times[i]][2]);
    }
  }
  return f[need] * need;
}

long long solve_specialness() {
  int need = 13;
  vector<long long> pre(need + 2, 1), suf(need + 2, 1);
  for (int i = 1; i <= need; ++i) {
    pre[i] = pre[i - 1] * binom[number[range[i]]][1] * times[range[i]];
  }
  for (int i = need; i; --i) {
    suf[i] = suf[i + 1] * binom[number[range[i]]][1] * times[range[i]];
  }
  long long result = 0;
  for (int i = 1; i <= need; ++i) {
    cmax(result, pre[i - 1] * suf[i + 1] * binom[number[range[i]]][2] * power[times[range[i]]][2]);
  }
  return result * need;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  init();
  cin >> tt;
  while (tt--) {
    memset(number, 0, sizeof number);
    string x;
    while (cin >> x && x != "0") {
      ++number[id(x)];
    }
    for (int i = 1; i <= all; ++i) {
      number[i] = 4 - number[i];
      times[i] = 1;
    }
    while (cin >> x && x != "0") {
      times[id(x)] = 2;
    }
    cout << max(solve_normal(), max(solve_7pairs(), solve_specialness())) << '\n';
  }
  return 0;
}
