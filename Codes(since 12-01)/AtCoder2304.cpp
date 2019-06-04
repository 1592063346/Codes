#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, root, degree[N];
long long s[N];
vector<int> adj[N];

int dfs(int x, int f) {
  bool go = false;
  vector<long long> values;
  for (auto y : adj[x]) {
    if (y != f) {
      go = true;
      values.push_back(dfs(y, x));
    }
  }
  if (!go) {
    return s[x];
  }
  long long sum = 0, max_value = 0;
  for (auto v : values) {
    sum += v;
    max_value = max(max_value, v);
  }
  auto no_solution = [&] () {
    cout << "NO" << '\n';
    exit(0);
  };
  if (sum > s[x] * 2 || s[x] > sum) {
    no_solution();
  }
  long long diff = sum - s[x];
  if (max_value * 2 > sum) {
    if (sum - max_value < diff) {
      no_solution();
    }
  }
  s[x] -= diff;
  sum -= diff << 1;
  if (x != root && sum != s[x]) {
    no_solution();
  } else if (x == root && (s[x] > 0 || sum > 0)) {
    no_solution();
  }
  return sum;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> s[i];
  }
  if (n == 2) {
    cout << (s[1] == s[2] ? "YES" : "NO") << '\n';
    exit(0);
  }
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
    ++degree[x];
    ++degree[y];
  }
  for (int i = 1; i <= n; ++i) {
    if (degree[i] > 1) {
      root = i;
    }
  }
  dfs(root, 0);
  cout << "YES" << '\n';
  return 0;
}
