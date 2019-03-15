#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

void cmin(long long& x, long long y) {
  if (x > y) {
    x = y;
  }
}

int n, a[N];
long long f[N][2];
bool best[N][2];
vector<int> adj[N], answer;

void dfs1(int u, int p) {
  long long min_diff = 0;
  bool go = false;
  for (auto v : adj[u]) {
    if (v != p) {
      go = true;
      dfs1(v, u);
      f[u][0] += f[v][0];
      f[u][1] += f[v][0];
      cmin(min_diff, f[v][1] - f[v][0]);
    }
  }
  f[u][1] += min_diff;
  if (!go) {
    f[u][0] = a[u];
  } else {
    cmin(f[u][0], f[u][1] + a[u]);
  }
}

void dfs2(int u, int p) {
  if (f[u][0] == f[u][1] + a[u]) {
    best[u][1] |= best[u][0];
    if (best[u][0]) {
      answer.push_back(u);
    }
  }
  long long sumf = 0;
  for (auto v : adj[u]) {
    if (v != p) {
      sumf += f[v][0];
    }
  }
  vector<int> diff_nodes;
  for (auto v : adj[u]) {
    if (v != p) {
      if (sumf == f[u][0]) {
        best[v][0] |= best[u][0];
      }
      if (sumf + f[v][1] - f[v][0] == f[u][1] && best[u][1]) {
        best[v][1] = true;
        diff_nodes.push_back(v);
      } else if (sumf + f[v][1] - f[v][0] + a[u] == f[u][0] && best[u][0]) {
        diff_nodes.push_back(v);
      }
    }
  }
  for (auto v : adj[u]) {
    if (v != p) {
      if (diff_nodes.size() > 1) {
        best[v][0] |= true;
      } else if (diff_nodes.size() == 1 && v != diff_nodes.back()) {
        best[v][0] |= true;
      }
      dfs2(v, u);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs1(1, 0);
  best[1][0] = true;
  dfs2(1, 0);
  printf("%lld %d\n", f[1][0], answer.size());
  sort(answer.begin(), answer.end());
  for (auto v : answer) {
    printf("%d ", v);
  }
  return puts(""), 0;
}
