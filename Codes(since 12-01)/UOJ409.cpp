#include<bits/stdc++.h>
#include "highway.h"

using namespace std;

const int N = 9e4 + 10;

vector<pair<int, int>> graph[N];
vector<int> sa, sb, used, tree;
int visit[N], ban[N];

int find(vector<int>& nodes, vector<int>& u, vector<int>& v, long long should) {
  int l = 0, r = nodes.size() - 1;
  while (l != r) {
    int mid = l + r >> 1;
    fill(used.begin(), used.end(), 1);
    memset(ban, 0, sizeof ban);
    for (int i = mid + 1; i < nodes.size(); ++i) {
      ban[nodes[i]] = 1;
    }
    for (auto e : tree) {
      if (!ban[u[e]] && !ban[v[e]]) {
        used[e] = 0;
      }
    }
    if (ask(used) == should) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  return nodes[l];
}

void find_pair(int n, vector<int> u, vector<int> v, int a, int b) {
  int m = u.size();
  for (int i = 0; i < m; ++i) {
    int x = u[i];
    int y = v[i];
    graph[x].emplace_back(y, i);
    graph[y].emplace_back(x, i);
  }
  used.resize(m);
  int dist = ask(used) / a;
  int l = 0, r = m - 1;
  while (l != r) {
    int mid = l + r >> 1;
    fill(used.begin(), used.end(), 0);
    for (int i = 0; i <= mid; ++i) {
      used[i] = 1;
    }
    if (ask(used) == (long long) dist * a) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  int c = u[l], d = v[l];
  tree.push_back(l);
  queue<int> que;
  que.push(c);
  que.push(d);
  visit[c] = 1;
  visit[d] = 2;
  sa.push_back(c);
  sb.push_back(d);
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (auto y : graph[x]) {
      if (!visit[y.first]) {
        tree.push_back(y.second);
        if (visit[x] == 1) {
          visit[y.first] = 1;
          sa.push_back(y.first);
        } else {
          visit[y.first] = 2;
          sb.push_back(y.first);
        }
        que.push(y.first);
      }
    }
  }
  answer(find(sa, u, v, (long long) dist * a), find(sb, u, v, (long long) dist * a));
}
