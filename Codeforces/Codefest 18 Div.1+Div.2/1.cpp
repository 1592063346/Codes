#include<bits/stdc++.h>

using namespace std;

int n;

int f(int n) {
  return !n ? 0 : f(n >> 1) + 1;
}

int main() {
  scanf("%d", &n);
  printf("%d\n", f(n));
  return 0;
}
