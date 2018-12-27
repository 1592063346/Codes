#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m;
char a[N], b[N];

int main() {
  scanf("%d%d%s%s", &n, &m, a, b);
  if (n > m + 1) {
    return puts("NO"), 0;
  }
  int pos = -1;
  for (int i = 0; i < n; ++i) {
    if (a[i] == '*') {
      pos = i;
    }
  }
  bool same = true;
  if (~pos) {
    for (int i = 0; i < pos; ++i) {
      if (a[i] != b[i]) {
        same = false;
      }
    }
    for (int i = 1; n - i > pos; ++i) {
      if (a[n - i] != b[m - i]) {
        same = false;
      }
    }
  } else {
    if (n != m) {
      same = false;
    } else {
      for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
          same = false;
        }
      }
    }
  }
  puts(same ? "YES" : "NO");
  return 0;
}
