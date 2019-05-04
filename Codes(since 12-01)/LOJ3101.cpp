#include<bits/stdc++.h>

using namespace std;

const int N = 50003, M = N * 10, max_block = 10000;

int t, n, m, tt, dfn[M], low[M], no[M], sta[M], ttt, top, scct, answer[N], final[N];
vector<int> adj[M], newadj[M];
bitset<max_block> states[M];
map<int, int> foo[N];
bool visit[M];

void tarjan(int x) {
  dfn[x] = low[x] = ttt++;
  sta[++top] = x;
  for (auto y : adj[x]) {
    if (!~dfn[y]) {
      tarjan(y);
      low[x] = min(low[x], low[y]);
    } else if (!~no[y]) {
      low[x] = min(low[x], dfn[y]);
    }
  }
  if (low[x] == dfn[x]) {
    while (1) {
      int y = sta[top--];
      no[y] = scct;
      if (x == y) {
        break;
      }
    }
    ++scct;
  }
}

void find(int x) {
  if (visit[x]) {
    return;
  }
  visit[x] = true;
  for (auto y : newadj[x]) {
    find(y);
    states[x] |= states[y];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> t >> n >> m;
  auto id = [&] (int x, int y) {
    if (!foo[x].count(y)) {
      foo[x][y] = tt;
      tt += 2;
    }
    return foo[x][y];
  };
  auto add = [&] (int x, int y) {
    adj[x].push_back(y);
    x ^= 1;
    y ^= 1;
    adj[y].push_back(x);
  };
  for (int i = 0, op, t, x, y; i < m; ++i) {
    cin >> op >> t >> x >> y;
    if (op == 0) {
      add(id(x, t) ^ 1, id(y, t + 1) ^ 1);
    } else {
      add(id(x, t), id(y, t) ^ 1);
    }
  }
  for (int i = 1; i <= n; ++i) {
    vector<int> nodes;
    for (auto node : foo[i]) {
      nodes.push_back(node.first);
    }
    if (!nodes.size() || nodes.back() != t + 1) {
      nodes.push_back(t + 1);
    }
    final[i] = id(i, t + 1);
    reverse(nodes.begin(), nodes.end());
    for (int j = 0; j + 1 < nodes.size(); ++j) {
      add(id(i, nodes[j]), id(i, nodes[j + 1]));
    }
  }
  for (int i = 0; i < tt; ++i) {
    dfn[i] = low[i] = no[i] = -1;
  }
  for (int i = 0; i < tt; ++i) {
    if (!~dfn[i]) {
      tarjan(i);
    }
  }
  for (int i = 1; i <= n; ++i) {
    answer[i] = n;
  }
  for (int i = 0; i < tt; ++i) {
    for (auto j : adj[i]) {
      if (no[i] != no[j]) {
        newadj[no[i]].push_back(no[j]);
      }
    }
  }
  for (int l = 1, r; l <= n; l += max_block) {
    r = min(n, l + max_block - 1);
    bitset<max_block> dead;
    for (int i = 0; i < scct; ++i) {
      visit[i] = false;
      states[i].reset();
    }
    for (int i = l; i <= r; ++i) {
      states[no[final[i] ^ 1]][i - l] = true;
    }
    for (int i = l, x; i <= r; ++i) {      
      find(x = no[final[i]]);
      if (states[x][i - l]) {
        dead[i - l] = true;
        answer[i] = -1;
      }
    }
    for (int i = 1, x, y; i <= n; ++i) {
      if (~answer[i]) {
        find(x = no[final[i]]);
        bitset<max_block> result = states[x] | dead;
        if (i >= l && i <= r) {
          result[i - l] = true;
        }
        answer[i] -= result.count();
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    cout << (~answer[i] ? answer[i] : 0) << " \n"[i == n];
  }
  return 0;
}
