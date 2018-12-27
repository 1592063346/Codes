#include<bits/stdc++.h>

using namespace std;

int n, k;

int main() {
  scanf("%d%d", &n, &k);
  printf("%d\n", (2 * n - 1) / k + 1 + (5 * n - 1) / k + 1 + (8 * n - 1) / k + 1);
  return 0;
}
