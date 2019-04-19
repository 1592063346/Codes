#include<bits/stdc++.h>

using namespace std;

const int N = 2345, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, m;
vector<pair<int, int>> adj[N];
char color[N];
bool can[200];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> color;
  for (int i = 1, x, y, z; i < n; ++i) {
    cin >> x >> y >> z;
    --x;
    --y;
    adj[x].emplace_back(y, z);
    adj[y].emplace_back(x, z); 
  }

  function<int (int, int, int)> dfs = [&] (int u, int p, int d) {
    int result = 1;
    for (auto v : adj[u]) {
      if (v.first != p && d + v.second <= m && can[color[v.first]]) {
        result = mul(result, dfs(v.first, u, d + v.second) + 1);
      }
    }
    return result;
  };

  int answer = 0;
  can['G'] = true; 
  for (int i = 0; i < n; ++i) {
    if (color[i] == 'G') {
      int x = 1;
      can['R'] = true;
      can['B'] = false;
      x = mul(x, dfs(i, -1, 0));
      can['B'] = true;
      can['R'] = false;
      x = mul(x, dfs(i, -1, 0));
      add(answer, x); 
    }
  }
  for (int i = 0; i < n; ++i) {
    if (color[i] == 'G') {
      for (auto e : adj[i]) {
        int j = e.first;
        if (j > i && color[j] == 'G' && e.second <= m) {
          int x = 1;
          can['R'] = true;
          can['B'] = false;
          x = mul(x, dfs(i, j, e.second));
          x = mul(x, dfs(j, i, e.second));
          can['B'] = true;
          can['R'] = false;
          x = mul(x, dfs(i, j, e.second));
          x = mul(x, dfs(j, i, e.second));
          sub(answer, x);
        }
      }
    }
  }
  cout << answer << '\n';
  return 0;
}
