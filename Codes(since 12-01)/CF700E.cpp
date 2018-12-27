#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, t, tt, last, ch[N][26], father[N], len[N], c[N], sorted[N], dp[N], root[N], lc[N * 20], rc[N * 20], pre[N];
char s[N];

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
      memcpy(ch[nq], ch[q], sizeof ch[q]);
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

int sum[N * 20];

void modify(int l, int r, int& o, int p) {
  if (!o) {
    o = ++tt;
  }
  if (l == r) {
    sum[o] = 1;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, lo, p);
    } else {
      modify(mid + 1, r, ro, p);
    }
    sum[o] = sum[lo] + sum[ro];
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
    return o;
  }
}

int query(int l, int r, int o, int ql, int qr) {
  if (!o) {
    return 0;
  }
  if (ql <= l && r <= qr) {
    return sum[o];
  } else {
    int mid = l + r >> 1, result = 0;
    if (ql <= mid) {
      result += query(l, mid, lo, ql, qr);
    } if (qr > mid) {
      result += query(mid + 1, r, ro, ql, qr);
    }
    return result;
  }
}

int find(int l, int r, int o) {
  if (l == r) {
    return l;
  } else {
    int mid = l + r >> 1;
    if (sum[lo]) {
      return find(l, mid, lo);
    } else {
      return find(mid + 1, r, ro);
    }
  }
}

int main() {
  len[0] = -1;
  last = newnode(0);
  scanf("%d%s", &n, s);
  for (int i = 0; i < n; ++i) {
    extend(s[i] - 'a');
    modify(0, n - 1, root[last], i);
  }
  radix_sort();
  for (int i = t; i > 1; --i) {
    int u = sorted[i];
    root[father[u]] = merge(root[father[u]], root[u]);
  }
  int answer = 0;
  for (int i = 2; i <= t; ++i) {
    int u = sorted[i];
    if (father[u] == 1) {
      pre[u] = u;
      dp[u] = 1;
    } else {
      int pos = find(0, n - 1, root[u]);
      if (query(0, n - 1, root[pre[father[u]]], pos - len[u] + len[pre[father[u]]], pos) >= 2) {
        pre[u] = u;
        dp[u] = dp[father[u]] + 1;
      } else {
        pre[u] = pre[father[u]];
        dp[u] = dp[father[u]];
      }
    }
    cmax(answer, dp[u]);
  }
  printf("%d\n", answer);
  return 0;
}
