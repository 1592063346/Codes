#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, c[N], k = 1e5;
char a[N], b[N];

void solve(int p, int coef) {
  if (a[p - 1] + coef < '0' || a[p - 1] + coef > '9') {
    solve(p - 1, -coef);
  }
  a[p - 1] += coef;
  a[p] += coef;
  printf("%d %d\n", p - 1, coef);
  if (!--k) {
    exit(0);
  }
}

int main() {
  scanf("%d%s%s", &n, a + 1, b + 1);
  copy(a + 1, a + 1 + n, c + 1);
  long long answer = 0;
  for (int i = 1; i < n; ++i) {
    if (c[i] != b[i]) {
      answer += abs(c[i] - (int) b[i]);
      c[i + 1] += (int) b[i] - c[i];
    }
  }
  if (c[n] != b[n]) {
    return puts("-1");
  } else {
    printf("%lld\n", answer);
    if (answer < k) {
      k = answer;
    }
    for (int i = n; i; --i) {
      for (; a[i] != b[i]; solve(i, a[i] < b[i] ? 1 : -1));
    }
  }
  return 0;
}
