#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10;

int k, n, father[N], ch[N][100], node_cnt, dfn_cnt, dfn[N], edfn[N], array1[N], array2[N], answer[N];
vector<int> graph[N];
vector<pair<int, int>> queries[N], mem[N];
char s[N], str[N];

void get_fail() {
  queue<int> que;
  for (int i = 0; i < 94; ++i) {
    if (ch[0][i]) {
      que.push(ch[0][i]);
    }
  }
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (int i = 0; i < 94; ++i) {
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

void dfs(int u) {
  dfn[u] = ++dfn_cnt;
  for (auto v : graph[u]) {
    dfs(v);
  }
  edfn[u] = dfn_cnt;
}

struct fenwick_tree {
  int c[N];

  void modify(int p, int v) {
    for (; p <= node_cnt + 1; p += p & -p) {
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
} tree[2];

void solve(int u) {
  for (auto s : queries[u]) {
    if (s.first > 0) {
      answer[s.first] -= tree[1].query(dfn[s.second], edfn[s.second]);
    } else {
      answer[-s.first] += tree[0].query(dfn[s.second], edfn[s.second]);
    }
  }
  for (auto s : mem[u]) {
    if (s.first < 0) {
      tree[0].modify(dfn[s.second], 1);
    } else {
      tree[1].modify(dfn[s.second], 1);
    }
  }
  for (auto v : graph[u]) {
    solve(v);
  }
  for (auto s : queries[u]) {
    if (s.first > 0) {
      answer[s.first] += tree[1].query(dfn[s.second], edfn[s.second]);
    } else {
      answer[-s.first] -= tree[0].query(dfn[s.second], edfn[s.second]);
    }
  }
}

int main() {
  scanf("%d%s%d", &k, s, &n);
  int lens = strlen(s);
  for (int tt = 1; tt <= n; ++tt) {
    scanf("%s", str);
    int len = strlen(str), u = 0;
    array1[0] = 0;
    array2[len + 1] = 0;
    for (int i = 0; i < len; ++i) {
      int c = str[i] - 33;
      if (!ch[u][c]) {
        ch[u][c] = ++node_cnt;
      }
      u = ch[u][c];
      array1[i + 1] = u;
    }
    u = 0;
    for (int i = len - 1; ~i; --i) {
      int c = str[i] - 33;
      if (!ch[u][c]) {
        ch[u][c] = ++node_cnt;
      }
      u = ch[u][c];
      array2[i + 1] = u;
    }
    for (int i = 0; i + k <= len; ++i) {
      queries[array1[i]].emplace_back(tt, array2[i + k + 1]);
    }
    for (int i = 1; i + k <= len; ++i) {
      queries[array1[i]].emplace_back(-tt, array2[i + k]);
    }
    if (len < k) {
      answer[tt] = lens - len + 1;
    }
  }
  get_fail();
  for (int i = 1; i <= node_cnt; ++i) {
    graph[father[i]].push_back(i);
  }
  dfs(0);
  int u = 0;
  array1[0] = 0;
  array2[lens + 1] = 0;
  for (int i = 0; i < lens; ++i) {
    int c = s[i] - 33;
    u = ch[u][c];
    array1[i + 1] = u;
  }
  u = 0;
  for (int i = lens - 1; ~i; --i) {
    int c = s[i] - 33;
    u = ch[u][c];
    array2[i + 1] = u;
  }
  for (int i = 0; i + k <= lens; ++i) {
    mem[array1[i]].emplace_back(1, array2[i + k + 1]);
  }
  for (int i = 1; i + k <= lens; ++i) {
    mem[array1[i]].emplace_back(-1, array2[i + k]);
  }
  solve(0);
  for (int i = 1; i <= n; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
