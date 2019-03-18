#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10, inf = 0x3f3f3f3f;
const char choice[6][5] = {"ACGT", "AGCT", "ATCG", "CGAT", "CTAG", "GTAC"};

char s[N], a[2], b[2];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<char>> grid(n + 1, vector<char>(m + 1)), tmp, best;
  tmp = best = grid;
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s + 1);
    for (int j = 1; j <= m; ++j) {
      grid[i][j] = s[j];
    }
  }
  int answer = inf;
  for (int k = 0; k < 6; ++k) {
    int result = 0;
    for (int i = 1; i <= n; ++i) {
      a[0] = choice[k][i & 1 ? 0 : 2];
      a[1] = choice[k][i & 1 ? 1 : 3];
      b[0] = a[1];
      b[1] = a[0];
      int diffa = 0, diffb = 0;
      for (int j = 1, t = 0; j <= m; ++j, t = (t + 1) % 2) {
        diffa += a[t] != grid[i][j];
        diffb += b[t] != grid[i][j];
      }
      for (int j = 1, t = 0; j <= m; ++j, t = (t + 1) % 2) {
        tmp[i][j] = diffa < diffb ? a[t] : b[t];
      }
      result += min(diffa, diffb);
    }
    if (result < answer) {
      answer = result;
      best = tmp;
    }
  }
  for (int k = 0; k < 6; ++k) {
    int result = 0;
    for (int i = 1; i <= m; ++i) {
      a[0] = choice[k][i & 1 ? 0 : 2];
      a[1] = choice[k][i & 1 ? 1 : 3];
      b[0] = a[1];
      b[1] = a[0];
      int diffa = 0, diffb = 0;
      for (int j = 1, t = 0; j <= n; ++j, t = (t + 1) % 2) {
        diffa += a[t] != grid[j][i];
        diffb += b[t] != grid[j][i];
      }
      for (int j = 1, t = 0; j <= n; ++j, t = (t + 1) % 2) {
        tmp[j][i] = diffa < diffb ? a[t] : b[t];
      }
      result += min(diffa, diffb);
    }
    if (result < answer) {
      answer = result;
      best = tmp;
    }
  }
  for (int i = 1; i <= n; ++i, puts("")) {
    for (int j = 1; j <= m; ++j) {
      printf("%c", best[i][j]);
    }
  }
  return 0;
}
