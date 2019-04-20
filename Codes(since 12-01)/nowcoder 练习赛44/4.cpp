#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tt, md;
  cin >> tt;
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
  auto phi = [&] (int x) {
    int result = x;
    for (int i = 2; i * i <= x; ++i) {
      if (x % i == 0) {
        result = result / i * (i - 1);
        while (x % i == 0) {
          x /= i;
        }
      }
    }
    if (x > 1) {
      result = result / x * (x - 1);
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
  auto mul = [&] (int x, int y) {
    return (int) ((long long) x * y % md);
  };
  auto qpow = [&] (int x, long long y, int md) {
    int result = 1;
    for (; y; y >>= 1, x = mul(x, x)) {
      if (y & 1) {
        result = mul(result, x);
      }
    }
    return result;
  };
  while (tt--) {
    string x;
    cin >> x >> md;
    x = add(x, x);
    if (x.length() < 11) {
      long long y = 0;
      for (int i = 0; i < x.length(); ++i) {
        y = y * 10 + x[i] - '0';
      }
      cout << (qpow(2, y, md) - 1 + md) % md << '\n';
    } else {
      long long y = mod(x, phi(md)) + phi(md);
      cout << (qpow(2, y, md) - 1 + md) % md << '\n';
    }
  }
  return 0;
}
