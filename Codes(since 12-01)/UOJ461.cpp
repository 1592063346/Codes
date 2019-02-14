#include<bits/stdc++.h>
#include "graph.h"

using namespace std;

const int N = 2e2 + 10;

int n, father[N], color[N];
vector<pair<int, int>> old;

void dfs(int u, int p) {
  father[u] = p;
  while (1) {
    vector<pair<int, int>> tmp = old;
    for (int i = 0; i < n; ++i) {
      if (!~color[i]) {
        tmp.emplace_back(u, i);
      }
    }
    if (query(tmp)) {
      break;
    }
    int l = old.size(), r = tmp.size() - 1;
    while (l != r) {
      int mid = l + r >> 1;
      vector<pair<int, int>> tmp2 = tmp;
      tmp2.resize(mid + 1);
      if (!query(tmp2)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    int v = tmp[l].second;
    color[v] = !color[u];
    dfs(v, u);
  }
  for (int i = 0; i < n; ++i) {
    if (!~color[i]) {
      old.emplace_back(u, i);
    }
  }
}

vector<int> check_bipartite(int vsize) {
  n = vsize;
  memset(color, -1, sizeof color);
  color[0] = 0;
  dfs(0, -1);
  vector<pair<int, int>> check;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (color[i] != color[j] && father[i] != j && father[j] != i) {
        check.emplace_back(i, j);
      }
    }
  }
  for (int i = 1; i < n; ++i) {
    check.emplace_back(i, father[i]);
    if (query(check)) {
      return vector<int>(0);
    }
    check.pop_back();
  }
  vector<int> result;
  for (int i = 0; i < n; ++i) {
    if (!color[i]) {
      result.push_back(i);
    }
  }
  return result;
}
