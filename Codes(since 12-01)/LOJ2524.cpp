#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

int tt, n, m, nodes, edges, dfn[N], adfn[N], low[N], size[N], belong[N], sub[N], cut_num[N], dfn_cnt;
vector<int> graph[N];
char color[N];
bool tag[N];

void tarjan(int u, int father) {
  dfn[u] = low[u] = ++dfn_cnt;
  adfn[dfn_cnt] = u;
  size[u] = (color[u] == '1');
  sub[u] = 0;
  tag[u] = true;
  cut_num[u] = 0;
  for (auto v : graph[u]) {
    if (v != father) {
      if (!dfn[v]) {
        tarjan(v, u);
        size[u] += size[v];
        cmin(low[u], low[v]);
        if (low[v] >= dfn[u]) {
          ++cut_num[u];
          sub[u] += size[v];
          tag[u] &= !(size[v] & 1);
        }
      } else if (dfn[v] < dfn[u]) {
        cmin(low[u], dfn[v]);
      }
    }
  }
  if (!father) {
    --cut_num[u];
  }
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
      graph[i].clear();
      dfn[i] = 0;
    }
    for (int i = 1; i <= m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      graph[u].push_back(v);
      graph[v].push_back(u);
    }
    scanf("%s", color + 1);
    dfn_cnt = 0;
    int number = 0, odd = 0;
    for (int i = 1; i <= n; ++i) {
      if (!dfn[i]) {
        ++number;
        int last = dfn_cnt;
        tarjan(i, 0);
        if (size[i] & 1) {
          ++odd;
        }
        for (int j = last + 1; j <= dfn_cnt; ++j) {
          belong[adfn[j]] = i;
        }
      }
    }
    int answer_p = m - n + number;
    printf("%d ", odd ? 0 : qpow(2, answer_p));
    for (int i = 1; i <= n; ++i) {
      if (!graph[i].size()) {
        if (odd - (size[i] & 1) == 0) {
          printf("%d%c", qpow(2, answer_p), " \n"[i == n]);
        } else {
          printf("0%c", " \n"[i == n]);
        }
      } else {
        if (tag[i] && !(size[belong[i]] - (color[i] == '1') - sub[i] & 1) && odd - (size[belong[i]] & 1) == 0) {
          printf("%d%c", qpow(2, answer_p - graph[i].size() + 1 + cut_num[i]), " \n"[i == n]);
        } else {
          printf("0%c", " \n"[i == n]);
        }
      }
    }
  }
  return 0;
}
