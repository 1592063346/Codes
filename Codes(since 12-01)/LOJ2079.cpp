#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, q, ch[N][2], size[N], heavy[N], father[N], depth[N], top[N], dfn[N], adfn[N], number[N], dfn_cnt;
long long answer;

void dfs1(int u) {
  size[u] = 1;
  for (int i = 0; i < 2; ++i) {
    if (ch[u][i]) {
      depth[ch[u][i]] = depth[u] + 1;
      father[ch[u][i]] = u;
      dfs1(ch[u][i]);
      size[u] += size[ch[u][i]];
      if (size[ch[u][i]] > size[heavy[u]]) {
        heavy[u] = ch[u][i];
      }
    }
  }
  answer += heavy[u];
}

void dfs2(int u, int t) {
  top[u] = t;
  dfn[u] = ++dfn_cnt;
  adfn[dfn_cnt] = u;
  if (heavy[u]) {
    dfs2(heavy[u], t);
    for (int i = 0; i < 2; ++i) {
      if (ch[u][i] && ch[u][i] != heavy[u]) {
        dfs2(ch[u][i], ch[u][i]);
      }
    }
  }
}

void modify(int p, int v) {
  for (; p <= n; p += p & -p) {
    number[p] += v;
  }
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    result += number[p];
  }
  return result;
}

int query_subt_size(int u) {
  int l = dfn[u], r = dfn[u] + size[u] - 1;
  return query(r) - query(l - 1);
}

int jump(int u, int k) {
  while (1) {
    if (dfn[u] - dfn[top[u]] >= k) {
      return adfn[dfn[u] - k];
    } else {
      k -= dfn[u] - dfn[top[u]] + 1;
      u = father[top[u]];
    }
  }
}

void update(int u) {
  answer -= heavy[u];
  int subt_l = ch[u][0] ? query_subt_size(ch[u][0]) : 0;
  int subt_r = ch[u][1] ? query_subt_size(ch[u][1]) : 0;
  if (subt_l == subt_r && subt_l) {
    answer += heavy[u];
  } else if (subt_l != subt_r) {
    heavy[u] = subt_l > subt_r ? ch[u][0] : ch[u][1];
    answer += heavy[u];
  } else {
    heavy[u] = 0;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &ch[i][0], &ch[i][1]);
  }
  dfs1(1);
  dfs2(1, 1);
  printf("%lld\n", answer);
  for (int i = 1; i <= n; ++i) {
    modify(i, 1);
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    int x;
    scanf("%d", &x);
    modify(dfn[x], -1);
    int up = depth[x];
    while (up) {
      int l = 0, r = up, t = jump(x, up);
      while (l != r) {
        int mid = (l + r >> 1) + 1;
        if ((query_subt_size(jump(x, mid)) << 1) <= query_subt_size(t)) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }
      up = l;
      update(jump(x, l + 1));
      if (l == 0) {
        break;
      }
    }
    printf("%lld\n", answer);
  }
  return 0;
}
