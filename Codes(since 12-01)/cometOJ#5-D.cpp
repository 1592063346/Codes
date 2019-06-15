#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 18, sq = 2000, mod = 998244353;

int n, m, q, tt, degree[N], a[N], x[N], y[N], z[N], ch[N * 100][2], root[N], tag[N], now_tag;
vector<pair<int, int>> adj[N], sadj[N];
long long sum[N * 100];
bool type[N];

class bit {
  long long a[N];

 public:
  bit() {
    memset(a, 0, sizeof a);
  }

  void add(int x, int y) {
    if (!x) {
      a[0] += y;
      return;
    }
    while (x < N) {
      a[x] += y;
      x += x & -x;
    }
  }

  long long sum(int x) {
    long long result = a[0];
    while (x) {
      result += a[x];
      x -= x & -x;
    }
    return result;
  }
} tree;

void insert(int& x, int d, int y, int z, int now_tag) {
  if (!x) {
    x = ++tt;
  }
  sum[x] += z;
  if (!~d) {
    return;
  }
  insert(ch[x][(y >> d & 1) ^ (now_tag >> d & 1)], d - 1, y, z, now_tag);
}

long long query(int x, int d, int y, int now_tag) {
  if (!x) {
    return 0;
  }
  if (!~d) {
    return sum[x];
  }
  if (y >> d & 1) {
    if (now_tag >> d & 1) {
      return sum[ch[x][1]] + query(ch[x][0], d - 1, y, now_tag);
    } else {
      return sum[ch[x][0]] + query(ch[x][1], d - 1, y, now_tag);
    }
  } else {
    if (now_tag >> d & 1) {
      return query(ch[x][1], d - 1, y, now_tag);
    } else {
      return query(ch[x][0], d - 1, y, now_tag);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> x[i] >> y[i] >> z[i];
    adj[x[i]].emplace_back(y[i], i);
    adj[y[i]].emplace_back(x[i], i);
    ++degree[x[i]];
    ++degree[y[i]];
  }
  for (int i = 1; i <= n; ++i) {
    if (degree[i] <= sq) {
      type[i] = false;
    } else {
      type[i] = true;
    }
  }
  vector<int> snodes;
  for (int i = 1; i <= n; ++i) {
    if (type[i]) {
      tag[i] = a[i];
      snodes.push_back(i);
      for (auto p : adj[i]) {
        if (type[p.first]) {
          sadj[i].push_back(p);
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (auto p : adj[i]) {
      int j = p.first;
      if (type[i] == type[j] && i < j) {
        tree.add(a[i] ^ a[j], z[p.second]);
      } else if (type[i] && !type[j]) {
        insert(root[i], 16, a[i] ^ a[j], z[p.second], tag[i]);
      }
    }
  }
  for (int i = 1, op, u, v; i <= q; ++i) {
    cin >> op >> u >> v;
    if (op == 1) {
      if (!type[u]) {
        for (auto p : adj[u]) {
          if (!type[p.first]) {
            tree.add(a[u] ^ a[p.first], -z[p.second]);
            tree.add(v ^ a[p.first], z[p.second]);
          } else {
            insert(root[p.first], 16, a[u] ^ a[p.first], -z[p.second], tag[p.first]);
            insert(root[p.first], 16, v ^ a[p.first], z[p.second], tag[p.first]);
          }
        }
      } else {
        tag[u] ^= a[u] ^ v;
        for (auto p : sadj[u]) {
          tree.add(a[u] ^ a[p.first], -z[p.second]);
          tree.add(v ^ a[p.first], z[p.second]);
        }
      }
      a[u] = v;
    } else if (op == 2) {
      int s = x[u], t = y[u];
      if (type[s] == type[t]) {
        tree.add(a[s] ^ a[t], -z[u]);
        tree.add(a[s] ^ a[t], v);
      } else {
        if (type[t]) {
          swap(s, t);
        }
        insert(root[s], 16, a[s] ^ a[t], -z[u], tag[s]);
        insert(root[s], 16, a[s] ^ a[t], v, tag[s]);
      }
      z[u] = v;
    } else {
      --u;
      long long answer = tree.sum(v) - (~u ? tree.sum(u) : 0);
      for (auto x : snodes) {
        answer += query(root[x], 16, v, tag[x]) - (~u ? query(root[x], 16, u, tag[x]) : 0);
      }
      cout << (answer % mod) << '\n';
    }
  }
  return 0;
}
