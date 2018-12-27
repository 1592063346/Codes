#include<bits/stdc++.h>

using namespace std;

long long n;

int query(long long x, long long y) {
  printf("%I64d %I64d\n", x, y);
  fflush(stdout);
  int result;
  scanf("%d", &result);
  return result;
}

int main() {
  scanf("%I64d", &n);
  long long x = 0, y = 0, deltax = 1, deltay = 1;
  while (1) {
    int result = query(x + deltax, y + deltay);
    if (!result) {
      break;
    } else if (result == 1) {
      x += deltax;
      deltax = min(deltax << 1, n - x);
    } else if (result == 2) {
      y += deltay;
      deltay = min(deltay << 1, n - y);
    } else {
      deltax = max(deltax >> 1, 1ll);
      deltay = max(deltay >> 1, 1ll);
    }
  }
  return 0;
}
