#include<bits/stdc++.h>
#include "aliens.h"

using namespace std;

const int N = 1234567;
const long long llinf = 1e18;

int maxh[N];
pair<long long, int> dp[N];

long long take_photos(int m, int n, int k, vector<int> r, vector<int> c) {
  for (int i = 1; i <= n; ++i) {
    maxh[i] = n - i;
  }
  for (int i = 0; i < m; ++i) {
    r[i] = n - 1 - r[i];
    if (r[i] + c[i] < n - 1) {
      int rr = r[i], cc = c[i];
      r[i] = n - 1 - cc;
      c[i] = n - 1 - rr;
    }
    ++r[i];
    ++c[i];
    maxh[c[i]] = max(maxh[c[i]], r[i]);
  }
  for (int i = n; i; --i) {
    maxh[i] = max(maxh[i], maxh[i + 1]);
  }
  vector<pair<int, int>> p(1, pair<int, int>(0, 1));
  for (int i = 1; i <= n; ++i) {
    if (maxh[i] != maxh[i + 1] && maxh[i] != n - i) {
      p.emplace_back(i, maxh[i] - n + i);
    }
  }
  auto squ = [&] (long long x) {
    return x * x;
  };
  auto slope = [&] (int i, int j) {
    long long xi = p[i + 1].second - p[i + 1].first, yi = dp[i].first + squ(p[i + 1].second - p[i + 1].first);
    long long xj = p[j + 1].second - p[j + 1].first, yj = dp[j].first + squ(p[j + 1].second - p[j + 1].first);
    return (double) (yj - yi) / (xj - xi);
  };
  auto solve = [&] (long long w) {
    dp[0] = pair<long long, int>(0, 0);
    vector<int> q(1, 0);
    for (int i = 1, j = 0, k; i < p.size(); ++i) {
      while (j + 1 < q.size() && slope(q[j], q[j + 1]) > -2 * p[i].first) {
        ++j;
      }
      int foo = p[q[j] + 1].second + p[i].first - p[q[j] + 1].first;
      dp[i].first = dp[q[j]].first + squ(foo) + w;
      dp[i].second = dp[q[j]].second + 1;
      if (i + 1 < p.size()) {
        if (p[i + 1].first - p[i + 1].second < p[i].first) {
          dp[i].first -= squ(p[i].first - p[i + 1].first + p[i + 1].second);
        }
        while ((k = q.size()) > 1 && slope(q[k - 1], q[k - 2]) < slope(i, q[k - 2])) {
          q.pop_back();
        }
        q.push_back(i);
      }
    }
    return dp[p.size() - 1];
  };
  long long ll = 0, rr = (long long) n * n;
  while (ll != rr) {
    long long mid = ll + rr >> 1;
    if (solve(mid).second > k) {
      ll = mid + 1;
    } else {
      rr = mid;
    }
  }
  pair<long long, int> answer = solve(rr);
  return answer.first - rr * k;
}
