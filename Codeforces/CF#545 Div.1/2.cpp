#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n, m, number[2], f[N];
char s[N], t[N];

int main() {
  scanf("%s%s", s, t);
  n = strlen(s);
  m = strlen(t);
  for (int i = 0; i < n; ++i) {
    ++number[s[i] - '0'];
  }
  f[0] = 0;
  for (int i = 1; i < m; ++i) {
    int j = f[i];
    for (; j && t[i] != t[j]; j = f[j]);
    f[i + 1] = t[i] == t[j] ? j + 1 : 0;
  }
  for (int i = 0, j = 0; i < n && number[0] && number[1]; ++i) {
    int c = t[j] - '0';
    printf("%d", c);
    --number[c];
    if (++j == m) {
      j = f[j];
    }
  }
  for (; number[0]; printf("0"), --number[0]);
  for (; number[1]; printf("1"), --number[1]);
  return puts(""), 0;
}
