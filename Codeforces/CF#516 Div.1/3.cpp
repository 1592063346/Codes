#include<bits/stdc++.h>

using namespace std;

#define rg register

int n;
char standard, cmd[10];

int main() {
  scanf("%d", &n);
  int l = -1e9, r = 1e9;
  for (rg int i = 1; i <= n; ++i) {
    int mid = l + r >> 1;
    printf("%d %d\n", mid, 1);
    fflush(stdout);
    scanf("%s", cmd);
    if (i == 1) {
      standard = *cmd;
    }
    if (*cmd == standard) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  printf("%d %d %d %d\n", l - 1, 0, r, 2);
  return 0;
}
