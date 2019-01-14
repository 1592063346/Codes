#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, m, from[N][2], a[N];
double answer[N];

int main() {
  srand(time(0));
  scanf("%d%d", &n, &m);
  int M = 100000000 / n;
  for (int i = m + 1; i <= n; ++i) {
    scanf("%d%d", &from[i][0], &from[i][1]);
  }
  for (int tt = 1; tt <= M; ++tt) {
    for (int i = 1; i <= m; ++i) {
      a[i] = rand();
    }
    for (int i = m + 1; i <= n; ++i) {
      a[i] = min(a[from[i][0]], a[from[i][1]]);
      answer[i] += a[i];
    }
  }
  for (int i = m + 1; i <= n; ++i) {
    answer[i] = ((double) RAND_MAX * M - answer[i]) / answer[i];
    printf("%.0lf\n", answer[i]);
  }
  return 0;
}
