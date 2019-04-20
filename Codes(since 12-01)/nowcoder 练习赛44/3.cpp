#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long l, r, k;
  cin >> l >> r >> k;
  k <<= 1;
  if (!l) {
    ++l;
  }
  l += k;
  if (l > r) {
    cout << 0 << '\n';
    return 0;
  }
  vector<long long> factor;
  for (long long i = 2; i * i <= k; ++i) {
    if (k % i == 0) {
      while (k % i == 0) {
        k /= i;
      }
      factor.push_back(i);
    }
  }
  if (k != 1) {
    factor.push_back(k);
  }
  long long answer = 0;
  function<void (int, int, long long)> dfs = [&] (int d, int x, long long lcm) {
    if (d == factor.size()) {
      answer += (x & 1 ? -1 : 1) * (r / lcm - (l - 1) / lcm);
    } else {
      dfs(d + 1, x, lcm);
      dfs(d + 1, x + 1, lcm * factor[d]);
    }
  };
  dfs(0, 0, 1);
  cout << answer << '\n';
  return 0;
}
