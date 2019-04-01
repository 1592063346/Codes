#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, a[N], tt;
long long f[N], s[N];
pair<long long, long long> sta[N];

double slope(pair<long long, long long> a, pair<long long, long long> b) {
  return (double) (b.second - a.second) / (b.first - a.first);
}

pair<long long, long long> solve(long long k) {
  int l = 1, r = tt;
  while (l != r) {
    int mid = l + r >> 1;
    if (slope(sta[mid], sta[mid + 1]) <= k) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return sta[l];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    s[i] = s[i - 1] + a[i];
    f[i] = f[i - 1] + (long long) a[i] * i;
  }
  sta[++tt] = {0, 0};
  long long answer = -1e18;
  for (int i = 1; i <= n; ++i) {
    pair<long long, long long> result = solve(s[i]);
    answer = max(answer, -s[i] * result.first + result.second + f[i]);
    pair<long long, long long> now = {i, -f[i] + i * s[i]};
    for (; tt > 1 && slope(sta[tt - 1], sta[tt]) <= slope(sta[tt], now); --tt);
    sta[++tt] = now;
  }
  printf("%lld\n", answer);
  return 0;
}
