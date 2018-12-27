#include<bits/stdc++.h>

using namespace std;

const int N = 1e2 + 10;

int n, num8;
char s[N];

inline void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int main() {
  scanf("%d%s", &n, s);
  for (int i = 0; i < n; ++i) {
    if (s[i] == '8') {
      ++num8;
    }
  }
  if (num8) {
    int ans = 0;
    for (int i = 1; i <= num8; ++i) {
      cmax(ans, min(i, (n - i) / 10));
    }
    printf("%d\n", ans);
  } else {
    printf("0\n");
  }
  return 0;
}
