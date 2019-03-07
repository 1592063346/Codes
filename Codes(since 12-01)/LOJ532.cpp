#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int a, b, c, x0, pre[N], A[N], B[N];
long double coef[N];
long long l1, r1, l2, r2;

int main() {
  scanf("%d%d%d%d%lld%lld%lld%lld", &a, &b, &c, &x0, &l1, &r1, &l2, &r2);
  int first_p, length;
  x0 = ((long long) a * x0 + b) % c + 1;
  for (int i = 1, x = x0;; ++i, x = ((long long) a * x + b) % c + 1) {
    if (pre[x]) {
      first_p = pre[x];
      length = i - pre[x];
      break;
    }
    pre[x] = i;
  }
  for (int i = 1; i <= c; ++i) {
    if (pre[i] >= first_p) {
      A[i] = ((r1 >= pre[i] ? (r1 - pre[i]) / length + 1 : 0) - (l1 - 1 >= pre[i] ? (l1 - 1 - pre[i]) / length + 1 : 0)) % mod;
      B[i] = ((r2 >= pre[i] ? (r2 - pre[i]) / length + 1 : 0) - (l2 - 1 >= pre[i] ? (l2 - 1 - pre[i]) / length + 1 : 0)) % mod;
    } else {
      A[i] = (r1 >= pre[i] && pre[i] >= l1);
      B[i] = (r2 >= pre[i] && pre[i] >= l2);
    }
    add(A[i], A[i - 1]);
    add(B[i], B[i - 1]);
  }
  for (int i = 2; i <= c + 1; ++i) {
    coef[i] = (i + sqrt((long double) i * i - 4)) / 2;
  }
  int answer = 0;
  for (int i = 1; i <= c; ++i) {
    int sa = (A[i] - A[i - 1] + mod) % mod, sb = (B[i] - B[i - 1] + mod) % mod;
    add(answer, (mul(sa, sb) << 1) % mod);
    if (!sa && !sb) {
      continue;
    }
    for (int l = i + 1, r, k; l <= c; l = r + 1) {
      k = ((long long) i * i + (long long) l * l - 1) / ((long long) i * l) + 1;
      r = min(c, (int) floor(i * coef[k]));
      add(answer, mul((mul(sa, (B[r] - B[l - 1] + mod) % mod) + mul(sb, (A[r] - A[l - 1] + mod) % mod)) % mod, k));
    }
  }
  printf("%d\n", answer);
  return 0;
}
