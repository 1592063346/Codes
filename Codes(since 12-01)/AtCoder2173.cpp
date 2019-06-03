#include<bits/stdc++.h>

using namespace std;

int n;
string s, t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> s >> t;
  int foo = 0, bar = 0, final = 0;
  queue<int> q;
  for (int i = n - 1, j, k = n - 1; ~i; i = j) {
    j = i;
    while (~j && t[j] == t[i]) {
      --j;
    }
    k = min(k, j + 1);
    while (~k && s[k] != t[i]) {
      --k;
    }
    if (!~k) {
      cout << -1 << '\n';
      exit(0);
    }
    if (j + 1 == k) {
      for (int l = j + 1; l <= i; ++l) {
        if (s[l] != t[l]) {
          final = 1;
        }
      }
      while (q.size()) {
        q.pop();
      }
      bar = 0;
    } else {
      final = 1;
      while (!q.empty() && q.front() >= j + 1 + q.size()) {
        q.pop();
      }
      q.push(k);
      foo = max(foo, bar = q.size());
    }
  }
  cout << foo + final << '\n';
  return 0;
}
