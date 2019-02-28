#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, k, a[N], b[N];

int main() {
  scanf("%d%d", &n, &k);
  --k;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    b[i] = a[i] - a[i - 1] - 1;
  }
  sort(b + 2, b + 1 + n);
  int answer = a[n] + 1 - a[1];
  for (int i = n; i > n - k; --i) {
    answer -= b[i];
  }
  printf("%d\n", answer);
  return 0;
}
