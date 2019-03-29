#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m, t, tt, a[N], pre[N];
set<pair<pair<int, int>, int>> all;
set<pair<int, int>> any[N];
map<int, int> id;

struct node_t {
  int l, r, sum;
} nodes[N * 80];

struct segment_t {
  int root;

  void insert(int l, int r, int& o, int x, int y) {
    if (!o) {
      o = ++t;
    }
    nodes[o].sum += y;
    if (l != r) {
      int mid = l + r >> 1;
      if (x <= mid) {
        insert(l, mid, nodes[o].l, x, y);
      } else {
        insert(mid + 1, r, nodes[o].r, x, y);
      }
    }
  }

  int query(int l, int r, int o, int ql, int qr) {
    if (!o) {
      return 0;
    }
    if (ql <= l && r <= qr) {
      return nodes[o].sum;
    } else {
      int mid = l + r >> 1;
      if (qr <= mid) {
        return query(l, mid, nodes[o].l, ql, qr);
      } else if (ql > mid) {
        return query(mid + 1, r, nodes[o].r, ql, qr);
      } else {
        return query(l, mid, nodes[o].l, ql, qr) + query(mid + 1, r, nodes[o].r, ql, qr);
      }
    }
  }
} tree[N];

void modify(int p, int x, int y) {
  for (; p <= n; p += p & -p) {
    tree[p].insert(0, n - 1, tree[p].root, x, y);
  }
}

int query(int p, int x) {
  int result = 0;
  for (; p; p -= p & -p) {
    result += tree[p].query(0, n - 1, tree[p].root, 0, x);
  }
  return result;
}

int query(int l, int r, int x) {
  return query(r, x) - query(l - 1, x);
}

void split(int p) {
  if (p > n) {
    return;
  }
  set<pair<pair<int, int>, int>>:: iterator i = --all.lower_bound(make_pair(make_pair(p + 1, 0), 0));
  if ((*i).first.first == p) {
    return;
  } else {
    pair<int, int> seg = (*i).first;
    int color = (*i).second;
    all.erase({seg, color});
    any[color].erase(seg);
    all.emplace(make_pair(seg.first, p - 1), color);
    all.emplace(make_pair(p, seg.second), color);
    any[color].emplace(seg.first, p - 1);
    any[color].emplace(p, seg.second);
  }
}

void update(int p, int x) {
  modify(p, pre[p], -1);
  pre[p] = x;
  modify(p, pre[p], 1);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    if (!id[a[i]]) {
      id[a[i]] = ++tt;
      any[tt].emplace(0, 0);
    }
    a[i] = id[a[i]];
    pre[i] = (*--any[a[i]].end()).first;
    modify(i, pre[i], 1);
    any[a[i]].emplace(i, i);
    all.emplace(make_pair(i, i), a[i]);
  }
  while (m--) {
    int opt, l, r, x;
    scanf("%d", &opt);
    if (opt == 1) {
      scanf("%d%d%d", &l, &r, &x);
      if (!id[x]) {
        id[x] = ++tt;
        any[tt].emplace(0, 0);
      }
      x = id[x];
      split(l);
      split(r + 1);
      vector<int> colors;
      while (1) {
        set<pair<pair<int, int>, int>>:: iterator p = all.lower_bound(make_pair(make_pair(l, 0), 0));
        if (p == all.end() || (*p).first.first > r) {
          break;
        }
        int ll = (*p).first.first;
        if (ll > l && pre[ll] != ll - 1) {
          update(ll, ll - 1);
        }
        pair<pair<int, int>, int> seg = *p;
        colors.push_back(seg.second);
        all.erase(seg);
        any[seg.second].erase(seg.first);
      }
      for (auto c : colors) {
        set<pair<int, int>>:: iterator i = any[c].upper_bound(make_pair(l, r)), j = i;
        if (i != any[c].end()) {
          update((*i).first, (*--j).second);
        }
      }
      set<pair<int, int>>:: iterator i = any[x].upper_bound(make_pair(l, r)), j = i;
      if (i != any[x].end()) {
        update((*i).first, r);
      }
      update(l, (*--j).second);
      all.emplace(make_pair(l, r), x);
      any[x].emplace(l, r);
    } else {
      scanf("%d%d", &l, &r);
      printf("%d\n", query(l, r, l - 1));
    }
  }
  return 0;
}
