#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m, h, a[N], b[N], minv[N << 2], addv[N << 2];

#define lo (o<<1)
#define ro (o<<1|1)

void build(int l, int r, int o) {
  if (l == r) {
    minv[o] = -l;
  } else {
    int mid = l + r >> 1;
    build(l, mid, lo);
    build(mid + 1, r, ro);
    minv[o] = min(minv[lo], minv[ro]);
  }
}

void add(int o, int v) {
  minv[o] += v;
  addv[o] += v;
}

void push_down(int o) {
  if (addv[o]) {
    add(lo, addv[o]);
    add(ro, addv[o]);
    addv[o] = 0;
  }
}

void modify(int l, int r, int o, int ql, int qr, int v) {
  if (ql <= l && r <= qr) {
    add(o, v);
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (ql <= mid) {
      modify(l, mid, lo, ql, qr, v);
    }
    if (qr > mid) {
      modify(mid + 1, r, ro, ql, qr, v);
    }
    minv[o] = min(minv[lo], minv[ro]);
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &h);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &b[i]);
  }
  sort(b + 1, b + 1 + m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  build(1, m, 1);
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    int p = lower_bound(b + 1, b + 1 + m, h - a[i]) - b;
    if (p <= m) {
      modify(1, m, 1, p, m, 1);
    }
    if (i > m) {
      p = lower_bound(b + 1, b + 1 + m, h - a[i - m]) - b;
      if (p <= m) {
        modify(1, m, 1, p, m, -1);
      }
    }
    answer += minv[1] >= 0;
  }
  printf("%d\n", answer);
  return 0;
}
