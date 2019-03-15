#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

void cmin(long long& x, long long y) {
  if (x > y) {
    x = y;
  }
}

int n, c, d, t[N];
char opt[N][2];

int main() {
  scanf("%d%d%d", &n, &c, &d);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%s", &t[i], opt[i]);
  }
  ++n;
  scanf("%d", &t[n]);
  long long answer = (long long) (n - 1) * d, s = 0;
  for (int i = n - 1, j = n; i >= 1; --i) {
    if (*opt[i - 1] != *opt[i]) {
      s += (long long) (t[j] - t[i]) * c;
      j = i;
    } else {
      s += min((long long) (t[j] - t[i]) * c, (long long) d);
    }
    cmin(answer, (long long) (i - 1) * d + s);
  }
  printf("%lld\n", answer);
  return 0;
}
