#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10, M = 2e7 + 10;

int n, a[N], b[N], num[M], numt[M], ways[M];

long long binom2(int n) {
  return (long long) n * (n - 1) / 2;
}

long long binom4(int n) {
  return (long long) n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    b[i] = a[i];
    ++num[a[i]];
  }
  sort(a + 1, a + 1 + n);
  sort(b + 1, b + 1 + n);
  int m = unique(b + 1, b + 1 + n) - b - 1;
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    --num[a[i]];
    for (int j = 1; j < i - 1; ++j) {
      ++ways[a[i - 1] + a[j]];
    }
    for (int j = i + 1; j <= n; ++j) {
      answer += binom2(--num[a[j]]) * ways[a[j] - a[i]];
    }
    for (int j = i + 1; j <= n; ++j) {
      ++num[a[j]];
    }
  }
  memset(ways, 0, sizeof ways);
  for (int i = 1, j = 1; i <= m; ++i) {
    for (; j <= n && a[j] < b[i]; ++j) {
      for (int k = 1; k < j; ++k) {
        ++ways[a[j] + a[k]];
      }
    }
    for (int k = j; k <= n; ++k) {
      if (a[k] > b[i]) {
        ++num[a[k]];
      } else {
        ++numt[a[k]];
      }
    }
    for (int k = j; k <= n; ++k) {
      if (a[k] > b[i]) {
        answer += (long long) --num[a[k]] * numt[b[i]] * numt[a[k] - b[i]] * ways[a[k]];
        if (b[i] != a[k] - b[i]) {
          answer += num[a[k]] * binom2(numt[b[i]]) * binom2(numt[a[k] - b[i]]);
        } else {
          answer += num[a[k]] * binom4(numt[b[i]]);
        }
      }
    }
  }
  printf("%lld\n", answer);
  return 0;
}
