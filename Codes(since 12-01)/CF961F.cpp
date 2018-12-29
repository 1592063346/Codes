#include<bits/stdc++.h>

using namespace std;

const int N = 4e6 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, m, f[N], tag[N];
char s[N], t[N];

int main() {
  scanf("%d%s", &n, s);
  memset(tag, -1, sizeof tag);
  for (int i = 0; i < n; ++i) {
    t[m++] = s[i];
    t[m++] = s[n - i - 1];
  }
  for (int i = 0; i < m; ++i) {
    s[i << 1 | 1] = t[i];
  }
  for (int i = 0; i <= m << 1; i += 2) {
    s[i] = '$';
  }
  for (int i = 1, j = 0, k = 0; i < m; ++i) {
    f[i] = k > i ? min(k - i, f[2 * j - i]) : 0;
    while (i - f[i] >= 0 && i + f[i] <= (m << 1) && s[i + f[i]] == s[i - f[i]]) {
      ++f[i];
    }
    if (i + f[i] > k) {
      j = i;
      k = i + f[i];
    }
    if (i % 4 == 2) {
      if ((f[i] - 1 >> 1) & 1) {
        cmax(tag[i - f[i] + 2], f[i] - 1 >> 1);
      } else {
        cmax(tag[i - f[i] + 4], (f[i] - 1 >> 1) - 1);
      }
    }
  }
  int answer = -1;
  for (int i = 1, j = 0; i < m; i += 4, j += 2) {
    cmax(answer, tag[i] + j);
    printf("%d%c", answer - j, " \n"[i + 4 > (m << 1)]);
  }
  return 0;
}
