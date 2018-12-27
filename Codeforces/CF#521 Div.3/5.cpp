#include<bits/stdc++.h>

using namespace std;

#define rg register

template<typename T> inline bool checkMax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}

const int N = 2e5 + 10;

int n, a[N], h[N], tag[N], num[N], t;

inline int qpow(int v, int p) {
  int res = 1;
  for (; p; p >>= 1, v *= v) {
    if (p & 1) {
      res *= v;
    }
  }
  return res;
}

inline int f(int v, int k) {
  return v * (qpow(2, k) - 1);
}

int main() {
  scanf("%d", &n);
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]), h[++t] = a[i];
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  for (rg int i = 1; i <= n; ++i) {
    a[i] = lower_bound(h + 1, h + 1 + t, a[i]) - h;
    ++tag[a[i]];
  }
  for (rg int i = 1; i <= t; ++i) {
    ++num[tag[i]];
  }
  for (rg int i = n; ~i; --i) {
    num[i] += num[i + 1];
  }
  int ans = 0;
  for (rg int i = 1; i <= n; ++i) {
    int v = tag[i], res = 1;
    checkMax(ans, f(v, res));
    for (;;) {
      v >>= 1, ++res;
      if (num[v] < res) {
        int l = 0, r = v;
        while (l ^ r) {
          int mid = (l + r >> 1) + 1;
          if (num[mid] < res) {
            r = mid - 1;
          } else {
            l = mid;
          }
        }
        v = l;
      }
      if (!v) {
        break;
      }
      checkMax(ans, f(v, res));
    }
  }
  printf("%d\n", ans);
  return 0;
}
