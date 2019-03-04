#include<bits/stdc++.h>

using namespace std;

const int N = 25e4 + 10, mod = 1e9 + 7, inv2 = mod + 1 >> 1;

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

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

struct query_t {
  int n, m, l, r, id;

  query_t() {}
  query_t(int n, int m, int l, int r, int id): n(n), m(m), l(l), r(r), id(id) {}
};

int tt, fac[N], inv_fac[N], answer[N];

int binom(int n, int m) {
  return n < m ? 0 : mul(fac[n], mul(inv_fac[m], inv_fac[n - m]));
}

void binom_init(int n) {
  fac[0] = inv_fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  inv_fac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    inv_fac[i] = mul(inv_fac[i + 1], i + 1);
  }
}

int main() {
  binom_init(25e4);
  scanf("%d%*d", &tt);
  vector<query_t> queries(tt);
  for (int i = 0; i < tt; ++i) {
    int n, m;
    scanf("%d%d", &n, &m);
    queries[i].n = n;
    queries[i].m = m;
    queries[i].l = n + m;
    queries[i].r = n > m ? m - 1 : n - 1;
    queries[i].id = i;
    if (n < m) {
      answer[i] = mul(binom(n + m, m), m - n);
    }
  }
  int M = sqrt(25e4);
  sort(queries.begin(), queries.end(), [&] (const query_t& a, const query_t& b) {
    int block_a = a.l / M, block_b = b.l / M;
    return block_a == block_b ? a.r < b.r : block_a < block_b;
  });
  int ql = 0, qr = 0, result = 1;
  for (auto v : queries) {
    for (; ql < v.l; ++ql) {
      result = mul(result, 2);
      sub(result, binom(ql, qr));
    }
    for (; ql > v.l; --ql) {
      add(result, binom(ql - 1, qr));
      result = mul(result, inv2);
    }
    for (; qr < v.r; ++qr) {
      add(result, binom(ql, qr + 1));
    }
    for (; qr > v.r; --qr) {
      sub(result, binom(ql, qr));
    }
    add(answer[v.id], result);
    answer[v.id] = mul(answer[v.id], qpow(binom(v.n + v.m, v.n), mod - 2));
    add(answer[v.id], (v.n - v.m + mod) % mod);
  }
  for (int i = 0; i < tt; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
