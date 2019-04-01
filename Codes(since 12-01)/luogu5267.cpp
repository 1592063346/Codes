#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

struct info_t {
  int x, y, id;

  info_t() {}
  info_t(int x, int y, int id): x(x), y(y), id(id) {}

  bool operator < (const info_t& a) const {
    return y == a.y ? id > a.id : y < a.y;
  }
};

int n, m, color[N], all, root, size[N], f[N], number[N], last[N], answer[N];
vector<info_t> control[N], events[N];
vector<int> adj[N];
bool visit[N];

void find_root(int u, int p) {
  size[u] = 1;
  f[u] = 0;
  for (auto v : adj[u]) {
    if (v != p && !visit[v]) {
      find_root(v, u);
      size[u] += size[v];
      cmax(f[u], size[v]);
    }
  }
  cmax(f[u], all - size[u]);
  if (f[u] < f[root]) {
    root = u;
  }
}

void dfs(int u, int p, int l, int r) {
  cmin(l, u);
  cmax(r, u);
  control[u].emplace_back(l, r, root);
  events[root].emplace_back(l, r, color[u]);
  for (auto v : adj[u]) {
    if (v != p && !visit[v]) {
      dfs(v, u, l, r);
    }
  }
}

void solve(int u) {
  visit[u] = true;
  dfs(u, 0, u, u);
  int old = all;
  for (auto v : adj[u]) {
    if (!visit[v]) {
      if (size[v] > size[u]) {
        all = old - size[u];
      } else {
        all = size[v];
      }
      root = 0;
      find_root(v, 0);
      solve(root);
    }
  }
}

void modify(int p, int v) {
  for (; p; p -= p & -p) {
    number[p] += v;
  }
}

int query(int p) {
  int result = 0;
  for (; p <= n; p += p & -p) {
    result += number[p];
  }
  return result;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &color[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  all = n;
  f[0] = n + 1;
  find_root(1, 0);
  solve(root);
  for (int i = 1; i <= m; ++i) {
    int l, r, x;
    scanf("%d%d%d", &l, &r, &x);
    for (auto info : control[x]) {
      if (l <= info.x && info.y <= r) {
        events[info.id].emplace_back(l, r, -i);
        break;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (events[i].size()) {
      sort(events[i].begin(), events[i].end());
      for (auto info : events[i]) {
        if (info.id < 0) {
          answer[-info.id] = query(info.x);
        } else {
          if (last[info.id] < info.x) {
            if (last[info.id]) {
              modify(last[info.id], -1);
            }
            modify(info.x, 1);
            last[info.id] = info.x;
          }
        }
      }
      for (auto info : events[i]) {
        if (info.id > 0 && last[info.id]) {
          modify(last[info.id], -1);
          last[info.id] = 0;
        }
      }
    }
  }
  for (int i = 1; i <= m; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
