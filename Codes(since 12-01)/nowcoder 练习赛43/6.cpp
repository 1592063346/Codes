#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  vector<map<int, int>> coef(21);
  int up;

  auto lcm = [&] (int x, int y) {
    return x * y / __gcd(x, y);
  };

  function<void (int, int, int)> dfs = [&] (int d, int x, int y) {
    if (d <= up) {
      dfs(d + 1, x + 1, lcm(y, d));
      dfs(d + 1, x, y);
    } else {
      coef[up][y] += x & 1 ? -1 : 1;
    }
  };

  for (up = 1; up <= 20; ++up) {
    dfs(2, 0, 1);
  }
  int tt;
  long long k, q, n;
  int m;
  cin >> tt;
  while (tt--) {
    cin >> k >> q >> n >> m;
    if (!k) {
      cout << "QAQ" << '\n';
      continue;
    }
    long long atk = 0;
    for (auto x : coef[m]) {
      if (x.first <= n) {
        atk += x.second * (n / x.first);
      } else {
        break;
      }
    }
    cerr << atk << '\n';
    q -= atk + k - 1;
    cout << (q <= 0 ? "Yes" : "QAQ") << '\n';
  }
  return 0;
}
