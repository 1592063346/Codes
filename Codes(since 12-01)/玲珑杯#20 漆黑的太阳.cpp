#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, M = 400;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, q, t, mod, a[N], h[N], block[N], times[N], answer[N], maxt, pre[N], suf[N], sumt[N];
long long sum, sumk[N];

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
  int l, r, mod, id;

  query_t() {}
  query_t(int l, int r, int mod, int id): l(l), r(r), mod(mod), id(id) {}

  bool operator < (const query_t& b) const {
    return block[l] == block[b.l] ? r < b.r : block[l] < block[b.l];
  }
} queries[N];

void add(int x) {
  if (times[x]) {
    sumk[times[x]] -= h[x];
    --sumt[times[x]];
  } else {
    sum += h[x];
  }
  if (sumt[times[x]] && !sumt[times[x] + 1]) {
    int r = suf[times[x]];
    pre[r] = times[x] + 1;
    suf[times[x]] = times[x] + 1;
    pre[times[x] + 1] = times[x];
    suf[times[x] + 1] = r;
  } else if (!sumt[times[x]] && !sumt[times[x] + 1]) {
    int l = pre[times[x]];
    int r = suf[times[x]];
    suf[l] = times[x] + 1;
    pre[r] = times[x] + 1;
    pre[times[x] + 1] = l;
    suf[times[x] + 1] = r;
  } else if (!sumt[times[x]] && sumt[times[x] + 1]) {
    int l = pre[times[x]];
    suf[l] = times[x] + 1;
    pre[times[x] + 1] = l;
  }
  ++times[x];
  cmax(maxt, times[x]);
  if (times[x]) {
    sumk[times[x]] += h[x];
    ++sumt[times[x]];
  }
}

void del(int x) {
  if (times[x]) {
    sumk[times[x]] -= h[x];
    --sumt[times[x]];
  }
  if (times[x] == maxt && !sumt[times[x]]) {
    --maxt;
  }
  if (sumt[times[x]] && !sumt[times[x] - 1]) {
    int l = pre[times[x]];
    suf[l] = times[x] - 1;
    pre[times[x]] = times[x] - 1;
    pre[times[x] - 1] = l;
    suf[times[x] - 1] = times[x];
  } else if (!sumt[times[x]] && !sumt[times[x] - 1]) {
    int l = pre[times[x]];
    int r = suf[times[x]];
    suf[l] = times[x] - 1;
    pre[r] = times[x] - 1;
    pre[times[x] - 1] = l;
    suf[times[x] - 1] = r;
  } else if (!sumt[times[x]] && sumt[times[x] - 1]) {
    int r = suf[times[x]];
    pre[r] = times[x] - 1;
    suf[times[x] - 1] = r;
  }
  --times[x];
  if (times[x]) {
    sumk[times[x]] += h[x];
    ++sumt[times[x]];
  } else {
    sum -= h[x];
  }
}

int query(int len) {
  int result = mul(sum % mod, qpow(2, len)), x = 1;
  for (int i = maxt, j = 0; i; i = pre[i]) {
    if (j < len - i) {
      x = mul(x, qpow(2, len - i - j));
      j = len - i;
    }
    sub(result, mul(sumk[i] % mod, x));
  }
  return result;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    block[i] = (i - 1) / M + 1;
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    h[i] = a[i];
  }
  sort(h + 1, h + 1 + n);
  t = unique(h + 1, h + 1 + n) - h - 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(h + 1, h + 1 + t, a[i]) - h;
  }
  for (int i = 1; i <= q; ++i) {
    int l, r, mod;
    scanf("%d%d%d", &l, &r, &mod);
    assert(mod >= 2);
    queries[i] = query_t(l, r, mod, i);
  }
  sort(queries + 1, queries + 1 + q);
  int ql = 1, qr = 0;
  suf[0] = n + 1;
  for (int i = 1; i <= q; ++i) {
    for (; qr < queries[i].r; add(a[++qr]));
    for (; qr > queries[i].r; del(a[qr--]));
    for (; ql < queries[i].l; del(a[ql++]));
    for (; ql > queries[i].l; add(a[--ql]));
    mod = queries[i].mod;
    answer[queries[i].id] = query(qr - ql + 1);
  }
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
