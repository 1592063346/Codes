#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, M = 30010;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, m, len, dfn_t, father[N], id[N], p[N], d[N], dfn[N], dfn_out[N], tt, lazy_t[N], maxv[N], team[2010][M + 1], arr[N], total;
vector<int> graph[N];

void dfs(int u) {
  dfn[u] = ++dfn_t;
  for (auto v : graph[u]) {
    dfs(v);
  }
  dfn_out[u] = dfn_t;
}

void add_new_team(int l, int r) {
  ++tt;
  int mind = 1e9, maxd = -1e9;
  for (int i = l; i < r; ++i) {
    id[i] = tt;
    cmin(mind, d[i]);
    cmax(maxd, d[i]);
  }
  lazy_t[tt] = mind;
  int up = maxd - mind;
  maxv[tt] = up;
  for (int i = 0; i <= up; ++i) {
    team[tt][i] = 0;
  }
  for (int i = l; i < r; ++i) {
    d[i] -= mind;
    ++team[tt][d[i]];
  }
  for (int i = 1; i <= up; ++i) {
    team[tt][i] += team[tt][i - 1];
  }
}

void modify(int l, int r, int add) {
  for (int i = id[l]; i <= id[r]; ++i) {
    if (i != id[l] && i != id[r]) {
      lazy_t[i] += add;
      continue;
    }
    int tl, tr;
    int mind = 1e9, maxd = -1e9;
    if (i == id[l] && id[l] == id[r]) {
      tl = l, tr = r;
      for (int j = l; j <= r; ++j) {
        d[j] += lazy_t[i] + add;
        cmin(mind, d[j]);
        cmax(maxd, d[j]);
      }
      for (int j = l - 1; j && id[j] == i; --j) {
        tl = j;
        d[j] += lazy_t[i];
        cmin(mind, d[j]);
        cmax(maxd, d[j]);
      }
      for (int j = r + 1; j <= n && id[j] == i; ++j) {
        tr = j;
        d[j] += lazy_t[i];
        cmin(mind, d[j]);
        cmax(maxd, d[j]);
      }
    } else if (i == id[l]) {
      tl = tr = l;
      for (int j = l; j <= n && id[j] == i; ++j) {
        tr = j;
        d[j] += lazy_t[i] + add;
        cmin(mind, d[j]);
        cmax(maxd, d[j]);
      }
      for (int j = l - 1; j && id[j] == i; --j) {
        tl = j;
        d[j] += lazy_t[i];
        cmin(mind, d[j]);
        cmax(maxd, d[j]);
      }
    } else {
      tl = tr = r;
      for (int j = r; j && id[j] == i; --j) {
        tl = j;
        d[j] += lazy_t[i] + add;
        cmin(mind, d[j]);
        cmax(maxd, d[j]);
      }
      for (int j = r + 1; j <= n && id[j] == i; ++j) {
        tr = j;
        d[j] += lazy_t[i];
        cmin(mind, d[j]);
        cmax(maxd, d[j]);
      }
    }
    int up = maxd - mind;
    maxv[i] = maxd - mind;
    for (int j = 0; j <= up; ++j) {
      team[i][j] = 0;
    }
    lazy_t[i] = mind;
    for (int j = tl; j <= tr; ++j) {
      d[j] -= mind;
      ++team[i][d[j]];
    }
    for (int j = 1; j <= up; ++j) {
      team[i][j] += team[i][j - 1];
    }
  }
}

void rebuild() {
  for (int i = 1; i <= n; ++i) {
    d[i] += lazy_t[id[i]];
  }
  tt = 0;
  int mind = 1e9, maxd = -1e9;
  for (int l = 1, r = 1; r <= n + 1; ++r) {
    if (r <= n) {
      cmin(mind, d[r]);
      cmax(maxd, d[r]);
    }
    if (maxd - mind > 3000 || r - l > 300 || r == n + 1) {
      add_new_team(l, r);
      mind = d[r];
      maxd = d[r];
      l = r;
    }
  }
}

int get_num(int l, int r, int v) {
  int result = 0;
  for (int i = id[l]; i <= id[r]; ++i) {
    if (i == id[l]) {
      for (int j = l; j <= r && id[j] == id[l]; ++j) {
        result += (d[j] + lazy_t[i] <= v);
      }
    } else if (i == id[r]) {
      for (int j = r; j && id[j] == id[r]; --j) {
        result += (d[j] + lazy_t[i] <= v);
      }
    } else {
      if (v - lazy_t[i] >= 0) {
        result += team[i][min(v - lazy_t[i], maxv[i])];
      }
    }
  }
  return result;
}

int main() {
  scanf("%d%d%*d", &n, &m);
  for (int i = 2; i <= n; ++i) {
    scanf("%d%d", &father[i], &p[i]);
    p[i] += p[father[i]];
    graph[father[i]].push_back(i);
  }
  dfs(1);
  for (int i = 1; i <= n; ++i) {
    d[dfn[i]] = p[i];
  }
  rebuild();
  int update_total = 0;
  while (m--) {
    int opt, x, k;
    scanf("%d%d%d", &opt, &x, &k);
    if (opt == 1) {
      if (dfn_out[x] - dfn[x] + 1 < k) {
        puts("-1");
      } else {
        int l = 0, r = 2e6;
        while (l != r) {
          int mid = l + r >> 1;
          if (get_num(dfn[x], dfn_out[x], mid) >= k) {
            r = mid;
          } else {
            l = mid + 1;
          }
        }
        printf("%d\n", l);
      }
    } else {
      modify(dfn[x], dfn_out[x], k);
      if (++update_total % 1500 == 0) {
        rebuild();
      }
    }
  }
  return 0;
}
