#include<bits/stdc++.h>

using namespace std;

#define rg register

int q;

int main() {
  scanf("%d", &q);
  for (rg int i = 1; i <= q; ++i) {
    int l, r; scanf("%d%d", &l, &r);
    int pat = (r - l + 1) / 2;
    if (l & 1) {
      printf("%d\n", pat - ((r & 1) ? r : 0));
    } else {
      printf("%d\n", -pat + (!(r & 1) ? r : 0));
    }
  }
  return 0;
}
