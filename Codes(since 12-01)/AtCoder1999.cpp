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
  sort(a + 1, a + 1 + n, greater<int>());
  for (int i = 1; i <= n; ++i) {
    if (a[i] >= i && a[i + 1] < i + 1) {
      int u = !(a[i] - i & 1), j = i + 1;
      while (a[j] == i) {
        ++j;
      }
      --j;
      int r = !(j - i & 1);
      cout << ((u & r) ? "Second" : "First") << '\n';
      break;
    }
  }
  return 0;
}
