#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, max_node = N * 26;

int n, q, block, ch[N][26], father[N], c[max_node], heavy[max_node], dfn[max_node], top[max_node], size[max_node], node_cnt, dfn_cnt;
long long g[N], answer[N];
char str[N];
vector<int> id[N], graph[max_node];
vector<pair<pair<int, int>, int>> info1[N], info2[N];

void insert(int x) {
  scanf("%s", str);
  int len = strlen(str), o = 0;
  id[x].resize(len);
  for (int i = 0; i < len; ++i) {
    int c = str[i] - 'a';
    if (!ch[o][c]) {
      ch[o][c] = ++node_cnt;
    }
    o = ch[o][c];
    id[x][i] = o;
  }
}

void get_fail() {
  queue<int> que;
  for (int i = 0; i < 26; ++i) {
    if (ch[0][i]) {
      que.push(ch[0][i]);
    }
  }
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (int i = 0; i < 26; ++i) {
      int& u = ch[x][i];
      if (!u) {
        u = ch[father[x]][i];
      } else {
        father[u] = ch[father[x]][i];
        que.push(u);
      }
    }
  }
}

void dfs1(int u) {
  size[u] = 1;
  heavy[u] = -1;
  for (auto v : graph[u]) {
    dfs1(v);
    size[u] += size[v];
    if (!~heavy[u] || size[v] > size[heavy[u]]) {
      heavy[u] = v;
    }
  }
}

void dfs2(int u, int t) {
  dfn[u] = ++dfn_cnt;
  top[u] = t;
  if (~heavy[u]) {
    dfs2(heavy[u], t);
    for (auto v : graph[u]) {
      if (v != heavy[u]) {
        dfs2(v, v);
      }
    }
  }
}

void modify(int p, int v) {
  for (; p <= dfn_cnt; p += p & -p) {
    c[p] += v;
  }
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    result += c[p];
  }
  return result;
}

int query(int l, int r) {
  return query(r) - query(l - 1);
}

int jump(int u) {
  int result = 0;
  for (; ~u; u = father[top[u]]) {
    result += query(dfn[top[u]], dfn[u]);
  }
  return result;
}

int main() {
  scanf("%d%d", &n, &q);
  int all = 0;
  for (int i = 1; i <= n; ++i) {
    insert(i);
    all += id[i].size();
  }
  block = (int) sqrt(all);
  get_fail();
  for (int i = 1; i <= node_cnt; ++i) {
    graph[father[i]].push_back(i);
  }
  father[0] = -1;
  dfs1(0);
  dfs2(0, 0);
  for (int i = 1; i <= q; ++i) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    if (id[k].size() <= block) {
      info1[l - 1].emplace_back(make_pair(i, k), -1);
      info1[r].emplace_back(make_pair(i, k), 1);
    } else {
      info2[k].emplace_back(make_pair(l - 1, r), i);
    }
  }
  for (int i = 1; i <= n; ++i) {
    modify(dfn[id[i][id[i].size() - 1]], 1);
    for (auto v : info1[i]) {
      for (auto o : id[v.first.second]) {
        answer[v.first.first] += v.second * jump(o);
      }
    }
  }
  memset(c, 0, sizeof c);
  for (int i = 1; i <= n; ++i) {
    if (info2[i].size()) {
      for (auto o : id[i]) {
        modify(dfn[o], 1);
      }
      for (int j = 1; j <= n; ++j) {
        int o = id[j][id[j].size() - 1];
        g[j] = g[j - 1] + query(dfn[o], dfn[o] + size[o] - 1);
      }
      for (auto v : info2[i]) {
        answer[v.second] -= g[v.first.first];
        answer[v.second] += g[v.first.second];
      }
      for (auto o : id[i]) {
        modify(dfn[o], -1);
      }
    }
  }
  for (int i = 1; i <= q; ++i) {
    printf("%I64d\n", answer[i]);
  }
  return 0;
}
