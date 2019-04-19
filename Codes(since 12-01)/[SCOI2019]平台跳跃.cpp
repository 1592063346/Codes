#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m, k, q;
  cin >> n >> m >> k >> q;
  int a = k - 1, b = n - k;

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

  auto div = [&] (string x, int y) {
    int n = x.length(), z = 0, base = 10;
    string result = "";
    for (int i = 0, first = 0; i < n; ++i) {
      z = z * base + x[i] - '0';
      if (z >= y) {
        first = 1;
      }
      if (first) {
        result.push_back(z / y + '0');
        z %= y;
      }
    }
    if (!result.size()) {
      result.push_back('0');
    }
    return result;
  };

  auto mod = [&] (string x, long long y) {
    int n = x.length(), base = 10;
    long long z = 0;
    for (int i = 0; i < n; ++i) {
      z = z * base + x[i] - '0';
      z %= y;
    }
    return z;
  };

  while (q--) {
    string x;
    cin >> x;
    string y = div(x, a + b);
    int z = mod(x, a + b);
    y = add(y, y);
    if (z && z <= a) {
      y = add(y, "1");
    } else if (z) {
      y = add(y, "2");
    }
    long long t = 68630377364883ll;
    for (int i = 29; ~i; --i, t /= 3) {
      if (mod(y, t) == 0) {
        cout << i + 1 << '\n';
        break;
      }
    }
  }
  return 0;
}
