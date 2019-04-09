#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m, l, r, x = 10;
    cin >> m >> n >> l >> r;
    --l;
    --r;
    for (int j = l; j; j >>= 1, x = ((long long) x * x) % n) {
      if (j & 1) {
        m = ((long long) m * x) % n;
      }
    }
    for (int i = l; i <= r; ++i) {
      printf("%lld", m * 10ll / n);
      m = m * 10ll % n;
    }
    puts("");
  }
  return 0;
}
