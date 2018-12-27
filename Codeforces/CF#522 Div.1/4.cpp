#include<bits/stdc++.h>

using namespace std;

#define X first
#define Y second
#define mp make_pair
#define rg register

typedef pair<int, int> pii;

template<typename T> inline bool checkMin(T& a, const T& b) {
  return a > b ? a = b, true : false;
}

template<typename T> inline bool checkMax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}

const int N = 1e5 + 10;

int n, a[N * 3], all;

#define lo (o<<1)
#define ro (o<<1|1)

int gol[20][N * 12], gor[20][N * 12];

inline void modify(int l, int r, int o, int p, int d, int lv, int rv) {
  if (l == r) {
    gol[d][o] = lv, gor[d][o] = rv;
  } else {
    int mid = l + r >> 1;
    (p <= mid) ? modify(l, mid, lo, p, d, lv, rv) : modify(mid + 1, r, ro, p, d, lv, rv);
    gol[d][o] = min(gol[d][lo], gol[d][ro]);
    gor[d][o] = max(gor[d][lo], gor[d][ro]);
  }
}

inline pii query(int l, int r, int o, int ql, int qr, int d) {
  if (ql <= l && r <= qr) {
    return mp(gol[d][o], gor[d][o]);
  } else {
    int mid = l + r >> 1;
    pii res(1e9, -1e9);
    if (ql <= mid) {
      pii x = query(l, mid, lo, ql, qr, d);
      checkMin(res.X, x.X);
      checkMax(res.Y, x.Y);
    } if (qr > mid) {
      pii x = query(mid + 1, r, ro, ql, qr, d);
      checkMin(res.X, x.X);
      checkMax(res.Y, x.Y);
    }
    return res;
  }
}

void init() {
  for (rg int i = 1; i <= all; ++i) {
    modify(1, all, 1, i, 0, i - a[i], i + a[i]);
  }
  for (rg int j = 1; (1 << j) <= n; ++j) {
    for (rg int i = 1; i <= all; ++i) {
      pii x = query(1, all, 1, i, i, j - 1);
      int left = max(1, x.X);
      int right = min(all, x.Y);
      x = query(1, all, 1, left, right, j - 1);
      modify(1, all, 1, i, j, x.X, x.Y);
    }
  }
}

int main() {
  scanf("%d", &n), all = n * 3;
  if (n == 1) {
    return puts("0"), 0;
  }
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    a[i + n] = a[i + n + n] = a[i];
  }
  init();
  for (rg int i = n + 1; i <= n + n; ++i) {
    int ans = 0, pl = i, pr = i;
    for (rg int j = (int) log2(n); ~j; --j) {
      pii x = query(1, all, 1, pl, pr, j);
      int left = x.X;
      int right = x.Y;
      if (right - left + 1 < n) {
        pl = left, pr = right;
        ans += 1 << j;
      }
    }
    printf("%d%c", ans + 1, " \n"[i == n + n]);
  }
  return 0;
}
