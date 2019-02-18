#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, k, a[N], h[N], t;

int main() {
  scanf("%d%*d%d", &n, &k);
  int answer = k;
  --k;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    if (i >= 2) {
      h[++t] = a[i] - a[i - 1];
      answer += a[i] - a[i - 1];
    }
  }
  sort(h + 1, h + 1 + t, greater<int>());
  for (int i = 1; i <= k; ++i) {
    answer -= h[i];
  }
  printf("%d\n", answer);
  return 0;
}
