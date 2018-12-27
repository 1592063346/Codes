#include<bits/stdc++.h>

using namespace std;

int n;

int main() {
  scanf("%d", &n);
  int block = (int) sqrt(n), total = 0;
  for (int t = 1;; ++t) {
    for (int j = 1, k = max(1, n - t * block + 1); j <= block; ++j, ++k) {
      printf("%d ", k);
      if (++total == n) {
        return 0;
      }
    }
  }
  return 0;
}
