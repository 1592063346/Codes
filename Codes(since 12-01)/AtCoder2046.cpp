#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, m, s[N], value[N], father[N], dfn[N], coef[N], tt, answer;
bool ban[N];
vector<int> adj[N], circle;

void dfs(int x, int f, int d) {
  s[x] = 0;
  father[x] = f;
  for (auto y : adj[x]) {
    if (y != f && (!ban[x] || !ban[y])) {
      dfs(y, x, !d);
      s[x] += s[y];
    }
  }
  s[x] += value[x];
  if (d) {
    ++s[x];
  } else {
    --s[x];
  }
  answer += abs(s[x]);
}

void find_circle(int x, int f) {
  dfn[x] = ++tt;
  father[x] = f;
  for (auto y : adj[x]) {
    if (y != f) {
      if (!dfn[y]) {
        find_circle(y, x);
      } else if (dfn[y] < dfn[x]) {
        circle.push_back(x);
        int z = x;
        while (z != y) {
          circle.push_back(z = father[z]);
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  if (m == n - 1) {
    dfs(1, 0, 0);
    cout << (s[1] ? -1 : answer) << '\n';
  } else {
    find_circle(1, 0);
    ban[circle[0]] = ban[circle[1]] = true;
    dfs(1, 0, 0);
    if (circle.size() & 1) {
      if (s[1] & 1) {
        cout << -1 << '\n';
      } else {
        value[circle[0]] -= s[1] >> 1;
        value[circle[1]] -= s[1] >> 1;
        answer = abs(s[1] >> 1);
        dfs(1, 0, 0);
        cout << answer << '\n';
      }
    } else {
      if (s[1]) {
        cout << -1 << '\n';
      } else {
        int x = circle[0], y = circle[1];
        while (x) {
          ++coef[x];
          x = father[x];
        }
        while (y) {
          --coef[y];
          y = father[y];
        }
        answer = 0;
        vector<int> values(1, 0);
        for (int i = 1; i <= n; ++i) {
          if (coef[i] == 0) {
            answer += abs(s[i]);
          } else if (coef[i] == 1) {
            values.push_back(-s[i]);
          } else {
            values.push_back(s[i]);
          }
        }
        sort(values.begin(), values.end());
        int p = values[values.size() >> 1];
        for (auto v : values) {
          answer += abs(v - p);
        }
        cout << answer << '\n';
      }
    }
  }
  return 0;
}
