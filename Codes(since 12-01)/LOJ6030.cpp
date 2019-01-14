#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

char grid[N][N];
int n, num_r[N], num_c[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", grid[i] + 1);
  }
  bool find = false;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (grid[i][j] == '#') {
        ++num_r[i];
        ++num_c[j];
        find = true;
      }
    }
  }
  if (!find) {
    return puts("-1"), 0;
  }
  int c_total = 0, answer = n << 1;
  for (int i = 1; i <= n; ++i) {
    if (num_c[i] != n) {
      ++c_total;
    }
  }
  for (int i = 1; i <= n; ++i) {
    answer = min(answer, c_total + n - num_r[i] + !num_c[i]);
  }
  printf("%d\n", answer);
  return 0;
}
