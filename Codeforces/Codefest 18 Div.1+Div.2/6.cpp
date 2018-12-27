#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int n, k, a[N], q[N], top, l[N], r[N];

int f(int len) {
  int div_begin = max(len - k, 0);
  int div_end = div_begin - div_begin / k * k;
  return ((long long) (div_begin + div_end) * (div_begin / k + 1) >> 1) % mod;
}

int main() {
  scanf("%d%d", &n, &k);
  --k;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  q[top = 0] = 0;
  for (int i = 1; i <= n; ++i) {
    for (; top && a[i] >= a[q[top]]; --top);
    l[i] = q[top];
    q[++top] = i;
  }
  q[top = 0] = n + 1;
  for (int i = n; i; --i) {
    for (; top && a[i] > a[q[top]]; --top);
    r[i] = q[top];
    q[++top] = i;
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    add(ans, (((long long) f(r[i] - l[i] - 1) - f(i - l[i] - 1) - f(r[i] - i - 1)) % mod + mod) * a[i] % mod);
  }
  printf("%d\n", ans);
  return 0;
}
