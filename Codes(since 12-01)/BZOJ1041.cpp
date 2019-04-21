#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long r, n, result = 1;
  cin >> r;
  n = r * r;
  for (long long i = 2; i * i <= r; ++i) {
    if (n % i == 0) {
      int t = 0;
      while (n % i == 0) {
        n /= i;
        ++t;
      }
      if (i % 4 == 1) {
        result *= t + 1;
      }
    }
  }
  n = sqrt(n);
  if (n != 1 && n % 4 == 1) {
    result *= 3;
  }
  cout << (result << 2) << '\n';
  return 0;
}
