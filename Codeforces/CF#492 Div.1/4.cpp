#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 18;

int n, r, a[N];

int main() {
  scanf("%d%d", &n, &r);
  n = 1 << n;
  double sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  printf("%.6lf\n", sum / n);
  for (int i = 1; i <= r; ++i) {
    int x, v;
    scanf("%d%d", &x, &v);
    sum += v - a[x];
    a[x] = v;
    printf("%.6lf\n", sum / n);
  }
  return 0;
}
