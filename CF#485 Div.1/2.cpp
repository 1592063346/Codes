#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, a[N], b[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    b[a[i]] = i;
  }
  int total = 0;
  for (int i = 1; i <= n; ++i) {
    if (a[i] != i) {
      int j = b[i];
      swap(b[a[i]], b[i]);
      swap(a[i], a[j]);
      ++total;
    }
  }
  if ((total & 1) == (3 * n & 1)) {
    puts("Petr");
  } else {
    puts("Um_nik");
  }
  return 0;
}
