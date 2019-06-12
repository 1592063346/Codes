#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  cout << (n * (n - 1) >> 1) - (n >> 1) << '\n';
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      if (i + j != (n | 1)) {
        cout << i << ' ' << j << '\n';
      }
    }
  }
  return 0;
}
