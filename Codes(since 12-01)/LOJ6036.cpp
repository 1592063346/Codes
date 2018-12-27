#include<bits/stdc++.h>

using namespace std;

const int N = 3e6 + 10;

int n, id[N], idx[N], pre[N], ch[N][2], node_cnt, trie_t, dfn[N], low[N], scc[N], scc_cnt, dfn_cnt;
vector<int> graph[N], pstack;

struct string_t {
  string s;

  bool operator < (const string_t& a) const {
    return s.length() < a.s.length();
  }
} str[N];

void add_edge(int u, int v) {
  graph[u].push_back(v);
  graph[v ^ 1].push_back(u ^ 1);
}

void tarjan(int u) {
  dfn[u] = low[u] = ++dfn_cnt;
  pstack.push_back(u);
  for (auto v : graph[u]) {
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (!scc[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    ++scc_cnt;
    while (1) {
      int x = pstack.back();
      pstack.pop_back();
      scc[x] = scc_cnt;
      if (x == u) {
        break;
      }
    }
  }
}

void add_pre(int p, int now_p, int now) {
  add_edge(now_p << 1, p << 1);
  add_edge(p << 1 | 1, now ^ 1);
}

void insert(string s, int now) {
  int len = s.length(), o = 0;
  int pre_id = ++node_cnt;
  for (int i = 0; i < len; ++i) {
    int c = s[i] - '0';
    if (!ch[o][c]) {
      ch[o][c] = ++trie_t;
    }
    o = ch[o][c];
    if (idx[o]) {
      add_pre(pre[o], pre_id, now);
    }
  }
  idx[o] = now;
  pre[o] = pre_id;
  add_edge(now, pre[o] << 1 | 1);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    cin >> str[i].s;
  }
  sort(str + 1, str + 1 + n);
  for (int i = 1; i <= n; ++i) {
    id[i] = ++node_cnt;
    int pos = str[i].s.find('?');
    if (pos >= 0 && pos < str[i].s.length()) {
      str[i].s[pos] = '0';
      insert(str[i].s, id[i] << 1);
      str[i].s[pos] = '1';
      insert(str[i].s, id[i] << 1 | 1);
    } else {
      insert(str[i].s, id[i] << 1);
      insert(str[i].s, id[i] << 1 | 1);
    }
  }
  for (int i = 2; i <= node_cnt << 1; ++i) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }
  bool fail = false;
  for (int i = 1; i <= n; ++i) {
    if (scc[id[i] << 1] == scc[id[i] << 1 | 1]) {
      fail = true;
    }
  }
  puts(fail ? "NO" : "YES");
  return 0;
}
