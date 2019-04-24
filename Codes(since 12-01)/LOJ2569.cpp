#include<bits/stdc++.h>

using namespace std;

long long min_value, max_value;

void MinMax(long long l, long long r, long long& x, long long& y) {
  printf("? %lld %lld\n", l, r);
  fflush(stdout);
  scanf("%lld%lld", &x, &y);
}

void find(long long l, long long r) {
  MinMax(l, r, min_value, max_value);
}

long long findGap(int T, int n) {
  long long answer = 0;
  find(0, 1e18);
  if (T == 1) {
    long long l = min_value, r = max_value;
    for (int i = 0; i < (n - 1 >> 1); ++i) {
      find(l + 1, r - 1);
      answer = max(answer, min_value - l);
      answer = max(answer, r - max_value);
      l = min_value;
      r = max_value;
    }
    if (!(n & 1)) {
      answer = max(answer, r - l);
    }
  } else {
    long long l = min_value, r = max_value, diff = (r - l) / (n - 1);
    for (long long ll = l, rr, pre = -1; ll <= r; ll += diff + 1) {
      rr = min(r, ll + diff);
      find(ll, rr);
      if (~max_value) {
        answer = max(answer, max_value - min_value);
        if (~pre) {
          answer = max(answer, min_value - pre);
        }
        pre = max_value;
      }
    }
  }
  return answer;
}

int main() {
  int T, n;
  scanf("%d%d", &T, &n);
  printf("! %lld\n", findGap(T, n));
  return 0;
}
