#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string n = "0", m;
  cin >> m;
  auto add = [&] (string x, string y) {
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    int n = x.length(), m = y.length();
    x.resize(max(n, m), '0');
    y.resize(max(n, m), '0');
    vector<int> s(max(n, m) + 1, 0);
    for (int i = 0; i < max(n, m); ++i) {
      s[i] += x[i] - '0' + y[i] - '0';
      if (s[i] >= 10) {
        s[i + 1] += s[i] / 10;
        s[i] %= 10;
      }
    }
    string result = "";
    for (int i = 0; i <= max(n, m); ++i) {
      result += s[i] + '0';
    }
    while (result.length() > 1 && result[result.length() - 1] == '0') {
      result.pop_back();
    }
    reverse(result.begin(), result.end());
    return result;
  };
  for (int i = 1; i <= 9; ++i) {
    n = add(n, m);
  }
  int l = 1, r = m.length();
  while (l != r) {
    int mid = l + r >> 1;
    auto check = [&] (int x) {
      string number = add(n, to_string(9 * x));
      int len = number.length(), all = 0;
      for (int i = 0; i < len; ++i) {
        all += number[i] - '0';
      }
      return all <= 9 * x;
    };
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << l << '\n';
  return 0;
}
