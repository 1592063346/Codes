#include<bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10;

int n, m, a[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n << 1; i += 2) {
    scanf("%d", &a[i]);
  }
  for (int i = 2; i <= n << 1; i += 2) {
    scanf("%d", &a[i]);
  }
  double total = m;
  for (int i = n << 1; i; --i) {
    if (a[i] == 1) {
      return puts("-1"), 0;
    } else {
      total += total / (a[i] - 1);
    }
  }
  printf("%.10lf\n", total - m);
  return 0;
}
