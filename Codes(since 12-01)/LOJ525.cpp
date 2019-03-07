#include<bits/stdc++.h>

using namespace std;

const int N = 6e4 + 10;

int p;

int phi(int x) {
  int result = x;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      result = result / i * (i - 1);
      for (; x % i == 0; x /= i);
    }
  }
  if (x > 1) {
    result = result / x * (x - 1);
  }
  return result;
}

int main() {
  scanf("%d", &p);
  if (p == 1) {
    return puts("-1"), 0;
  }
  int phi_p = phi(p);
  printf("%d\n", 2 * phi_p + 1);
  for (int i = 0; i <= 2 * phi_p + 1; ++i) {
    printf("%d%c", i == phi_p + 1 ? p - 1 : i == 2 * phi_p + 1 ? 1 : 0, " \n"[i == 2 * phi_p + 1]);
  }
  return 0;
}
