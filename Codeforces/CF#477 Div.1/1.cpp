#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, cl, ce, v, q, l[N], e[N];

int solve(int s, int t, int high, int n, int* pos, int v) {
  int p1 = upper_bound(pos + 1, pos + 1 + n, s) - pos - 1;
  int p2 = lower_bound(pos + 1, pos + 1 + n, s) - pos;
  int p3 = upper_bound(pos + 1, pos + 1 + n, t) - pos;
  int answer = 0x3f3f3f3f;
  if (p1 >= 1 && p1 <= n) {
    answer = min(answer, abs(s - pos[p1]) + abs(t - pos[p1]) + (high - 1) / v + 1);
  }
  if (p2 >= 1 && p2 <= n) {
    answer = min(answer, abs(s - pos[p2]) + abs(t - pos[p2]) + (high - 1) / v + 1);
  }
  if (p3 >= 1 && p3 <= n) {
    answer = min(answer, abs(s - pos[p3]) + abs(t - pos[p3]) + (high - 1) / v + 1);
  }
  return answer;
}

int main() {
  scanf("%d%d%d%d%d", &n, &m, &cl, &ce, &v);
  for (int i = 1; i <= cl; ++i) {
    scanf("%d", &l[i]);
  }
  for (int i = 1; i <= ce; ++i) {
    scanf("%d", &e[i]);
  }
  scanf("%d", &q);
  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    if (x1 > x2) {
      swap(x1, x2);
    }
    if (y1 > y2) {
      swap(y1, y2);
    }
    if (x1 == x2) {
      printf("%d\n", abs(y1 - y2));
    } else {
      printf("%d\n", min(solve(y1, y2, x2 - x1, cl, l, 1), solve(y1, y2, x2 - x1, ce, e, v)));
    }
  }
  return 0;
}
