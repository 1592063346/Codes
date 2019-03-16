#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string a, b;
  cin >> a >> b;
  int n = a.length();
  long long answer = 0;
  for (int i = 0, last = -1; i < n; ++i) {
    if (a[i] == b[i]) {
      answer = max(answer, (long long) i - last);
    } else {
      last = i;
    }
  }
  cout << answer * answer + answer * 2 << "\n";
  return 0;
}
