#include<bits/stdc++.h>

using namespace std;

int query(int x) {
  printf("%d\n", x);
  fflush(stdout);
  int result;
  scanf("%d", &result);
  return result;
}

int n, m, type[35];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int result = query(1);
    if (result == 0) {
      return 0;
    } else {
      type[i] = result;
    }
  }
  int l = 1, r = n, round = 1;
  while (l <= r) {
    int mid = l + r >> 1, result = query(mid);
    if (result == 0) {
      return 0;
    } else if (result * type[round] == -1) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
    round = round % m + 1;
  }
  return 0;
}
