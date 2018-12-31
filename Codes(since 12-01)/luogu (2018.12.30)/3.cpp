#include<bits/stdc++.h>

using namespace std;

const int N = 6e5 + 10, max_node = N * 30;

int n, last, t, tt, a[N], father[N], len[N], c[N], sorted[N], root[N], lc[max_node], rc[max_node], sum[max_node];
long long sumpos[max_node];
map<int, int> ch[N];
vector<int> position;

int newnode(int from) {
  ++t;
  len[t] = len[from] + 1;
  return t;
}

void extend(int c) {
  int p = last, np = newnode(p);
  for (; p && !ch[p][c]; p = father[p]) {
    ch[p][c] = np;
  }
  if (!p) {
    father[np] = 1;
  } else {
    int q = ch[p][c];
    if (len[p] + 1 == len[q]) {
      father[np] = q;
    } else {
      int nq = newnode(p);
      ch[nq] = ch[q];
      father[nq] = father[q];
      father[np] = father[q] = nq;
      for (; p && ch[p][c] == q; p = father[p]) {
        ch[p][c] = nq;
      }
    }
  }
  last = np;
}

void radix_sort() {
  for (int i = 1; i <= t; ++i) {
    ++c[len[i]];
  }
  for (int i = 1; i <= n; ++i) {
    c[i] += c[i - 1];
  }
  for (int i = t; i; --i) {
    sorted[c[len[i]]--] = i;
  }
}

#define lo lc[o]
#define ro rc[o]

void modify(int l, int r, int& o, int p) {
  if (!o) {
    o = ++tt;
  }
  sum[o] += 1;
  sumpos[o] += p;
  if (l == r) {
    return;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, lo, p);
    } else {
      modify(mid + 1, r, ro, p);
    }
  }
}

int merge(int x, int y) {
  if (!x || !y) {
    return x | y;
  } else {
    int o = ++tt;
    lo = merge(lc[x], lc[y]);
    ro = merge(rc[x], rc[y]);
    sum[o] = sum[lo] + sum[ro];
    sumpos[o] = sumpos[lo] + sumpos[ro];
    return o;
  }
}

pair<int, long long> operator + (const pair<int, long long>& a, const pair<int, long long>& b) {
  return {a.first + b.first, a.second + b.second};
}

pair<int, long long> query(int l, int r, int o, int ql, int qr) {
  if (!o) {
    return {0, 0};
  }
  if (ql <= l && r <= qr) {
    return {sum[o], sumpos[o]};
  } else {
    int mid = l + r >> 1;
    pair<int, long long> result(0, 0);
    if (ql <= mid) {
      result = result + query(l, mid, lo, ql, qr);
    } if (qr > mid) {
      result = result + query(mid + 1, r, ro, ql, qr);
    }
    return result;
  }
}

void get_position(int l, int r, int o) {
  if (l == r) {
    position.push_back(l);
  } else {
    int mid = l + r >> 1;
    if (lo) {
      get_position(l, mid, lo);
    } if (ro) {
      get_position(mid + 1, r, ro);
    }
  }
}

int main() {
  len[0] = -1;
  last = newnode(0);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  long long answer = (long long)n * (n - 1) / 2;
  --n;
  for (int i = 1; i <= n; ++i) {
    a[i] = a[i + 1] - a[i];
    extend(a[i]);
    modify(1, n, root[last], i);
  }
  radix_sort();
  for (int i = t; i > 1; --i) {
    int u = sorted[i], p = father[u], from, to;
    if (sum[root[u]] < sum[root[p]]) {
      from = u;
      to = p;
    } else {
      from = p;
      to = u;
    }
    position.clear();
    get_position(1, n, root[from]);
    int l, r;
    for (auto v : position) {
      l = v + len[p] + 1;
      r = n;
      if (l <= r) {
        answer += (long long)query(1, n, root[to], l, r).first * len[p];
      }
      l = v + 2;
      r = min(v + len[p], n);
      if (l <= r) {
        pair<int, long long> result = query(1, n, root[to], l, r);
        answer += result.second - (long long)result.first * (v + 1);
      }
      l = 1;
      r = v - len[p] - 1;
      if (l <= r) {
        answer += (long long)query(1, n, root[to], l, r).first * len[p];
      }
      l = max(1, v - len[p]);
      r = v - 2;
      if (l <= r) {
        pair<int, long long> result = query(1, n, root[to], l, r);
        answer += (long long)result.first * (v - 1) - result.second;
      }
    }
    root[p] = merge(root[p], root[u]);
  }
  printf("%lld\n", answer);
  return 0;
}
