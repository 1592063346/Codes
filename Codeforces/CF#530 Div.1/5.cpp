#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, a[N], h[20][N], logv[N];
long long number[N];

void rmq_init() {
  for (int i = 2; i <= n; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= n; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
      h[i][j] = __gcd(h[i - 1][j], h[i - 1][j + (1 << i - 1)]);
    }
  }
}

int get_gcd(int l, int r) {
  int k = logv[r - l + 1];
  return __gcd(h[k][l], h[k][r - (1 << k) + 1]);
}

long long s(long long n) {
  return n * (n + 1) >> 1;
}

long long f(long long a, long long b, long long c, int n) {
  if (n < 0) {
    return 0;
  } else if (!a) {
    return (b / c) * (n + 1);
  } else if (a >= c || b >= c) {
    return (a / c) * n * (n + 1) / 2 + (b / c) * (n + 1) + f(a % c, b % c, c, n);
  } else {
    return (a * n + b) / c * n - f(c, c - b - 1, a, (a * n + b) / c - 1);
  }
}

long long g(long long a, long long b, long long c, int n) {
  return f(-a, a * n + b, c, n);
}

long long solve(long long x) {
  long long result = 0, sum = 0, sum2 = 0;
  for (int i = 1; i <= m; ++i) {
    int y = min(number[i], x / i);
    result += (2 * number[i] - y + 1) * y >> 1;
  }
  for (int i = 2, j = 1; i <= m; sum += number[i] * i, sum2 += number[i], ++i) {
    if (number[i]) {
      for (; sum > x; ++j, sum -= number[j] * j, sum2 -= number[j]);
      while (1) {
        if (number[j]) {
          int p = min(number[i], (x - sum) / i);
          long long y = g(-i, x - sum, j, p) - (x - sum) / j;
          if ((x - sum) / j > number[j]) {
            p = min(number[i], (x - sum - j * number[j]) / i);
            y -= g(-i, x - sum - j * number[j], j, p) - (x - sum - j * number[j]) / j;
          }
          result += y;
        }
        if (j + 1 < i && sum + number[i] * i >= x) {
          ++j;
          sum -= number[j] * j;
          sum2 -= number[j];
        } else {
          break;
        }
      }
      result += sum2 * number[i];
    }
  }
  return result;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    m = max(m, a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    h[0][i] = a[i];
  }
  rmq_init();
  for (int i = 1; i <= n; ++i) {
    for (int x = a[i], j = i, l, r; j <= n; j = r + 1, x = get_gcd(i, j)) {
      l = j, r = n;
      while (l != r) {
        int mid = (l + r >> 1) + 1;
        if (get_gcd(i, mid) == x) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }
      number[x] += r - j + 1;
    }
  }
  long long l = 1, r = s(n) * m, all = s(s(n));
  while (l != r) {
    long long mid = l + r >> 1;
    if (solve(mid) * 2 >= all) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  printf("%lld\n", l);
  return 0;
}
