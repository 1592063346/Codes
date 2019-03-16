#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 1e8 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  long long sum = 0, y = 0;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    sum += x;
    y ^= x;
  }
  cout << (sum + y) % mod << "\n";
  return 0;
}
