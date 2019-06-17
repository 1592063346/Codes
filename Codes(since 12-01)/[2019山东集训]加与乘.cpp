#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tt, n, op;
  cin >> tt;
  while (tt--) {
    cin >> n >> op;
    int x = 0;
    for (int i = 1, z, last = 0; i <= n; ++i) {
      cin >> z;
      z &= 1;
      if (z && !last) {
        ++x;
        last = 1;
      } else {
        last = 0;
      }
    }
    if (n == 1) {
      cout << (x ? 'B' : 'A') << '\n';
    } else if (!op) {
      if (!(n & 1)) {
        cout << 'A' << '\n';
      } else {
        cout << (x == (n + 1 >> 1) ? 'B' : 'A') << '\n';
      }
    } else {
      if (n & 1) {
        cout << 'A' << '\n';
      } else {
        cout << (x == (n >> 1) ? 'B' : 'A') << '\n';
      }
    }
  }
  return 0;
}
