#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, l;
long long a[N];
set<pair<int, int>> interval;

int main() {
  scanf("%d%d%d", &n, &m, &l);
  for (int i = 1; i <= n; ++i) {
    scanf("%I64d", &a[i]);
    if (a[i] > l) {
      int left = i;
      if (interval.size() && (*interval.rbegin()).second == i - 1) {
        left = (*interval.rbegin()).first;
        interval.erase(--interval.end());
      }
      interval.insert(make_pair(left, i));
    }
  }
  for (int i = 1; i <= m; ++i) {
    int type, p, d;
    scanf("%d", &type);
    if (type == 0) {
      printf("%d\n", interval.size());
    } else {
      scanf("%d%d", &p, &d);
      a[p] += d;
      if (a[p] - d <= l && a[p] > l) {
        int left = p, right = p;
        if (interval.size()) {
          set<pair<int, int>>:: iterator it = interval.lower_bound(make_pair(p, p));
          if (it != interval.begin()) {
            --it;
            if ((*it).second == p - 1) {
              left = (*it).first;
              interval.erase(it);
            }
          }
          it = interval.upper_bound(make_pair(p, p));
          if (it != interval.end()) {
            if ((*it).first == p + 1) {
              right = (*it).second;
              interval.erase(it);
            }
          }
        }
        interval.insert(make_pair(left, right));
      }
    }
  }
  return 0;
}
