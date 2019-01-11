#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n;
long long w[N], h[N], c[N], a[N], b[N], gcd[N];
vector<long long> num[N], tmp[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld%lld%lld", &w[i], &h[i], &c[i]);
    a[i] = w[i];
    b[i] = h[i];
  }
  sort(a + 1, a + 1 + n);
  sort(b + 1, b + 1 + n);
  int m1 = unique(a + 1, a + 1 + n) - a - 1;
  int m2 = unique(b + 1, b + 1 + n) - b - 1;
  if ((long long) m1 * m2 != n) {
    return puts("0"), 0;
  }
  for (int i = 1; i <= m1; ++i) {
    num[i].resize(m2 + 1);
  }
  for (int i = 1; i <= n; ++i) {
    int id = lower_bound(a + 1, a + 1 + m1, w[i]) - a;
    num[id][lower_bound(b + 1, b + 1 + m2, h[i]) - b] = c[i];
  }
  for (int i = 1; i <= m1; ++i) {
    tmp[i] = num[i];
    gcd[i] = tmp[i][1];
    for (int j = 1; j <= m2; ++j) {
      gcd[i] = __gcd(gcd[i], tmp[i][j]);
    }
    for (int j = 1; j <= m2; ++j) {
      tmp[i][j] /= gcd[i];
    }
  }
  for (int i = 2; i <= m1; ++i) {
    for (int j = 1; j <= m2; ++j) {
      if (tmp[i][j] != tmp[i - 1][j]) {
        return puts("0"), 0;
      }
    }
  }
  long long final = gcd[1];
  for (int i = 2; i <= m1; ++i) {
    final = __gcd(final, gcd[i]);
  }
  int answer = 0;
  for (long long i = 1; i * i <= final; ++i) {
    if (final % i == 0) {
      ++answer;
      if (i * i != final) {
        ++answer;
      }
    }
  }
  printf("%d\n", answer);
  return 0;
}
