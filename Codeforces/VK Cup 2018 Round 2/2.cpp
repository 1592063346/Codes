#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, u, a[N];

int main() {
  scanf("%d%d", &n, &u);
  double answer = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  bool find = false;
  for (int i = 1, k = 1; i + 1 < n; ++i) {
    for (; k <= n && a[k] - a[i] <= u; ++k);
    --k;
    if (k >= i + 2) {
      find = true;
      answer = max(answer, 1 - (double) (a[i + 1] - a[i]) / (a[k] - a[i]));
    }
  }
  if (!find) {
    puts("-1");
  } else {
    printf("%.10lf\n", answer);
  }
  return 0;
}
