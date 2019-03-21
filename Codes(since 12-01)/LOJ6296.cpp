#include<bits/stdc++.h>

using namespace std;

const int N = 3e4 + 10;

int n, m, from[N], to[N], len;
vector<pair<int, int>> adj[N];
bitset<N * 2> have[26], f[N], g[N], answer;
char cmd[N];

void dfs(int u, int p) {
  for (auto v : adj[u]) {
    if (v.first != p) {
      dfs(v.first, u);
      bitset<N * 2> ff = (f[v.first] << 1) & have[v.second];
      bitset<N * 2> gg = (g[v.first] >> 1) & have[v.second];
      answer |= (ff << 1) & g[u];
      answer |= (f[u] << 1) & gg;
      f[u] |= ff;
      g[u] |= gg;
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d%s", &u, &v, cmd);
    adj[u].emplace_back(v, *cmd - 'a');
    adj[v].emplace_back(u, *cmd - 'a');
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%s", cmd);
    int k = strlen(cmd);
    from[i] = len;
    f[0][len] = true;
    for (int j = 0; j < k; ++j) {
      have[cmd[j] - 'a'][++len] = true;
    }
    to[i] = ++len;
    g[0][len] = true;
  }
  for (int i = 1; i <= n; ++i) {
    f[i] = f[0];
    g[i] = g[0];
  }
  dfs(1, 0);
  for (int i = 1; i <= m; ++i) {
    bool appeared = false;
    for (int j = from[i] + 1; j <= to[i]; ++j) {
      appeared |= answer[j];
    }
    printf("%s\n", appeared ? "YES" : "NO");
  }
  return 0;
}
