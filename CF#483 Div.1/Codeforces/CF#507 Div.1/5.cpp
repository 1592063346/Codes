#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

#define lo ch[o][0]
#define ro ch[o][1]

int n, w, q, block, value[N], rmq_max[N][20], rmq_min[N][20], logv[N], ch[N][2], size[N], pa[N], go[N], ans[N];
vector<pair<int, int> > que;
vector<int> changed[N];

void rmq_init() {
  for (int i = 2; i <= n; ++i) {
    logv[i] = logv[i >> 1] + 1;
  }
  for (int j = 1; (1 << j) <= n; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
      rmq_max[i][j] = max(rmq_max[i][j - 1], rmq_max[i + (1 << j - 1)][j - 1]);
      rmq_min[i][j] = min(rmq_min[i][j - 1], rmq_min[i + (1 << j - 1)][j - 1]);
    }
  }
}

int diff(int l, int r) {
  int k = logv[r - l + 1];
  int maxv = max(rmq_max[l][k], rmq_max[r - (1 << k) + 1][k]);
  int minv = min(rmq_min[l][k], rmq_min[r - (1 << k) + 1][k]);
  return maxv - minv;
}

bool is_root(int o) {
  int p = pa[o];
  return ch[p][0] ^ o && ch[p][1] ^ o;
}

int side(int o, int p) {
  return ch[p][1] == o;
}

void push_up(int o) {
  size[o] = size[lo] + size[ro] + 1;
}

void rotate(int o) {
  int p = pa[o], to = side(o, p), topa = side(p, pa[p]), ano_ch = ch[o][to ^ 1];
  pa[o] = pa[p];
  if (!is_root(p)) {
    ch[pa[p]][topa] = o;
  }
  pa[ano_ch] = p;
  ch[p][to] = ano_ch;
  pa[p] = o;
  ch[o][to ^ 1] = p;
  push_up(p);
  push_up(o);
}

void splay(int o) {
  while (!is_root(o)) {
    int p = pa[o];
    if (!is_root(p)) {
      if (side(o, p) == side(p, pa[p])) {
        rotate(p);
      }
    }
    rotate(o);
  }
}

void access(int o) {
  for (int p = 0; o; p = o, o = pa[o]) {
    splay(o);
    ro = p;
    push_up(o);
  }
}

void link(int u, int v) {
  access(u);
  splay(u);
  pa[u] = v;
}

void cut(int u, int v) {
  access(u);
  splay(u);
  int l_ch = ch[u][0];
  ch[u][0] = pa[l_ch] = 0;
  push_up(u);
}

pair<int, int> query(int o) {
  access(o);
  splay(o);
  int result = 0, from = o;
  for (o = lo; o; from = o, o = lo) {
    result += 1 + size[ro];
  }
  return pair<int, int> (result, from);
}

int main() {
  scanf("%d%d%d", &n, &w, &q);
  block = (int) sqrt(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &value[i]);
    rmq_max[i][0] = rmq_min[i][0] = value[i];
  }
  rmq_init();
  for (int i = 1; i <= q; ++i) {
    int k;
    scanf("%d", &k);
    que.emplace_back(w - k, i);
  }
  sort(que.begin(), que.end());
  size[n + 1] = 1;
  for (int i = 1; i <= n; ++i) {
    go[i] = i + 1;
    size[i] = 1;
    link(i, i + 1);
    changed[0].push_back(i);
  }
  for (int i = 0; i < que.size(); ++i) {
    for (auto v : changed[i]) {
      cut(v, go[v]);
      if (go[v] - v <= block) {
        for (; go[v] <= n && diff(v, go[v]) <= que[i].first; ++go[v]);
        int pos = lower_bound(que.begin(), que.end(), pair<int, int> (diff(v, go[v]), 0)) - que.begin();
        cmax(pos, i + 1);
        changed[pos].push_back(v);
        if (go[v] - v <= block) {
          link(v, go[v]);
        }
      }
    }
    int o = 1, result = 0;
    while (o ^ n + 1) {
      pair<int, int> lct_s = query(o);
      if (!lct_s.first) {
        ++result;
        int l = o, r = n;
        while (l ^ r) {
          int mid = (l + r >> 1) + 1;
          if (diff(o, mid) <= que[i].first) {
            l = mid;
          } else {
            r = mid - 1;
          }
        }
        o = l + 1;
      } else {
        result += lct_s.first;
        o = lct_s.second;
      }
    }
    ans[que[i].second] = --result;
  }
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
