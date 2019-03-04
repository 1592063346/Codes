#include<bits/stdc++.h>

using namespace std;

const int N = 4e2 + 10, inf = 0x3f3f3f3f;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, id[N], f[N][N][N][3], number[N][3];
vector<int> pos[3];
char s[N];

int main() {
  id['R'] = 0;
  id['G'] = 1;
  id['Y'] = 2;
  scanf("%d%s", &n, s + 1);
  for (int i = 1; i <= n; ++i) {
    pos[id[s[i]]].push_back(i);
    for (int j = 0; j < 3; ++j) {
      number[i][j] = pos[j].size();
    }
  }
  memset(f, 0x3f, sizeof f);
  f[0][0][0][0] = 0;
  f[0][0][0][1] = 0;
  f[0][0][0][2] = 0;
  for (int i = 0; i < n; ++i) {
    for (int a = 0; a <= i && a <= pos[0].size(); ++a) {
      for (int b = 0; a + b <= i && b <= pos[1].size(); ++b) {
        int c = i - a - b;
        if (c <= pos[2].size()) {
          for (int opt = 0; opt < 3; ++opt) {
            if (opt != 0 && a < pos[0].size()) {
              int p = pos[0][a];
              cmin(f[i + 1][a + 1][b][0], f[i][a][b][opt] + max(number[p][1] - b, 0) + max(number[p][2] - c, 0));
            }
            if (opt != 1 && b < pos[1].size()) {
              int p = pos[1][b];
              cmin(f[i + 1][a][b + 1][1], f[i][a][b][opt] + max(number[p][0] - a, 0) + max(number[p][2] - c, 0));
            }
            if (opt != 2 && c < pos[2].size()) {
              int p = pos[2][c];
              cmin(f[i + 1][a][b][2], f[i][a][b][opt] + max(number[p][0] - a, 0) + max(number[p][1] - b, 0));
            }
          }
        }
      }
    }
  }
  int answer = inf;
  for (int i = 0; i < 3; ++i) {
    cmin(answer, f[n][pos[0].size()][pos[1].size()][i]);
  }
  printf("%d\n", answer == inf ? -1 : answer);
  return 0;
}
