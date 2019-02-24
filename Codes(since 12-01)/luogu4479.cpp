#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, t, number[N];
long long k, h[N];
pair<int, int> p[N];

void modify(int p, int v) {
  for (; p <= t; p += p & -p) {
    number[p] += v;
  }
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    result += number[p];
  }
  return result;
}

long long solve(int x) {
  t = 0;
  for (int i = 1; i <= n; ++i) {
    h[++t] = p[i].second - (long long) x * p[i].first;
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  memset(number, 0, sizeof number);
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    int y = lower_bound(h + 1, h + 1 + t, p[i].second - (long long) x * p[i].first) - h;
    answer += query(y);
    modify(y, 1);
  }
  return answer;
}

int main() {
  scanf("%d%lld", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &p[i].first, &p[i].second);
  }
  sort(p + 1, p + 1 + n, [&] (const pair<int, int>& a, const pair<int, int>& b) {
    return a.first == b.first ? a.second > b.second : a.first < b.first;
  });
  int l = -2e8, r = 2e8;
  while (l != r) {
    int mid = (l + r >> 1) + 1;
    if (solve(mid) >= k) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  printf("%d\n", l);
  return 0;
}
