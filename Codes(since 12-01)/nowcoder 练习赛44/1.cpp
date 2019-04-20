#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m, p;
  cin >> n >> m;
  vector<int> a(n), l(m + 1, n), r(m + 1, 0);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    if (a[i] == m) {
      p = i;
    }
    l[a[i]] = min(l[a[i]], i);
    r[a[i]] = max(r[a[i]], i);
  }
  for (int i = 1; i <= m; ++i) {
    if (l[i] > r[i]) {
      l[i] = r[i] = p;
    }
    cout << l[i] + 1 << ' ' << r[i] + 1 << '\n';
  }
  return 0;
}
