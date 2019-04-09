#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i];
    for (int j = 0; j < i; ++j) {
      if (a[i] + b[i] == a[j] && a[j] + b[j] == a[i]) {
        cout << "YE5\n";
        exit(0);
      }
    }
  }
  cout << "N0\n";
  return 0;
}
