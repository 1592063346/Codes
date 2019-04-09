#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 998244353, inv2 = mod + 1 >> 1;

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

int n, m, f[N << 2], g[N << 2], mult[N << 2], addt[N << 2], all, tt = 1;

void tadd(int o, int x) {
  add(g[o], x);
  add(addt[o], x);
}

void tmul(int o, int x) {
  g[o] = mul(g[o], x);
  addt[o] = mul(addt[o], x);
  mult[o] = mul(mult[o], x);
}

void push(int o) {
  if (mult[o] != 1) {
    tmul(o << 1, mult[o]);
    tmul(o << 1 | 1, mult[o]);
    mult[o] = 1;
  }
  if (addt[o]) {
    tadd(o << 1, addt[o]);
    tadd(o << 1 | 1, addt[o]);
    addt[o] = 0;
  }
}

void modify(int l, int r, int o, int ql, int qr) {
  int mid = l + r >> 1;
  if (r < ql || l > qr) {
    sub(all, f[o]);
    f[o] = (mul(f[o], inv2) + mul(g[o], inv2)) % mod;
    add(all, f[o]);
  } else if (ql <= l && r <= qr) {
    sub(all, f[o]);
    f[o] = (mul(f[o], inv2) + inv2) % mod;
    g[o] = (mul(g[o], inv2) + inv2) % mod;
    add(all, f[o]);
    if (l != r) {
      tmul(o << 1, inv2);
      tadd(o << 1, inv2);
      tmul(o << 1 | 1, inv2);
      tadd(o << 1 | 1, inv2);
    }
  } else {
    sub(all, f[o]);
    f[o] = mul(f[o], inv2);
    g[o] = mul(g[o], inv2);
    add(all, f[o]);
    push(o);
    modify(l, mid, o << 1, ql, qr);
    modify(mid + 1, r, o << 1 | 1, ql, qr);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  fill(mult + 1, mult + (n << 2) + 1, 1);
  while (m--) {
    int opt, l, r;
    scanf("%d", &opt);
    if (opt == 1) {
      scanf("%d%d", &l, &r);
      modify(1, n, 1, l, r);
      tt = (tt << 1) % mod;
    } else {
      printf("%d\n", mul(all, tt));
    }
  }
  return 0;
}
