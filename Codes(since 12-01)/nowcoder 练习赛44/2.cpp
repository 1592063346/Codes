#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  unsigned int sa, sb, sc;
  int n, mod;
  cin >> n >> mod >> sa >> sb >> sc;
  auto rng = [&] () {
    sa ^= sa << 16;
    sa ^= sa >> 5;
    sa ^= sa << 1;
    unsigned int t = sa;
    sa = sb;
    sb = sc;
    sc ^= t ^ sa;
    return sc;
  };
  vector<int> a(n), b(n), c(n, n - 1);
  for (int i = 0; i < n; ++i) {
    a[i] = rng() % mod + 1;
  }
  long long answer = (long long) n * (n - 1) >> 1;
  for (int i = n - 2, j = n - 1; ~i; --i) {
    j = min(j, c[i]);
    if (a[j] - j + i < 0) {
      b[i] = 1 + b[j - 1];
    }
    if (i - a[i] - 1 > -1) {
      c[i - a[i] - 1] = min(c[i - a[i] - 1], i);
    }
    answer += b[i];
  }
  cout << answer << '\n';
  return 0;
}
