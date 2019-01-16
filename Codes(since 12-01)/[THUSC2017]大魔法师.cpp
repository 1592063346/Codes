#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, q, a[N], b[N], c[N];
bool changed[N << 2];

struct matrix_t {
  int n, m, a[4][4];

  matrix_t() {
    memset(a, 0, sizeof a);
  }

  matrix_t operator + (const matrix_t& b) const {
    matrix_t result = *this;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        add(result.a[i][j], b.a[i][j]);
      }
    }
    return result;
  }

  matrix_t operator * (const matrix_t& b) const {
    matrix_t result;
    result.n = n;
    result.m = b.m;
    for (int i = 0; i < n; ++i) {
      for (int k = 0; k < m; ++k) {
        if (a[i][k]) {
          for (int j = 0; j < b.m; ++j) {
            if (b.a[k][j]) {
              result.a[i][j] = (result.a[i][j] + (long long) a[i][k] * b.a[k][j]) % mod;
            }
          }
        }
      }
    }
    return result;
  }
} info[N << 2], tag[N << 2], old;

#define lo (o<<1)
#define ro (o<<1|1)

void mul(int o, matrix_t x) {
  info[o] = info[o] * x;
  tag[o] = tag[o] * x;
  changed[o] = true;
}

void push_down(int o) {
  if (changed[o]) {
    mul(lo, tag[o]);
    mul(ro, tag[o]);
    tag[o] = old;
    changed[o] = false;
  }
}

void build(int l, int r, int o) {
  tag[o] = old;
  changed[o] = false;
  if (l == r) {
    info[o].n = 1;
    info[o].m = 4;
    info[o].a[0][0] = a[l];
    info[o].a[0][1] = b[l];
    info[o].a[0][2] = c[l];
    info[o].a[0][3] = 1;
  } else {
    int mid = l + r >> 1;
    build(l, mid, lo);
    build(mid + 1, r, ro);
    info[o] = info[lo] + info[ro];
  }
}

void modify(int l, int r, int o, int ql, int qr, int type, int v) {
  if (ql <= l && r <= qr) {
    matrix_t tran = old;
    switch (type) {
      case 1:
        tran.a[1][0] = 1;
        break;
      case 2:
        tran.a[2][1] = 1;
        break;
      case 3:
        tran.a[0][2] = 1;
        break;
      case 4:
        tran.a[3][0] = v;
        break;
      case 5:
        tran.a[1][1] = v;
        break;
      case 6:
        tran.a[2][2] = 0;
        tran.a[3][2] = v;
        break;
    }
    mul(o, tran);
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (ql <= mid) {
      modify(l, mid, lo, ql, qr, type, v);
    } if (qr > mid) {
      modify(mid + 1, r, ro, ql, qr, type, v);
    }
    info[o] = info[lo] + info[ro];
  }
}

matrix_t query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return info[o];
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (qr <= mid) {
      return query(l, mid, lo, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, ro, ql, qr);
    } else {
      return query(l, mid, lo, ql, qr) + query(mid + 1, r, ro, ql, qr);
    }
  }
}

int main() {
  old.n = old.m = 4;
  for (int i = 0; i < 4; ++i) {
    old.a[i][i] = 1;
  }
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a[i], &b[i], &c[i]);
  }
  build(1, n, 1);
  scanf("%d", &q);
  while (q--) {
    int type, l, r, v;
    scanf("%d%d%d", &type, &l, &r);
    switch (type) {
      case 1:
        modify(1, n, 1, l, r, 1, 0);
        break;
      case 2:
        modify(1, n, 1, l, r, 2, 0);
        break;
      case 3:
        modify(1, n, 1, l, r, 3, 0);
        break;
      case 4:
        scanf("%d", &v);
        modify(1, n, 1, l, r, 4, v);
        break;
      case 5:
        scanf("%d", &v);
        modify(1, n, 1, l, r, 5, v);
        break;
      case 6:
        scanf("%d", &v);
        modify(1, n, 1, l, r, 6, v);
        break;
      case 7:
        matrix_t result = query(1, n, 1, l, r);
        printf("%d %d %d\n", result.a[0][0], result.a[0][1], result.a[0][2]);
        break;
    }
  }
  return 0;
}
