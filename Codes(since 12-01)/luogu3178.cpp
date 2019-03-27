#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, q, tt, a[N], dfn[N], edfn[N], coef[N << 2];
long long sum[N << 2], addv[N << 2];
vector<int> adj[N];

void pull(int o) {
  sum[o] = sum[o << 1] + sum[o << 1 | 1];
  coef[o] = coef[o << 1] + coef[o << 1 | 1];
}

void add(int o, long long v) {
  sum[o] += coef[o] * v;
  addv[o] += v;
}

void push(int o) {
  if (addv[o]) {
    add(o << 1, addv[o]);
    add(o << 1 | 1, addv[o]);
    addv[o] = 0;
  }
}

void modify(int l, int r, int o, int ql, int qr, int v, int c = 0) {
  if (ql <= l && r <= qr) {
    if (c) {
      coef[o] = c;
    }
    add(o, v);
  } else {
    int mid = l + r >> 1;
    push(o);
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr, v, c);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr, v, c);
    } else {
      modify(l, mid, o << 1, ql, qr, v, c);
      modify(mid + 1, r, o << 1 | 1, ql, qr, v, c);
    }
    pull(o);
  }
}

long long query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return sum[o];
  } else {
    int mid = l + r >> 1;
    push(o);
    if (qr <= mid) {
      return query(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      return query(l, mid, o << 1, ql, qr) + query(mid + 1, r, o << 1 | 1, ql, qr);
    }
  }
}

void dfs(int u, int p) {
  dfn[u] = ++tt;
  modify(1, n << 1, 1, tt, tt, a[u], 1);
  for (auto v : adj[u]) {
    if (v != p) {
      dfs(v, u);
    }
  }
  edfn[u] = ++tt;
  modify(1, n << 1, 1, tt, tt, a[u], -1);
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 0);
  while (q--) {
    int opt, a, b;
    scanf("%d", &opt);
    switch (opt) {
      case 1:
        scanf("%d%d", &a, &b);
        modify(1, n << 1, 1, dfn[a], dfn[a], b);
        modify(1, n << 1, 1, edfn[a], edfn[a], b);
        break;
      case 2:
        scanf("%d%d", &a, &b);
        modify(1, n << 1, 1, dfn[a], edfn[a], b);
        break;
      case 3:
        scanf("%d", &a);
        printf("%lld\n", query(1, n << 1, 1, 1, dfn[a]));
        break;
    }
  }
  return 0;
}
