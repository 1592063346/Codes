#include<bits/stdc++.h>

using namespace std;

const int N = 1234, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, a[N][N], b[N][N], height[N];

long long solve(int x, int y) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      b[i][j] = (a[i][j] >> x & 1) == y;
    }
  }
  memset(height, 0, sizeof height);
  long long result = 0;
  for (int i = 0; i < n; ++i) {
    vector<pair<int, int>> hqueue;
    int t = 0;
    for (int j = 0; j < n; ++j) {
      height[j] = b[i][j] ? height[j] + 1 : 0;
      while (hqueue.size() && height[hqueue.back().second] >= height[j]) {
        t -= height[hqueue.back().second] * (hqueue.back().second - hqueue.back().first + 1);
        hqueue.pop_back();
      }
      int l, r = j;
      if (!hqueue.size()) {
        l = 0;
      } else {
        l = hqueue.back().second + 1;
      }
      hqueue.emplace_back(l, r);
      t += height[j] * (r - l + 1);
      result += t;
    }
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> a[i][j];
    }
  }
  long long all = (long long) n * n * (n + 1) * (n + 1) >> 2;
  int answer_and = 0, answer_or = 0;
  for (int i = 0; i <= 30; ++i) {
    add(answer_and, mul(1 << i, solve(i, 1)));
    add(answer_or, mul(1 << i, (all - solve(i, 0)) % mod));
  }
  cout << answer_and << ' ' << answer_or << '\n';
  return 0;
}
