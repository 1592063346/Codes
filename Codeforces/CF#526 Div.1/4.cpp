#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;

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

int n, a[N], pre[N], suf[N], pos[N];

struct info_t {
  int maxl, minr, tagl, tagr, suml, sumr, sumlr, sumjr, sumcoef;

  info_t() {
    tagl = -1;
    tagr = -1;
  }
  info_t(int maxl, int minr, int suml, int sumr, int sumlr, int sumjr, int sumcoef): maxl(maxl), minr(minr), suml(suml), sumr(sumr), sumlr(sumlr), sumjr(sumjr), sumcoef(sumcoef) {}

  info_t operator + (info_t a) {
    info_t result;
    result.maxl = max(maxl, a.maxl);
    result.minr = min(minr, a.minr);
    result.suml = (suml + a.suml) % mod;
    result.sumr = (sumr + a.sumr) % mod;
    result.sumlr = (sumlr + a.sumlr) % mod;
    result.sumjr = (sumjr + a.sumjr) % mod;
    result.sumcoef = (sumcoef + a.sumcoef) % mod;
    return result;
  }
} info[N << 2];

#define lo (o<<1)
#define ro (o<<1|1)

int samediff_sum(int l, int r) {
  return ((long long) (l + r) * (r - l + 1) >> 1) % mod;
}

void cover_l(int l, int r, int o, int prep) {
  info[o].tagl = prep;
  info[o].maxl = prep;
  info[o].suml = mul(r - l + 1, prep);
  info[o].sumlr = mul(info[o].sumr, prep);
  info[o].sumcoef = (info[o].suml - samediff_sum(l - 1, r - 1) + mod) % mod;
}

void cover_r(int l, int r, int o, int sufp) {
  info[o].tagr = sufp;
  info[o].minr = sufp;
  info[o].sumr = mul(r - l + 1, sufp);
  info[o].sumlr = mul(info[o].suml, sufp);
  info[o].sumjr = mul(sufp, samediff_sum(l, r));
}

void push_down(int l, int r, int o) {
  int mid = l + r >> 1;
  if (~info[o].tagl) {
    cover_l(l, mid, lo, info[o].tagl);
    cover_l(mid + 1, r, ro, info[o].tagl);
    info[o].tagl = -1;
  }
  if (~info[o].tagr) {
    cover_r(l, mid, lo, info[o].tagr);
    cover_r(mid + 1, r, ro, info[o].tagr);
    info[o].tagr = -1;
  }
}

void modify(int l, int r, int o, int p, int prep, int sufp) {
  if (l == r) {
    info[o] = info_t(prep, sufp, prep, sufp, mul(prep, sufp), mul(l, sufp), (prep - l + 1 + mod) % mod);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (p <= mid) {
      modify(l, mid, lo, p, prep, sufp);
    } else {
      modify(mid + 1, r, ro, p, prep, sufp);
    }
    info[o] = info[lo] + info[ro];
  }
}

void modify_max(int l, int r, int o, int ql, int qr, int prep) {
  if (ql <= l && r <= qr) {
    cover_l(l, r, o, prep);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (ql <= mid) {
      modify_max(l, mid, lo, ql, qr, prep);
    } if (qr > mid) {
      modify_max(mid + 1, r, ro, ql, qr, prep);
    }
    info[o] = info[lo] + info[ro];
  }
}

void modify_min(int l, int r, int o, int ql, int qr, int sufp) {
  if (ql <= l && r <= qr) {
    cover_r(l, r, o, sufp);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (ql <= mid) {
      modify_min(l, mid, lo, ql, qr, sufp);
    } if (qr > mid) {
      modify_min(mid + 1, r, ro, ql, qr, sufp);
    }
    info[o] = info[lo] + info[ro];
  }
}

info_t query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return info[o];
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
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
  scanf("%d", &n);
  vector<int> h;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    h.push_back(a[i]);
  }
  sort(h.begin(), h.end());
  h.erase(unique(h.begin(), h.end()), h.end());
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(h.begin(), h.end(), a[i]) - h.begin();
  }
  for (int i = 1; i <= n; ++i) {
    pre[i] = pos[a[i]] ? pos[a[i]] : 0;
    pos[a[i]] = i;
  }
  memset(pos, 0, sizeof pos);
  for (int i = n; i; --i) {
    suf[i] = pos[a[i]] ? pos[a[i]] : n + 1;
    pos[a[i]] = i;
  }
  int answer = 0;
  for (int i = 1, j = 1; i <= n; ++i) {
    for (; j <= pre[i]; ++j);
    int l = j, r = i;
    while (l != r) {
      int mid = l + r >> 1;
      if (query(1, n, 1, mid, i - 1).maxl < pre[i]) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    if (l <= i - 1) {
      modify_max(1, n, 1, l, i - 1, pre[i]);
    }
    l = j, r = i;
    while (l != r) {
      int mid = l + r >> 1;
      if (query(1, n, 1, mid, i - 1).minr > suf[i]) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    if (l <= i - 1) {
      modify_min(1, n, 1, l, i - 1, suf[i]);
    }
    modify(1, n, 1, i, pre[i], suf[i]);
    info_t result = query(1, n, 1, j, i);
    add(answer, result.sumjr);
    sub(answer, result.sumlr);
    add(answer, mul(i + 1, result.sumcoef));
    sub(answer, result.sumr);
  }
  printf("%d\n", answer);
  return 0;
}
