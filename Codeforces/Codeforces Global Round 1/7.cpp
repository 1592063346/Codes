#include<bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

int tt, n, degree[N];
vector<int> graph[N];
char s[N];

void add_edge(int u, int v) {
  graph[u].push_back(v);
  graph[v].push_back(u);
  ++degree[u];
  ++degree[v];
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d", &n);
    if (n <= 2) {
      for (int i = 1; i < n; ++i) {
        scanf("%*d%*d");
      }
      scanf("%*s");
      puts("Draw");
      continue;
    }
    int tn = n;
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      add_edge(u, v);
    }
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i) {
      if (s[i] == 'W') {
        int newp = ++tn;
        add_edge(newp, i);
        add_edge(newp, ++tn);
        add_edge(newp, ++tn);
      }
    }
    bool stoped = false;
    for (int i = 1; i <= n; ++i) {
      if (degree[i] >= 4) {
        stoped = true;
        break;
      }
    }
    n = tn;
    if (!stoped) {
      for (int i = 1; i <= n; ++i) {
        if (degree[i] >= 3) {
          int total = 0;
          for (auto v : graph[i]) {
            if (degree[v] != 1) {
              ++total;
            }
          }
          if (total >= 2) {
            stoped = true;
            break;
          }
        }
      }
    }
    if (!stoped) {
      int leaves = 0;
      for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) {
          ++leaves;
        }
      }
      if (leaves == 4 && (n - leaves + 2 & 1)) {
        stoped = true;
      }
    }
    puts(stoped ? "White" : "Draw");
    for (int i = 1; i <= n; ++i) {
      graph[i].clear();
      degree[i] = 0;
    }
  }
  return 0;
}
