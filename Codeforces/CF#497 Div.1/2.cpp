#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int t, f[N];

bool check(int a, int b, int c) {
  return ((a & 1) && (b & 2) && (c & 4)) ||
         ((a & 1) && (b & 4) && (c & 2)) ||
         ((a & 2) && (b & 1) && (c & 4)) ||
         ((a & 2) && (b & 4) && (c & 1)) ||
         ((a & 4) && (b & 1) && (c & 2)) ||
         ((a & 4) && (b & 2) && (c & 1));
}

int binom(int n, int m) {
  switch (m) {
    case 0: return 1;
    case 1: return n;
    case 2: return n * (n - 1) / 2;
    case 3: return n * (n - 1) * (n - 2) / 6;
  }
}

int main() {
  for (int i = 1; i <= 1e5; ++i) {
    for (int j = i; j <= 1e5; j += i) {
      ++f[j];
    }
  }
  scanf("%d", &t);
  for (int kase = 1; kase <= t; ++kase) {
    int a, b, c, s[8], total[8];
    scanf("%d%d%d", &a, &b, &c);
    s[7] = f[__gcd(a, __gcd(b, c))];
    s[6] = f[__gcd(a, b)] - s[7];
    s[5] = f[__gcd(a, c)] - s[7];
    s[3] = f[__gcd(b, c)] - s[7];
    s[4] = f[a] - s[6] - s[5] - s[7];
    s[2] = f[b] - s[6] - s[3] - s[7];
    s[1] = f[c] - s[5] - s[3] - s[7];
    int answer = 0;
    for (int i = 1; i < 8; ++i) {
      for (int j = i; j < 8; ++j) {
        for (int k = j; k < 8; ++k) {
          if (check(i, j, k)) {
            memset(total, 0, sizeof total);
            ++total[i];
            ++total[j];
            ++total[k];
            int result = 1;
            for (int l = 1; l < 8; ++l) {
              result *= binom(total[l] + s[l] - 1, total[l]);
            }
            answer += result;
          }
        }
      }
    }
    printf("%d\n", answer);
  }
  return 0;
}
