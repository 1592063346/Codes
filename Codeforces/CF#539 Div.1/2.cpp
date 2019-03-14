#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

char s[N], t[N];
int number[N];

int main() {
  scanf("%s", s + 1);
  int n = strlen(s + 1), p = 0;
  for (int i = 1; i <= n; ++i) {
    p = max(p, ++number[s[i]]);
  }
  if (p >= n - 1) {
    return puts("Impossible"), 0;
  } else {
    for (int i = 1; i < n; ++i) {
      int l = 0, r = n + 1;
      for (int j = i; j; --j) {
        t[--r] = s[j];
      }
      for (int j = i + 1; j <= n; ++j) {
        t[++l] = s[j];
      }
      bool pal = true, same = true;
      for (int j = 1; j <= n; ++j) {
        if (t[j] != t[n - j + 1]) {
          pal = false;
        }
        if (t[j] != s[j]) {
          same = false;
        }
      }
      if (!same && pal) {
        return puts("1"), 0;
      }
    }
    puts("2");
  }
  return 0;
}
