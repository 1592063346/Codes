#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, a[N], b[N], ha[N], hb[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    if (i > 1) {
      ha[i - 1] = a[i] - a[i - 1];
    }
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &b[i]);
    if (i > 1) {
      hb[i - 1] = b[i] - b[i - 1];
    }
  }
  if (a[1] != b[1] || a[n] != b[n]) {
    return puts("No"), 0;
  }
  sort(ha + 1, ha + n);
  sort(hb + 1, hb + n);
  for (int i = 1; i < n; ++i) {
    if (ha[i] != hb[i]) {
      return puts("No"), 0;
    }
  }
  return puts("Yes"), 0;
}
