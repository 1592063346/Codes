#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, q, a[N];
long long s, t, b[N], temp;

void modify(int p, int coef) {
  if (b[p] > 0) {
    temp -= b[p] * s * coef;
  } else {
    temp -= b[p] * t * coef;
  }
}

int main() {
  scanf("%d%d%lld%lld", &n, &q, &s, &t);
  for (int i = 0; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    b[i] = a[i] - a[i - 1];
  }
  for (int i = 1; i <= n; ++i) {
    modify(i, 1);
  }
  while (q--) {
    int l, r, x;
    scanf("%d%d%d", &l, &r, &x);
    modify(l, -1);
    b[l] += x;
    modify(l, 1);
    if (r != n) {
      modify(r + 1, -1);
      b[r + 1] -= x;
      modify(r + 1, 1);
    }
    printf("%lld\n", temp);
  }
  return 0;
}
