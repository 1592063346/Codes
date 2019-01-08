#include<bits/stdc++.h>

using namespace std;

int n;

int main() {
  scanf("%d", &n);
  if (n % 4) {
    return puts("! -1"), 0;
  } else {
    int half = n >> 1;
    function<int (int)> query = [&] (int p) {
      int a, b;
      printf("? %d\n", p);
      fflush(stdout);
      scanf("%d", &a);
      printf("? %d\n", p + half);
      fflush(stdout);
      scanf("%d", &b);
      return a - b;
    };
    int result_1 = query(1);
    if (!result_1) {
      return puts("! 1"), 0;
    } else {
      int l = 1, r = half;
      while (l <= r) {
        int mid = l + r >> 1, result = query(mid);
        if (!result) {
          return printf("! %d\n", mid), 0;
        } else if ((result > 0 && result_1 > 0) || (result < 0 && result_1 < 0)) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      puts("! -1");
    }
  }
  return 0;
}
