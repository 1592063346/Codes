#include<bits/stdc++.h>

using namespace std;

int q;
long long tag1[61], tag2[61], l[61], r[61];

int find(long long c) {
  int l = 1, r = 60;
  while (l != r) {
    int mid = (l + r >> 1) + 1;
    if (::l[mid] > c) {
      r = mid - 1;
    } else {
      l = mid;
    }
  }
  return l;
}

void modify1(long long u, long long k) {
  int c = find(u);
  tag1[c] -= k;
}

void modify2(long long u, long long k) {
  int c = find(u);
  tag2[c] += k;
}

long long tran(long long u, int c, long long tag) {
  long long leng = r[c] - l[c] + 1;
  long long diff = tag % leng;
  u += diff;
  if (u < l[c]) {
    u += leng;
  }
  if (u > r[c]) {
    u -= leng;
  }
  return u;
}

void solve(long long u) {
  int c = find(u);
  u = tran(u, c, -tag1[c]);
  for (int i = c; i; --i) {
    printf("%lld%c", tran(u, i, tag1[i]), " \n"[i == 1]);
    u = tran(u, i, tag2[i]) >> 1;
  }
}

int main() {
  for (int i = 1; i <= 60; ++i) {
    l[i] = 1ll << i - 1;
    r[i] = (1ll << i) - 1;
  }
  scanf("%d", &q);
  while (q--) {
    int t;
    long long x, k;
    scanf("%d%lld", &t, &x);
    switch (t) {
      case 1:
        scanf("%lld", &k);
        modify1(x, k);
        break;
      case 2:
        scanf("%lld", &k);
        modify2(x, k);
        break;
      case 3:
        solve(x);
        break;
    }
  }
  return 0;
}
