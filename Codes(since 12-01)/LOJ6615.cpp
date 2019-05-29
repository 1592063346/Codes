#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  while (cin >> n) {
    int binom2 = (long long) n * (n - 1) / 2;
    int binom4 = (long long) n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4;
    cout << (binom2 + binom4 + 1) << '\n';
  }
  return 0;
}
