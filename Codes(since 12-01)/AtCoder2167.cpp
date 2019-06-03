#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, m, color[N], number[3], number_e;
vector<pair<int, int>> adj[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  long long answer = 0;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    adj[x].emplace_back(y, 1);
    adj[y].emplace_back(x, -1);
  }
  bool ok;
  function<void (int, int)> dfs = [&] (int x, int z) {
    ++number[color[x] = z];
    for (auto e : adj[x]) {
      int y = e.first;
      if (e.second == 1) {
        ++number_e;
      }
      if (!~color[y]) {
        dfs(y, (z + e.second + 3) % 3);
      } else if (color[y] != (z + e.second + 3) % 3) {
        ok = false;
      }
    }
  };
  memset(color, -1, sizeof color);
  for (int i = 1; i <= n; ++i) {
    if (!~color[i]) {
      memset(number, 0, sizeof number);
      number_e = 0;
      ok = true;
      dfs(i, 0);
      if (ok && (!number[1] || !number[2])) {
        answer += number_e;
      } else if (ok) {
        answer += (long long) number[0] * number[1];
        answer += (long long) number[1] * number[2];
        answer += (long long) number[2] * number[0];
      } else {
        int all = number[0] + number[1] + number[2];
        answer += (long long) all * all;
      }
    }
  }
  cout << answer << '\n';
  return 0;
}
