#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, k, t, x[N];
long long y[N];

bool check(int s) {
  for (int i = 1; i <= n; ++i) {
    y[i] = x[i] - 2ll * s * t * i;
  }
  if (y[1] < y[n]) {
    return false;
  }
  int l = k, r = k, oldl, oldr;
  while (1) {
    oldl = l;
    oldr = r;
    for (int p = l; p >= 1 && y[p] >= y[r]; --p) {
      if (y[p] >= y[l]) {
        l = p;
      }
    }
    for (int p = r; p <= n && y[p] <= y[l]; ++p) {
      if (y[p] <= y[r]) {
        r = p;
      }
    }
    if (oldl == l && oldr == r) {
      break;
    }
  }
  int tmpl = l, tmpr = r;
  l = 1, r = n;
  while (1) {
    oldl = l;
    oldr = r;
    for (int p = l; p <= n && y[p] >= y[r]; ++p) {
      if (y[p] >= y[l]) {
        l = p;
      }
    }
    for (int p = r; p >= 1 && y[p] <= y[l]; --p) {
      if (y[p] <= y[r]) {
        r = p;
      }
    }
    if (oldl == l && oldr == r) {
      break;
    }
  }
  return tmpl <= l && tmpr >= r;
}

int main() {
  scanf("%d%d%d", &n, &k, &t);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x[i]);
  }
  int l = 0, r = 1e9;
  while (l != r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  printf("%d\n", l);
  return 0;
}
