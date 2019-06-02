#include<bits/stdc++.h>

using namespace std;

const int N = 123;

int n, a[N], number[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  int dir = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    ++number[a[i]];
    dir = max(dir, a[i]);
  }
  auto no_solution = [&] () {
    cout << "Impossible" << '\n';
    exit(0);
  };
  if (!(dir & 1) && number[dir >> 1] != 1) {
    no_solution();
  } else if ((dir & 1) && number[dir + 1 >> 1] != 2) {
    no_solution();
  }
  for (int i = dir; i; --i) {
    if (i + i > dir && number[i] < 2) {
      no_solution();
    } else if (i + i < dir && number[i]) {
      no_solution();
    }
  }
  cout << "Possible" << '\n';
  return 0;
}
