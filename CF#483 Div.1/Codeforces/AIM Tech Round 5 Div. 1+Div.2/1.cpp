#include<bits/stdc++.h>

using namespace std;

const int N = 120;

int n, m;
char mat[N][N];

bool check_black(int i, int& l, int& r) {
  bool t = false;
  for (int j = 1; j <= m; ++j) {
    if (mat[i][j] == 'B') {
      t = true;
      if (j == 1 || mat[i][j - 1] ^ 'B') {
        l = j;
      }
      if (j == m || mat[i][j + 1] ^ 'B') {
        r = j;
      }
    }
  }
  return t;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", mat[i] + 1);
  }
  for (int i = 1; i <= n; ++i) {
    int l, r;
    if (check_black(i, l, r)) {
      int mid = (r - l) >> 1;
      return printf("%d %d\n", i + mid, l + mid), 0;
    }
  }
  return 0;
}
