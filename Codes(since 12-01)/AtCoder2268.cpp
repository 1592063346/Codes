#include<bits/stdc++.h>

using namespace std;

const int N = 234567;

int n, maxd[N], smaxd[N], sum[N];
long long answer;
vector<int> adj[N];
string s;

void dfs(int x, int f) {
  sum[x] = s[x - 1] == '1';
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
      sum[x] += sum[y];
      int d = maxd[y] + 1;
      if (d > maxd[x]) {
        smaxd[x] = maxd[x];
        maxd[x] = d;
      } else {
        smaxd[x] = max(smaxd[x], d);
      }
    }
  }
}

void dfs(int x, int f, int fa_d) {
  int first = maxd[x], second = smaxd[x];
  if (fa_d > first) {
    second = first;
    first = fa_d;
  } else {
    second = max(second, fa_d);
  }
  int mind = n + 1;
  if (sum[1] - sum[x] > 0) {
    mind = min(mind, fa_d);
  }
  for (auto y : adj[x]) {
    if (y != f) {
      int new_d = max(fa_d, maxd[y] + 1 == maxd[x] ? smaxd[x] : maxd[x]);
      dfs(y, x, new_d + 1);
      if (new_d <= maxd[y] && sum[1] - sum[y] > 0) {
        ++answer;
      } else if (new_d >= maxd[y] && sum[y] > 0) {
        ++answer;
      }
      if (sum[y]) {
        mind = min(mind, maxd[y] + 1);
      }
    }
  }
  int up = second, down = s[x - 1] == '1' ? 0 : mind;
  answer += max(0, up - down + 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  cin >> s;
  dfs(1, 0);
  dfs(1, 0, 0);
  cout << answer << '\n';
  return 0;
}
