#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, w, t, x[N], v[N];
double l[N], r[N], h[N];
pair<pair<int, int>, int> interv[N];

#define lo (o<<1)
#define ro (o<<1|1)

struct segment_t {
  int sum[N << 2];

  void reset() {
    memset(sum, 0, sizeof sum);
  }

  void modify(int l, int r, int o, int p, int v) {
    sum[o] += v;
    if (l == r) {
      return;
    } else {
      int mid = l + r >> 1;
      if (p <= mid) {
        modify(l, mid, lo, p, v);
      } else {
        modify(mid + 1, r, ro, p, v);
      }
    }
  }

  int query(int l, int r, int o, int ql, int qr) {
    if (ql > qr) {
      return 0;
    }
    if (ql <= l && r <= qr) {
      return sum[o];
    } else {
      int mid = l + r >> 1, result = 0;
      if (ql <= mid) {
        result += query(l, mid, lo, ql, qr);
      } if (qr > mid) {
        result += query(mid + 1, r, ro, ql, qr);
      }
      return result;
    }
  }
} seg_t[2];

double fdiv(int x, int y) {
  int g = __gcd(x, y);
  x /= g;
  y /= g;
  return (double) x / y;
}

int main() {
  scanf("%d%d", &n, &w);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &x[i], &v[i]);
    l[i] = fdiv(x[i], v[i] - w);
    r[i] = fdiv(x[i], v[i] + w);
    if (l[i] > r[i]) {
      swap(l[i], r[i]);
    }
    h[++t] = l[i];
    h[++t] = r[i];
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  for (int i = 1; i <= n; ++i) {
    interv[i] = {{lower_bound(h + 1, h + 1 + t, l[i]) - h, lower_bound(h + 1, h + 1 + t, r[i]) - h}, i};
  }
  sort(interv + 1, interv + 1 + n);
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    int type = x[interv[i].second] > 0;
    answer += seg_t[!type].sum[1] - seg_t[!type].query(1, t, 1, 1, interv[i].first.first - 1);
    seg_t[type].modify(1, t, 1, interv[i].first.second, 1);
  }
  seg_t[0].reset();
  seg_t[1].reset();
  sort(interv + 1, interv + 1 + n, [&] (const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
    return a.first.first == b.first.first ? a.first.second > b.first.second : a.first.first < b.first.first;
  });
  for (int i = 1; i <= n; ++i) {
    int type = x[interv[i].second] > 0;
    answer += seg_t[type].query(1, t, 1, interv[i].first.second, t);
    seg_t[type].modify(1, t, 1, interv[i].first.second, 1);
  }
  printf("%lld\n", answer);
  return 0;
}
