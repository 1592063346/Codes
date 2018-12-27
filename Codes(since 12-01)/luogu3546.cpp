#include<bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, f[N], l[N], r[N];
char s[N], t[N];

int main() {
  scanf("%d%s", &n, s);
  int newn = 0;
  for (int i = 0; i < n >> 1; ++i) {
    t[newn++] = s[i];
    t[newn++] = s[n - i - 1];
  }
  n = newn;
  for (int i = 0; i < n; ++i) {
    s[i << 1 | 1] = t[i];
  }
  for (int i = 0; i <= n << 1; i += 2) {
    s[i] = '$';
  }
  for (int i = 1, j = 0, k = 0; i < n << 1; ++i) {
    f[i] = k > i ? min(k - i, f[(j << 1) - i]) : 0;
    while (i - f[i] >= 0 && i + f[i] <= n << 1 && s[i - f[i]] == s[i + f[i]]) {
      ++f[i];
    }
    if (i + f[i] > k) {
      j = i;
      k = i + f[i];
    }
    if (!(i % 2)) {
      cmax(r[i - f[i] + 1], f[i] - 1);
      cmax(l[i + f[i] - 1], f[i] - 1);
    }
  }
  for (int i = 2; i <= n << 1; i += 2) {
    cmax(r[i], r[i - 2] - 2);
  }
  for (int i = (n << 1) - 2; i >= 0; i -= 2) {
    cmax(l[i], l[i + 2] - 2);
  }
  int answer = 0;
  for (int i = 0; i <= n << 1; i += 2) {
    if (i - (l[i] << 1) == 0) {
      cmax(answer, l[i] + r[i]);
    }
  }
  printf("%d\n", answer >> 1);
  return 0;
}
