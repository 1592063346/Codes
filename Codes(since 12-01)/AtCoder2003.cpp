#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, a[N], b[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    b[i] = a[i];
  }
  sort(b + 1, b + 1 + n);
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;
  }
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    if (a[i] - i & 1) {
      ++answer;
    }
  }
  answer >>= 1;
  cout << answer << '\n';
  return 0;
}
