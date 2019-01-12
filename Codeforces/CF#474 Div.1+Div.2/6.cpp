#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, a[N], b[N], w[N], h[N], root[N], lo[N * 100], ro[N * 100], maxv[N * 100], tt;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int query(int l, int r, int o, int ql, int qr) {
  if (!o) {
    return 0;
  }
  if (ql <= l && r <= qr) {
    return maxv[o];
  } else {
    int mid = l + r >> 1, result = 0;
    if (ql <= mid) {
      cmax(result, query(l, mid, lo[o], ql, qr));
    }
    if (qr > mid) {
      cmax(result, query(mid + 1, r, ro[o], ql, qr));
    }
    return result;
  }
}

void modify(int l, int r, int& o, int p, int v) {
  if (!o) {
    o = ++tt;
  }
  if (l == r) {
    cmax(maxv[o], v);
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, lo[o], p, v);
    } else {
      modify(mid + 1, r, ro[o], p, v);
    }
    maxv[o] = max(maxv[lo[o]], maxv[ro[o]]);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &a[i], &b[i], &w[i]);
    h[i] = w[i];
  }
  sort(h + 1, h + 1 + m);
  int c = unique(h + 1, h + 1 + m) - h - 1;
  int answer = 0;
  for (int i = m; i; --i) {
    w[i] = lower_bound(h + 1, h + 1 + c, w[i]) - h;
    int f = w[i] < c ? query(1, c, root[b[i]], w[i] + 1, c) + 1 : 1;
    cmax(answer, f);
    modify(1, c, root[a[i]], w[i], f);
  }
  printf("%d\n", answer);
  return 0;
}
