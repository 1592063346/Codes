#include<bits/stdc++.h>

using namespace std;

int main() {
  int tt, l, r;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d", &l, &r);
    printf("%d %d\n", l, (l << 1));
  }
  return 0;
}
