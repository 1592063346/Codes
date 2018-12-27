#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, maxlen[N][2], pa[N], result;
vector<int> graph[N], nodes;

void dfs(int u, int pa) {
  for (auto v : graph[u]) {
    if (v ^ pa) {
      dfs(v, u);
    }
  }
  nodes.push_back(u);
  ::pa[u] = pa;
}

int f(int d) {
  result = 0;
  memset(maxlen, 0, sizeof maxlen);
  for (auto u : nodes) {
    if (maxlen[u][0] + maxlen[u][1] + 1 >= d) {
      ++result;
      maxlen[u][0] = 0;
    } else {
      ++maxlen[u][0];
    }
    if (pa[u]) {
      if (maxlen[u][0] > maxlen[pa[u]][0]) {
        maxlen[pa[u]][1] = maxlen[pa[u]][0];
        maxlen[pa[u]][0] = maxlen[u][0];
      } else {
        cmax(maxlen[pa[u]][1], maxlen[u][0]);
      }
    }
  }
  return result;
}

int main() {
  scanf("%d", &n);
  int block = min(n, 400);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d" ,&u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= block; ++i) {
    printf("%d\n", f(i));
  }
  int k = block + 1;
  for (int i = n / (block + 1); i; --i) {
    int l = k - 1, r = n;
    while (l ^ r) {
      int mid = (l + r >> 1) + 1;
      if (f(mid) >= i) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    for (int j = k; j <= l; ++j) {
      printf("%d\n", i);
    }
    k = l + 1;
  }
  for (int i = k; i <= n; ++i) {
    puts("0");
  }
  return 0;
}
