#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n;
pair<long long, long long> p[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld%lld", &p[i].first, &p[i].second);
  }
  sort(p + 1, p + 1 + n, [&] (const pair<long long, long long>& x, const pair<long long, long long>& y) {
    return x.first > y.first;
  });
  long long sum = 0, pre = 1e18, answer = 0;
  for (int i = 1; i <= n; ++i) {
    pre = min(pre, sum + p[i].first);
    sum += p[i].second;
    answer = max(answer, sum + p[i].first - pre);
  }
  printf("%lld\n", answer);
  return 0;
}
