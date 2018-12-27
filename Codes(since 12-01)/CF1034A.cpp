// fuck!!!
#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, a[N], num[15000010], p[15000010];
vector<int> primes;

void sieve() {
  fill(p + 1, p + 15000001, 1);
  for (int i = 2; i <= 15000000; ++i) {
    if (p[i]) {
      primes.push_back(i);
    }
    for (auto v : primes) {
      int d = i * v;
      if (d > 15000000) {
        break;
      }
      p[d] = 0;
      if (i % v == 0) {
        break;
      }
    }
  }
}

int main() {
  sieve();
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    ++num[a[i]];
  }
  int ans = n;
  for (auto v : primes) {
    int result = 0;
    for (int i = v; i <= 15000000; i += v) {
      result += num[i];
    }
    if (result ^ n) {
      cmin(ans, n - result);
    }
  }
  sort(a + 1, a + 1 + n);
  memset(p, 0, sizeof p);
  for (int i = 1; i <= n; ++i) {
    if (a[i] ^ 1 && a[i] ^ a[i - 1] && p[a[i]] <= 1) {
      int result = 0;
      for (int j = a[i]; j <= 15000000; j += a[i]) {
        ++p[j];
        result += num[j];
      }
      if (result ^ n) {
        cmin(ans, n - result);
      }
    }
  }
  printf("%d\n", ans == n ? -1 : ans);
  return 0;
}
