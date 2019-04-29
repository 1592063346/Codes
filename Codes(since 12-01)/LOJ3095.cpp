#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n;
vector<int> foo[N];
string x, y;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> x;
  int last = -1;
  for (int i = 0, j = -1; i < n; ++i) {
    if (~last && x[i] == x[last]) {
      foo[j].push_back(i);
    } else {
      last = i;
      foo[++j].push_back(i);
      y.push_back(x[i]);
    }
  }
  y.push_back('z' + 1);
  function<void (int)> print = [&] (int here) {
    if (here == y.length() - 1) {
      return;
    }
    if (y[here] < y[here + 1]) {
      print(here + 1);
      for (auto x : foo[here]) {
        cout << x + 1 << ' ';
      }
    } else {
      for (auto x : foo[here]) {
        cout << x + 1 << ' ';
      }
      print(here + 1);
    }
  };
  print(0);
  cout << '\n';
  return 0;
}
