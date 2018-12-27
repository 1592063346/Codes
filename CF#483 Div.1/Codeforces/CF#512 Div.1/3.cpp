#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, q, a[N], value[N];

#define lo (o<<1)
#define ro (o<<1|1)

long long sum[N << 2];

void build(int l, int r, int o) {
  if (l == r) {
    sum[o] = value[l];
  } else {
    int mid = l + r >> 1;
    build(l, mid, lo);
    build(mid + 1, r, ro);
    sum[o] = sum[lo] + sum[ro];
  }
}

void modify(int l, int r, int o, int p) {
  if (l == r) {
    sum[o] = value[l];
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

long long query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return sum[o];
  } else {
    int mid = l + r >> 1;
    long long result = 0;
    if (ql <= mid) {
      result += query(l, mid, lo, ql, qr);
    } if (qr > mid) {
      result += query(mid + 1, r, ro, ql, qr);
    }
    return result;
  }
}

int query(int l, int r, int o, long long x) {
  if (l == r) {
    return l;
  } else {
    int mid = l + r >> 1;
    if (sum[lo] > x) {
      return query(l, mid, lo, x);
    } else {
      return query(mid + 1, r, ro, x - sum[lo]);
    }
  }
}

struct state {
  int a, b, c;

  state () {}
  state (int a, int b, int c): a(a), b(b), c(c) {}

  state operator + (const state& other) const {
    state result = *this;
    add(result.a, other.a);
    add(result.b, other.b);
    add(result.c, other.c);
    return result;
  }

  state operator - (const state& other) const {
    state result = *this;
    sub(result.a, other.a);
    sub(result.b, other.b);
    sub(result.c, other.c);
    return result;
  }
} c[N];

void modify(int p, state x) {
  for (; p <= n; p += p & -p) {
    c[p] = c[p] + x;
  }
}

state query(int p) {
  state result (0, 0, 0);
  for (; p; p -= p & -p) {
    result = result + c[p];
  }
  return result;
}

state query(int l, int r) {
  return query(r) - query(l - 1);
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &value[i]);
    modify(i, state (value[i], mul(value[i], i), mul(value[i], a[i])));
  }
  build(1, n, 1);
  for (int i = 1; i <= q; ++i) {
    int p, x;
    scanf("%d%d", &p, &x);
    if (p < 0) {
      p = -p;
      modify(p, state ((mod - value[p]) % mod, (mod - mul(value[p], p)) % mod, (mod - mul(value[p], a[p])) % mod));
      value[p] = x;
      modify(p, state (value[p], mul(value[p], p), mul(value[p], a[p])));
      modify(1, n, 1, p);
    } else {
      long long sumv = query(1, n, 1, p, x) >> 1;
      if (p ^ 1) {
        sumv += query(1, n, 1, 1, p - 1);
      }
      int static_pos = query(1, n, 1, sumv), ans = 0;
      if (p ^ static_pos) {
        int l = p, r = static_pos - 1;
        state result = query(l, r);
        add(ans, ((result.b + (long long) result.a * (a[static_pos] - static_pos) - result.c) % mod + mod) % mod);
      }
      if (x ^ static_pos) {
        int l = static_pos + 1, r = x;
        state result = query(l, r);
        add(ans, ((result.c - (long long) result.a * (a[static_pos] - static_pos) - result.b) % mod + mod) % mod);
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
