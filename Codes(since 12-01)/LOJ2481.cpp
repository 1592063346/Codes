#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n;
double a[N], b[N];

double solve(int x, int y) {
  --x;
  --y;
  return min(a[x], b[y]) - x - y - 2;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.setf(ios::fixed);
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i];
  }
  sort(a, a + n, greater<double>());
  sort(b, b + n, greater<double>());
  for (int i = 1; i < n; ++i) {
    a[i] += a[i - 1];
    b[i] += b[i - 1];
  }
  double answer = 0;
  for (int i = 1; i <= n * 2; ++i) {
    int l = max(1, i - n), r = min(i - 1, n);
    while (r - l >= 3) {
      int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
      if (solve(m1, i - m1) >= solve(m2, i - m2)) {
        r = m2;
      } else {
        l = m1;
      }
    }
    for (int j = l; j <= r; ++j) {
      answer = max(answer, solve(j, i - j));
    }
  }
  cout << setprecision(4) << answer << '\n';
  return 0;
}
