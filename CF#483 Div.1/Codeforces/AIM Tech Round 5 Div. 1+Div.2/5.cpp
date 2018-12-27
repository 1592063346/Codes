#include<bits/stdc++.h>

using namespace std;

const int N = 140600;

int n, b[N], c[N];
long long a[N];

void print_0() {
  puts("YES");
  for (int i = 0; i < n; ++i) {
    printf("%d%c", 1, " \n"[i == n - 1]);
  }
}

int main() {
  auto go_last = [&] (int x) {
    return (x + n - 1) % n;
  };
  auto go_next = [&] (int x) {
    return (x + 1) % n;
  };

  scanf("%d", &n);
  int pos = 0, same = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
    if (i == 0) {
      same = b[i];
    } else {
      if (b[i] ^ same) {
        same = -1;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    if (b[i] >= b[pos] && b[go_last(i)] < b[i]) {
      pos = i;
    }
  }
  if (~same) {
    if (same) {
      return puts("NO"), 0;
    } else {
      return print_0(), 0;
    }
  }
  for (int i = n - 1, j = pos; ~i; --i) {
    c[i] = b[j];
    j = go_last(j);
  }
  a[n - 1] = c[n - 1];
  long long sumb = 0;
  for (int i = n - 2; ~i; --i) {
    sumb += c[i];
    a[i] = sumb + (c[n - 1] << 1);
  }
  puts("YES");
  for (int i = 0, j = n - 1 - pos; i < n; ++i) {
    printf("%I64d%c", a[j], " \n"[i == n - 1]);
    j = go_next(j);
  }
  return 0;
}
