#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const long long inf = 1e15;

int n, a0[N], a1[N], root[N], ch[N * 20][2], node_cnt;
long long k[N * 20], b[N * 20], answer[N];
vector<int> graph[N];

long long get_y(long long k, long long b, int x) {
  return (long long) k * x + b;
}

void modify(int l, int r, int& o, long long tk, long long tb) {
  if (!o) {
    o = ++node_cnt;
    k[o] = tk;
    b[o] = tb;
    return;
  } else if (get_y(k[o], b[o], l) >= get_y(tk, tb, l) && get_y(k[o], b[o], r) >= get_y(tk, tb, r)) {
    k[o] = tk;
    b[o] = tb;
    return;
  } else if (get_y(k[o], b[o], l) <= get_y(tk, tb, l) && get_y(k[o], b[o], r) <= get_y(tk, tb, r)) {
    return;
  } else {
    int mid = l + r >> 1;
    if (get_y(k[o], b[o], mid) <= get_y(tk, tb, mid)) {
      if (get_y(k[o], b[o], l) <= get_y(tk, tb, l)) {
        modify(mid + 1, r, ch[o][1], tk, tb);
      } else {
        modify(l, mid, ch[o][0], tk, tb);
      }
    } else {
      if (get_y(k[o], b[o], r) >= get_y(tk, tb, r)) {
        modify(l, mid, ch[o][0], k[o], b[o]);
      } else {
        modify(mid + 1, r, ch[o][1], k[o], b[o]);
      }
      k[o] = tk;
      b[o] = tb;
    }
  }
}

long long query(int l, int r, int o, int p) {
  if (!o) {
    return inf;
  }
  long long result = get_y(k[o], b[o], p);
  if (l == r) {
    return result;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      return min(result, query(l, mid, ch[o][0], p));
    } else {
      return min(result, query(mid + 1, r, ch[o][1], p));
    }
  }
}

int merge(int l, int r, int x, int y) {
  if (!x || !y) {
    return x | y;
  } else {
    int mid = l + r >> 1;
    ch[x][0] = merge(l, mid, ch[x][0], ch[y][0]);
    ch[x][1] = merge(mid + 1, r, ch[x][1], ch[y][1]);
    modify(l, r, x, k[y], b[y]);
    return x;
  }
}

void dfs(int u, int father) {
  bool go = false;
  for (auto v : graph[u]) {
    if (v != father) {
      go = true;
      dfs(v, u);
      root[u] = merge(-1e5, 1e5, root[u], root[v]);
    }
  }
  answer[u] = go ? query(-1e5, 1e5, root[u], a0[u]) : 0;
  modify(-1e5, 1e5, root[u], a1[u], answer[u]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a0[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a1[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; ++i) {
    printf("%lld%c", answer[i], " \n"[i == n]);
  }
  return 0;
}
