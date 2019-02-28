#include<bits/stdc++.h>

using namespace std;

const int N = 3e3 + 10;

int n, m;
char s[N][N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s[i] + 1);
  }
  int answer = 0;
  for (int i = 1, x, y; i <= n + m - 1; ++i) {
    if (i <= n) {
      x = i;
      y = 1;
    } else {
      x = n;
      y = i - n + 1;
    }
    int a = 0, b = 0, c = 0;
    for (; x >= 1 && y <= m; --x, ++y) {
      int ta = a, tb = b, tc = c;
      if (y < m && s[x][y - 1] == 'R' && s[x][y] == 'G' && s[x][y + 1] == 'W') {
        a = max(ta, tc) + 1;
      } else {
        a = 0;
      }
      if (x > 1 && s[x - 1][y] == 'R' && s[x][y] == 'G' && s[x + 1][y] == 'W') {
        b = max(tb, tc) + 1;
      } else {
        b = 0;
      }
      c = max(tc, max(ta, tb));
    }
    answer += max(a, max(b, c));
  }
  printf("%d\n", answer);
  return 0;
}
