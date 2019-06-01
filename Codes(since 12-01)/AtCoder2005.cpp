#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, q, t;
long long events[N], answer[N], coef[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  events[++t] = n;
  for (int i = 1; i <= q; ++i) {
    long long x;
    cin >> x;
    while (t && events[t] >= x) {
      --t;
    }
    events[++t] = x;
  }
  coef[t] = 1;
  function<void (long long, long long)> solve = [&] (long long x, long long y) {
    if (x) {
      int p = lower_bound(events + 1, events + 1 + t, x) - events - 1;
      if (!p) {
        answer[1] += y;
        answer[x + 1] -= y;
      } else {
        coef[p] += y * (x / events[p]);
        solve(x % events[p], y);
      }
    }
  };
  for (int i = t; i > 1; --i) {
    coef[i - 1] += coef[i] * (events[i] / events[i - 1]);
    solve(events[i] % events[i - 1], coef[i]);
  }
  answer[1] += coef[1];
  answer[events[1] + 1] -= coef[1];
  for (int i = 1; i <= n; ++i) {
    answer[i] += answer[i - 1];
    cout << answer[i] << '\n';
  }
  return 0;
}
