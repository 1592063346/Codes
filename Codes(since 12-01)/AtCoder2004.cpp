#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n;
long long a[N], b[N];
map<long long, int> number;
map<long long, bool> used;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    long long x = a[i];
    a[i] = b[i] = 1;
    for (int j = 2; j <= 2200; ++j) {
      if (x % j == 0) {
        int t = 0;
        while (x % j == 0) {
          x /= j;
          ++t;
        }
        if (t % 3 == 1) {
          a[i] *= j;
          b[i] *= j * j;
        } else if (t % 3 == 2) {
          a[i] *= j * j;
          b[i] *= j;
        }
      }
    }
    if (x != 1) {
      long long y = (long long) (sqrt(x) + 0.5);
      a[i] *= x;
      if (y * y == x) {
        b[i] *= y;
      } else {
        b[i] *= x * x;
      }
    }
    ++number[a[i]];
  }
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    if (!used[a[i]]) {
      used[a[i]] = used[b[i]] = true;
      if (a[i] == 1) {
        ++answer;
      } else {
        answer += max(number[a[i]], number[b[i]]);
      }
    }
  }
  cout << answer << '\n';
  return 0;
}
