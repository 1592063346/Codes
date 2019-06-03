#include<bits/stdc++.h>

using namespace std;

const int N = 234567;

int n, a[N], b[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  int m = (n << 1) - 1;
  for (int i = 1; i <= m; ++i) {
    cin >> a[i];
  }
  auto check = [&] (int x) {
    for (int i = 1; i <= m; ++i) {
      b[i] = a[i] > x;
    }
    for (int i = 1; i < n; ++i) {
      if (b[n - i] == b[n - i + 1]) {
        return b[n - i];
      }
      if (b[n + i] == b[n + i - 1]) {
        return b[n + i];
      }
    }
    return b[n] ^ (n & 1) ^ 1;
  };
  int l = 1, r = m;
  while (l != r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  cout << l << '\n';
  return 0;
}
