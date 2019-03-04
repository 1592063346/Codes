#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, number[N][3], carried[3];

int main() {
  scanf("%d", &n);
  long long answer = 0;
  for (int i = 1; i <= n << 1; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x < 1) {
      answer += 1 - x;
      x = 1;
    } else if (x > n) {
      answer += x - n;
      x = n;
    }
    if (y < 1) {
      answer += 1 - y;
      y = 1;
    } else if (y > 2) {
      answer += y - 2;
      y = 2;
    }
    ++number[x][y];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= 2; ++j) {
      carried[j] += number[i][j] - 1;
    }
    if (carried[1] > 0 && carried[2] < 0) {
      int t = min(abs(carried[1]), abs(carried[2]));
      answer += t;
      carried[1] -= t;
      carried[2] += t;
    }
    if (carried[1] < 0 && carried[2] > 0) {
      int t = min(abs(carried[1]), abs(carried[2]));
      answer += t;
      carried[1] += t;
      carried[2] -= t;
    }
    for (int j = 1; j <= 2; ++j) {
      answer += abs(carried[j]);
    }
  }
  printf("%lld\n", answer);
  return 0;
}
