#include<bits/stdc++.h>

using namespace std;

const int table[] = {0, 1, 1, 5, 1, 21, 1, 85, 73, 341, 89, 1365, 1, 5461, 4681, 21845, 1, 87381, 1, 349525, 299593, 1398101, 178481, 5592405, 1082401};

int q;

int main() {
  scanf("%d", &q);
  while (q--) {
    int x;
    scanf("%d", &x);
    int p = 0;
    for (int i = 24; ~i; --i) {
      if (x >> i & 1) {
        p = i;
        break;
      }
    }
    int total = 0;
    for (int i = p; ~i; --i) {
      if (x >> i & 1) {
        ++total;
      }
    }
    if (total == p + 1) {
      printf("%d\n", table[p]);
    } else {
      printf("%d\n", (1 << p + 1) - 1);
    }
  }
  return 0;
}
