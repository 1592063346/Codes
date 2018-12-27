#include<bits/stdc++.h>

using namespace std;

int n, a, b, c, d;

int main() {
  scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
  int rank_id = 1;
  for (int i = 1; i < n; ++i) {
    int x, y, z, w;
    scanf("%d%d%d%d", &x, &y, &z, &w);
    if (x + y + z + w > a + b + c + d) {
      ++rank_id;
    }
  }
  printf("%d\n", rank_id);
  return 0;
}
