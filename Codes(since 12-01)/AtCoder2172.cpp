#include<bits/stdc++.h>

using namespace std;

const int N = 234567;

int n, limit;
vector<pair<int, int>> adj[N], states[N];

void dfs(int x) {
  states[x].clear();
  if (!adj[x].size()) {
    states[x].emplace_back(0, 0);
  } else {
    int l = adj[x][0].first, r = adj[x][1].first;
    dfs(l);
    dfs(r);
    for (auto e : adj[x]) {
      int y = e.first;
      for (auto& state : states[y]) {
        state.first += e.second;
        state.second += e.second;
      }
    }
    if (states[l].size() > states[r].size()) {
      swap(l, r);
    }
    vector<pair<int, int>> all;
    auto cmpy = [&] (const pair<int, int>& a, const pair<int, int>& b) {
      return a.second > b.second;
    };
    auto cmpx = [&] (const pair<int, int>& a, const pair<int, int>& b) {
      return a.first < b.first;
    };
    sort(states[l].begin(), states[l].end(), cmpy);
    sort(states[r].begin(), states[r].end(), cmpx);
    for (int i = 0, j = 0, k = 1e7; i < states[l].size(); ++i) {
      int y = states[l][i].first, z = states[l][i].second;
      while (j < states[r].size() && z + states[r][j].first <= limit) {
        k = min(k, states[r][j].second);
        ++j;
      }
      if (j) {
        all.emplace_back(y, k);
        all.emplace_back(k, y);
      }
    }
    sort(all.begin(), all.end());
    for (int i = 0; i < all.size(); ++i) {
      if (i && all[i].first == all[i - 1].first) {
        continue;
      } else {
        states[x].push_back(all[i]);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 2, x, y; i <= n; ++i) {
    cin >> x >> y;
    adj[x].emplace_back(i, y);
  }
  auto check = [&] (int x) {
    limit = x;
    dfs(1);
    return states[1].size() > 0;
  };
  int l = 0, r = 1e9;
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
