#include<bits/stdc++.h>

using namespace std;

#define rg register

int n;

int main() {
  scanf("%d", &n);
  for (rg int i = 0; i < n; ++i) {
    printf("%d %d\n", i * 2 / 3, i * 2 % 3);
  }
  return 0;
}
