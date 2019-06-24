#include<bits/stdc++.h>

using namespace std;

const int N = 567890;

int n, q, top, a[N], sta[N];
long long s[N], answer[N];
vector<pair<int, int>> queries[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    s[i] = s[i - 1] + a[i];
  }
  cin >> q;
  for (int i = 1, x, y; i <= q; ++i) {
    cin >> x >> y;
    queries[y].emplace_back(x, i);
  }
  for (int i = 1; i <= n; ++i) {
    auto funx = [&] (int x) {
      return (long long) a[x];
    };
    auto funy = [&] (int x) {
      return -s[x] + (long long) x * a[x];
    };
    auto slope = [&] (int x, int y) {
      return (double) (funy(x) - funy(y)) / (funx(x) - funx(y));
    };
    auto solve = [&] (int target, int k) {
      int l = 1, r = top;
      while (l != r) {
        int mid = l + r >> 1;
        if (sta[mid] >= target) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      r = top;
      while (l != r) {
        int mid = l + r >> 1;
        if (slope(sta[mid], sta[mid + 1]) < k) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      return funy(sta[l]) - funx(sta[l]) * k;
    };
    while ((top && a[i] <= a[sta[top]]) || (top > 1 && slope(sta[top - 1], sta[top]) >= slope(sta[top], i))) {
      --top;
    }
    sta[++top] = i;
    for (auto query : queries[i]) {
      answer[query.second] = solve(i - query.first + 1, i - query.first) + s[i];
    }
  }
  for (int i = 1; i <= q; ++i) {
    cout << answer[i] << '\n';
  }
  return 0;
}
