#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, m, sumi2[N << 2], sumi[N << 2], sum[N << 2], adda[N << 2], addb[N << 2], addc[N << 2];

void build(int l, int r, int o) {
  if (l == r) {
    sumi2[o] = mul(l, l);
    sumi[o] = l;
  } else {
    int mid = l + r >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
    sumi2[o] = (sumi2[o << 1] + sumi2[o << 1 | 1]) % mod;
    sumi[o] = (sumi[o << 1] + sumi[o << 1 | 1]) % mod;
  }
}

void add(int l, int r, int o, int a, int b, int c) {
  add(adda[o], a);
  add(addb[o], b);
  add(addc[o], c);
  add(sum[o], ((mul(sumi2[o], a) + mul(sumi[o], b)) % mod + mul(r - l + 1, c)) % mod);
}

void push_down(int l, int r, int o) {
  int mid = l + r >> 1;
  if (adda[o] || addb[o] || addc[o]) {
    add(l, mid, o << 1, adda[o], addb[o], addc[o]);
    add(mid + 1, r, o << 1 | 1, adda[o], addb[o], addc[o]);
    adda[o] = 0;
    addb[o] = 0;
    addc[o] = 0;
  }
}

void modify(int l, int r, int o, int ql, int qr, int a, int b, int c) {
  if (ql <= l && r <= qr) {
    add(l, r, o, a, b, c);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr, a, b, c);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr, a, b, c);
    } else {
      modify(l, mid, o << 1, ql, qr, a, b, c);
      modify(mid + 1, r, o << 1 | 1, ql, qr, a, b, c);
    }
    sum[o] = (sum[o << 1] + sum[o << 1 | 1]) % mod;
  }
}

int query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return sum[o];
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (qr <= mid) {
      return query(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      return (query(l, mid, o << 1, ql, qr) + query(mid + 1, r, o << 1 | 1, ql, qr)) % mod;
    }
  }
}

void add(int l, int r, int x) {
  int inv2 = mod + 1 >> 1, len = r - l + 1, a, b, c;
  a = mul(x, inv2);
  b = mul(mul(x, ((3 - 2 * l) % mod + mod) % mod), inv2);
  c = mul(mul(x, ((mul(l, l) - 3 * l + 2) % mod + mod) % mod), inv2);
  modify(0, n, 1, l, r, a, b, c);
  if (r != n) {
    a = 0;
    b = mul(len, x);
    c = mul(mul(mul(((len - 2 * r + 1) % mod + mod) % mod, len), x), inv2);
    modify(0, n, 1, r + 1, n, a, b, c);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  build(0, n, 1);
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    add(i, i, x);
  }
  while (m--) {
    int type, l, r, x;
    scanf("%d%d%d", &type, &l, &r);
    if (type == 1) {
      if (l > r) {
        swap(l, r);
      }
      scanf("%d", &x);
      add(l, r, x);
    } else {
      int s1 = query(0, n, 1, n, n);
      int s2 = query(0, n, 1, l - 1, r - 1);
      int s3 = query(0, n, 1, n - r, n - l);
      printf("%d\n", ((mul(s1, r - l + 1) - s2 - s3) % mod + mod) % mod);
    }
  }
  return 0;
}
