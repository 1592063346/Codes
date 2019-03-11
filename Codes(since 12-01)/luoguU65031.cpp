#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, size[N], heavy[N], father[N], length[N];
long long answer, part1, part2;
vector<int> adj[N];
set<int> subtree;
bool appeared[N];

long long s(int x) {
  return (long long) x * (x + 1) >> 1;
}

void reset() {
  subtree.clear();
  subtree.insert(0);
  subtree.insert(n + 1);
  part1 = 0;
  part2 = s(n);
}

void dfs1(int u, int p) {
  size[u] = 1;
  for (auto v : adj[u]) {
    if (v != p) {
      dfs1(v, u);
      size[u] += size[v];
      if (size[v] > size[heavy[u]]) {
        heavy[u] = v;
      }
    }
  }
}

int find(int x) {
  return father[x] == x ? x : father[x] = find(father[x]);
}

void merge(int u, int v) {
  part1 += (long long) length[u] * length[v];
  father[u] = v;
  length[v] += length[u];
}

void update(int u) {
  subtree.insert(u);
  set<int>:: iterator l = subtree.find(u), r = l;
  --l;
  ++r;
  part2 -= s(*r - *l - 1);
  part2 += s(u - *l - 1);
  part2 += s(*r - u - 1);
  ++part1;
  appeared[u] = true;
  if (appeared[u - 1]) {
    int x = find(u - 1), y = find(u);
    merge(x, y);
  }
  if (appeared[u + 1]) {
    int x = find(u + 1), y = find(u);
    merge(x, y);
  }
}

void add_tag(int u, int p, int ban) {
  update(u);
  for (auto v : adj[u]) {
    if (v != p && v != ban) {
      add_tag(v, u, ban);
    }
  }
}

void del_tag(int u, int p) {
  appeared[u] = false;
  father[u] = u;
  length[u] = 1;
  for (auto v : adj[u]) {
    if (v != p) {
      del_tag(v, u);
    }
  }
}

void dfs2(int u, int p, bool retain = false) {
  for (auto v : adj[u]) {
    if (v != p && v != heavy[u]) {
      dfs2(v, u);
    }
  }
  if (heavy[u]) {
    dfs2(heavy[u], u, true);
  }
  add_tag(u, p, heavy[u]);
  answer += s(n) - part1 - part2;
  if (!retain) {
    del_tag(u, p);
    reset();
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    father[i] = i;
    length[i] = 1;
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs1(1, 0);
  reset();
  dfs2(1, 0, true);
  printf("%lld\n", answer);
  return 0;
}
