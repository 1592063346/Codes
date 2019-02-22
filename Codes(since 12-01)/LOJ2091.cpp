#include<bits/stdc++.h>

using namespace std;

const int N = 17;

int n, m;
long long f[N][N];
bool linked[N][N];
vector<int> graph[N];

void dfs(int u, int father, int s) {
  for (int i = 0; i < n; ++i) {
    f[u][i] = (s >> i & 1);
  }
  for (auto v : graph[u]) {
    if (v != father) {
      dfs(v, u, s);
      for (int i = 0; i < n; ++i) {
        if (s >> i & 1) {
          long long result = 0;
          for (int j = 0; j < n; ++j) {
            if ((s >> j & 1) && linked[i][j]) {
              result += f[v][j];
            }
          }
          f[u][i] *= result;
        }
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u;
    --v;
    linked[u][v] = true;
    linked[v][u] = true;
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u;
    --v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  long long answer = 0;
  for (int s = 1; s <= 1 << n; ++s) {
    dfs(0, -1, s);
    int opt = (__builtin_popcount((1 << n) - 1 ^ s) & 1) ? -1 : 1;
    for (int i = 0; i < n; ++i) {
      if (s >> i & 1) {
        answer += opt * f[0][i];
      }
    }
  }
  printf("%lld\n", answer);
  return 0;
}
