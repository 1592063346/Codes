#include<bits/stdc++.h>

using namespace std;

const int N = 3e3 + 10;

int h, w, r[N][N], d[N][N];
char a[N][N];

int main() {
  scanf("%d%d", &h, &w);
  for (int i = 1; i <= h; ++i) {
    scanf("%s", a[i] + 1);
  }
  for (int i = 1; i <= h; ++i) {
    int number = 0;
    for (int j = w; j; --j) {
      if (a[i][j] == 'O') {
        ++number;
      }
      r[i][j] = number;
    }
  }
  for (int j = 1; j <= w; ++j) {
    int number = 0;
    for (int i = h; i; --i) {
      if (a[i][j] == 'I') {
        ++number;
      }
      d[i][j] = number;
    }
  }
  long long answer = 0;
  for (int i = 1; i <= h; ++i) {
    for (int j = 1; j <= w; ++j) {
      if (a[i][j] == 'J') {
        answer += r[i][j] * d[i][j];
      }
    }
  }
  printf("%lld\n", answer);
  return 0;
}
