#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

#define lo (o<<1)
#define ro (o<<1|1)

int n, q, a[N], minv[N << 2], maxv[N << 2], addv[N << 2];
long long sum[N << 2];

void add(int l, int r, int o, int v) {
  sum[o] += (long long) (r - l + 1) * v;
  minv[o] += v;
  maxv[o] += v;
  addv[o] += v;
}

void push_down(int l, int r, int o) {
  if (addv[o]) {
    int mid = l + r >> 1;
    add(l, mid, lo, addv[o]);
    add(mid + 1, r, ro, addv[o]);
    addv[o] = 0;
  }
}

void push_up(int o) {
  minv[o] = min(minv[lo], minv[ro]);
  maxv[o] = max(maxv[lo], maxv[ro]);
  sum[o] = sum[lo] + sum[ro];
}

void build(int l, int r, int o) {
  if (l == r) {
    minv[o] = maxv[o] = sum[o] = a[l];
  } else {
    int mid = l + r >> 1;
    build(l, mid, lo);
    build(mid + 1, r, ro);
    push_up(o);
  }
}

void modify_add(int l, int r, int o, int ql, int qr, int v) {
  if (ql <= l && r <= qr) {
    add(l, r, o, v);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (ql <= mid) {
      modify_add(l, mid, lo, ql, qr, v);
    }
    if (qr > mid) {
      modify_add(mid + 1, r, ro, ql, qr, v);
    }
    push_up(o);
  }
}

int integ_div(int x, int d) {
  if (x >= 0 || x % d == 0) {
    return x / d;
  } else {
    return x / d - 1;
  }
}

void modify_div(int l, int r, int o, int ql, int qr, int v) {
  if (ql <= l && r <= qr && minv[o] - integ_div(minv[o], v) == maxv[o] - integ_div(maxv[o], v)) {
    add(l, r, o, integ_div(minv[o], v) - minv[o]);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (ql <= mid) {
      modify_div(l, mid, lo, ql, qr, v);
    }
    if (qr > mid) {
      modify_div(mid + 1, r, ro, ql, qr, v);
    }
    push_up(o);
  }
}

long long query_sum(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return sum[o];
  } else {
    int mid = l + r >> 1;
    long long result = 0;
    push_down(l, r, o);
    if (ql <= mid) {
      result += query_sum(l, mid, lo, ql, qr);
    }
    if (qr > mid) {
      result += query_sum(mid + 1, r, ro, ql, qr);
    }
    return result;
  }
}

int query_min(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return minv[o];
  } else {
    int mid = l + r >> 1, result = INT_MAX;
    push_down(l, r, o);
    if (ql <= mid) {
      result = min(result, query_min(l, mid, lo, ql, qr));
    }
    if (qr > mid) {
      result = min(result, query_min(mid + 1, r, ro, ql, qr));
    }
    return result;
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  build(1, n, 1);
  while (q--) {
    int type, l, r, v;
    scanf("%d%d%d", &type, &l, &r);
    ++l;
    ++r;
    switch (type) {
      case 1:
        scanf("%d", &v);
        modify_add(1, n, 1, l, r, v);
        break;
      case 2:
        scanf("%d", &v);
        modify_div(1, n, 1, l, r, v);
        break;
      case 3:
        printf("%d\n", query_min(1, n, 1, l, r));
        break;
      case 4:
        printf("%lld\n", query_sum(1, n, 1, l, r));
        break;
    }
  }
  return 0;
}
