#include<bits/stdc++.h>

using namespace std;

const int N = 234567, mod = 998244353;

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

int power(int x, int y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

int n, tt, depth[N], first[N], father[N], size[N], log_2[N << 1], coef[N], ways[N];
vector<int> adj[N], nodes[N];
vector<pair<int, int>> events[N];
pair<int, int> rmq_t[20][N << 1];

void dfs(int x) {
  first[x] = ++tt;
  rmq_t[0][tt] = make_pair(depth[x], x);
  nodes[depth[x]].push_back(x);
  for (auto y : adj[x]) {
    depth[y] = depth[x] + 1;
    dfs(y);
    rmq_t[0][++tt] = make_pair(depth[x], x);
  }
}

int get_lca(int x, int y) {
  x = first[x];
  y = first[y];
  if (x > y) {
    swap(x, y);
  }
  int k = log_2[y - x + 1];
  return min(rmq_t[k][x], rmq_t[k][y - (1 << k) + 1]).second;
}

int find(int x) {
  return father[x] == x ? x : father[x] = find(father[x]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1, x; i < n; ++i) {
    cin >> x;
    adj[x].push_back(i + 1);
  }
  dfs(1);
  for (int i = 2; i <= tt; ++i) {
    log_2[i] = log_2[i >> 1] + 1;
  }
  for (int i = 1; (1 << i) <= tt; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= tt; ++j) {
      rmq_t[i][j] = min(rmq_t[i - 1][j], rmq_t[i - 1][j + (1 << i - 1)]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    coef[i] = size[i] = 1;
    father[i] = i;
  }
  for (int i = 1; i <= n; ++i) {
    if (!nodes[i].size()) {
      break;
    }
    vector<int> value(1, i);
    for (int j = 0; j + 1 < nodes[i].size(); ++j) {
      int x = nodes[i][j], y = nodes[i][j + 1], lca = get_lca(x, y);
      value.push_back(depth[x] - depth[lca]);
      events[depth[x] - depth[lca]].emplace_back(x, y);
    }
    sort(value.begin(), value.end());
    value.erase(unique(value.begin(), value.end()), value.end());
    int last = 0, t = power(2, nodes[i].size());
    for (auto w : value) {
      coef[last + 1] = mul(coef[last + 1], t);
      coef[w + 1] = mul(coef[w + 1], power(t, mod - 2));
      last = w;
      for (auto p : events[w]) {
        int x = find(p.first), y = find(p.second);
        t = mul(t, power(size[x] + 1, mod - 2));
        t = mul(t, power(size[y] + 1, mod - 2));
        father[x] = y;
        size[y] += size[x];
        t = mul(t, size[y] + 1);
      }
      events[w].clear();
    }
  }
  int answer = 0;
  for (int i = 1, j = 1, k = 0; i <= n; ++i) {
    j = mul(j, coef[i]);
    k += nodes[i - 1].size();
    ways[i] = mul(j, k + 1);
    sub(ways[i], n + 1);
  }
  for (int i = 1; i <= n; ++i) {
    int cnt = (ways[i] - ways[i + 1] + mod) % mod;
    add(answer, mul(cnt, i));
  }
  cout << answer << '\n';
  return 0;
}
