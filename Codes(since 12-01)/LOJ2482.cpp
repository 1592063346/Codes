#include<bits/stdc++.h>

using namespace std;

const int N = 1234567;

int n, t, m, father[N], cuts[N], cost[N], answer;
vector<int> adj[N];

void dfs(int x, int f) {
  father[x] = f;
  if (~f) {
    cuts[x] = cuts[f] + adj[x].size() - 2;
  }
  long long max0 = -1, max1 = -1;
  for (int i = 0; i < adj[x].size(); ++i) {
    int y = adj[x][i];
    if (y != f) {
      ++cost[x];
      dfs(y, x);
      if (cost[y] > max0) {
        max1 = max0;
        max0 = cost[y];
      } else if (cost[y] > max1) {
        max1 = cost[y];
      }
    }
  }
  if (~max1) {
    cost[x] += max1;
  }
}

bool check(int limit) {
  int rest = min(limit, 1), times = 0;
  for (int last = -1, x = m; x != t; last = x, x = father[x]) {
    int foo = ~last ? -1 : 0;
    for (int i = 0; i < adj[x].size(); ++i) {
      int y = adj[x][i];
      if (y != last && y != father[x]) {
        if (cost[y] + foo + 1 > limit - times) {
          --foo;
          if (++times > rest) {
            return false;
          }
        }
      }
    }
    ++rest;
    rest = min(rest, limit);
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> t >> m;
  if (t == m) {
    cout << 0 << '\n';
    return 0;
  }
  --t;
  --m;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    --x;
    --y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(t, -1);
  for (int i = 0; i < n; ++i) {
    if (i != t) {
      cost[i] += cuts[father[i]];
    }
  }
  int l = 0, r = n;
  while (l != r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << l << '\n';
  return 0;
}
