#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m, k, logv[N];
long long d[N], min_l[20][N], min_r[20][N];
pair<int, int> plan[N];

void build_rmq(int n) {
  for (int i = 1; 1 << i <= n; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
      min_l[i][j] = min(min_l[i - 1][j], min_l[i - 1][j + (1 << i - 1)]);
      min_r[i][j] = min(min_r[i - 1][j], min_r[i - 1][j + (1 << i - 1)]);
    }
  }
}

long long query_min_l(int l, int r) {
  int g = logv[r - l + 1];
  return min(min_l[g][l], min_l[g][r - (1 << g) + 1]);
}

long long query_min_r(int l, int r) {
  int g = logv[r - l + 1];
  return min(min_r[g][l], min_r[g][r - (1 << g) + 1]);
}

bool check(int p, int len, long long v, int diff_l, int diff_r) {
  int ql, qr;
  ql = lower_bound(plan + 1, plan + 1 + k, pair<int, int>(p - len + diff_l, 0)) - plan;
  qr = lower_bound(plan + 1, plan + 1 + k, pair<int, int>(p + 1, 0)) - plan - 1;
  if (ql <= qr && d[p] + query_min_l(ql, qr) <= v) {
    return false;
  }
  ql = lower_bound(plan + 1, plan + 1 + k, pair<int, int>(p - len, 0)) - plan;
  if (ql <= qr && d[p] + query_min_l(ql, qr) < v) {
    return false;
  }
  ql = lower_bound(plan + 1, plan + 1 + k, pair<int, int>(p, 0)) - plan;
  qr = lower_bound(plan + 1, plan + 1 + k, pair<int, int>(p + len - diff_r + 1, 0)) - plan - 1;
  if (ql <= qr && query_min_r(ql, qr) - d[p] <= v) {
    return false;
  }
  qr = lower_bound(plan + 1, plan + 1 + k, pair<int, int>(p + len + 1, 0)) - plan - 1;
  if (ql <= qr && query_min_r(ql, qr) - d[p] < v) {
    return false;
  }
  return true;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 2; i <= n; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int i = 2; i <= n; ++i) {
    scanf("%lld", &d[i]);
    d[i] += d[i - 1];
  }
  while (m--) {
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i) {
      scanf("%d%d", &plan[i].first, &plan[i].second);
    }
    sort(plan + 1, plan + 1 + k);
    for (int i = 1; i <= k; ++i) {
      min_l[0][i] = plan[i].second - d[plan[i].first];
      min_r[0][i] = plan[i].second + d[plan[i].first];
    }
    build_rmq(k);
    long long answer = 0;
    for (int i = 1; i <= k; ++i) {
      int l, r, ql, qr;
      l = 1;
      r = plan[i].first;
      while (l != r) {
        int mid = l + r >> 1;
        if (check(mid, plan[i].first - mid, plan[i].second + d[plan[i].first] - d[mid], 1, 1)) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      ql = l;
      l = plan[i].first;
      r = n;
      while (l != r) {
        int mid = (l + r >> 1) + 1;
        if (check(mid, mid - plan[i].first, plan[i].second + d[mid] - d[plan[i].first], 1, 0)) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }
      qr = l;
      answer += qr - ql + 1;
    }
    printf("%lld\n", answer);
  }
  return 0;
}
