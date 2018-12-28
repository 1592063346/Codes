#include<bits/stdc++.h>

using namespace std;

int l1, r1, t1, l2, r2, t2;

int solve() {
  int g = __gcd(t1, t2), diff;
  if (l1 - l2 <= 0) {
    diff = l2 - l1 - (l2 - l1) / g * g;
  } else {
    diff = ((l1 - l2 - 1) / g + 1) * g - l1 + l2;
  }
  int result = 0;
  if (diff <= r1 - l1 + 1) {
    result = min(r1 - l1 + 1 - diff, r2 - l2 + 1);
  }
  return result;
}

int main() {
  scanf("%d%d%d%d%d%d", &l1, &r1, &t1, &l2, &r2, &t2);
  int answer = solve();
  swap(l1, l2);
  swap(r1, r2);
  swap(t1, t2);
  answer = max(answer, solve());
  printf("%d\n", answer);
  return 0;
}
