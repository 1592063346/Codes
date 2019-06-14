#include<bits/stdc++.h>

using namespace std;

const int N = 567890, maxlog = 19;

int n, q, tt, root[N], sub[N], self[N], down[N], father[N], cnt[N * 20], go[N * 20][2];
vector<int> adj[N];

void dfs(int x, int f) {
  father[x] = f;
  for (auto y : adj[x]) {
    if (y != f) {
      dfs(y, x);
    }
  }
}

void insert(int& x, int d, int y, int z) {
  if (!x) {
    x = ++tt;
  }
  cnt[x] += z;
  if (d == maxlog) {
    return;
  }
  insert(go[x][y & 1], d + 1, y >> 1, z);
}

void modify(int x, int d, int& y) {
  if (!x || d == maxlog) {
    return;
  }
  if (cnt[go[x][0]] & 1) {
    y ^= (1 << d + 1) - 1;
  }
  swap(go[x][0], go[x][1]);
  modify(go[x][0], d + 1, y);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(1, 0);
  for (int i = 2; i <= n; ++i) {
    insert(root[father[i]], 0, 0, 1);
  }
  while (q--) {
    int x;
    cin >> x;
    modify(root[x], 0, sub[x]);
    int value = 0;
    if (x != 1) {
      int f = father[x];
      value = self[f] + down[father[f]];
      if (father[f]) {
        insert(root[father[f]], 0, value, -1);
        insert(root[father[f]], 0, value + 1, 1);
        sub[father[f]] ^= value ^ value + 1;
      }
      ++self[f];
      ++value;
    }
    ++down[x];
    cout << (sub[x] ^ value) << '\n';
  }
  return 0;
}
