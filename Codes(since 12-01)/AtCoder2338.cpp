#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, a[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  sort(a + 1, a + 1 + n);
  int l = 1, r = n + 1;
  auto check = [&] (int x) {
    long long value = a[x];
    for (int i = 1; i <= n; ++i) {
      if (i != x) {
        if (a[i] > value * 2) {
          return false;
        }
        value += a[i];
      }
    }
    return true;
  };
  while (l != r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << n - l + 1 << '\n';
  return 0;
}
