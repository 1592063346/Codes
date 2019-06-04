#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, a[N], b[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  long long sum = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sum += a[i];
  }
  if (sum % ((long long) n * (n + 1) / 2)) {
    cout << "NO" << '\n';
    exit(0);
  }
  long long maxb = 0;
  for (int i = 1; i <= n; ++i) {
    b[i] = a[i] - a[i == 1 ? n : i - 1];
    maxb = max(maxb, (long long) b[i]);
  }
  long long all = 0;
  for (int i = 1; i <= n; ++i) {
    if ((maxb - b[i]) % n) {
      cout << "NO" << '\n';
      exit(0);
    }
    all += (maxb - b[i]) / n;
  }
  long long diff = sum / ((long long) n * (n + 1) / 2) - all;
  cout << (all == maxb && diff >= 0 && diff % n == 0 ? "YES" : "NO") << '\n';
  return 0;
}
