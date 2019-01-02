#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

struct matrix {
  int x, y;
  long long v;
} a[N];

int n, convex_hull[N];
long long f[N];

double slope(int i, int j) {
  return (double) (f[i] - f[j]) / (a[i].x - a[j].x);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%lld", &a[i].x, &a[i].y, &a[i].v);
  }
  sort(a + 1, a + 1 + n, [&] (const matrix& a, const matrix& b) {
    return a.x < b.x;
  });
  int ql = 0, qr = 0;
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    for (; ql < qr && slope(convex_hull[ql], convex_hull[ql + 1]) >= a[i].y; ++ql);
    int j = convex_hull[ql];
    f[i] = f[j] + (long long) a[i].y * (a[i].x - a[j].x) - a[i].v;
    answer = max(answer, f[i]);
    for (; ql < qr && slope(convex_hull[qr], i) >= slope(convex_hull[qr - 1], i); --qr);
    convex_hull[++qr] = i;
  }
  printf("%lld\n", answer);
  return 0;
}
