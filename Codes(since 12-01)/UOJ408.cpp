#include<bits/stdc++.h>
#include "doll.h"

using namespace std;

const int maxn = 3e5 + 10, cycle = 19260817;

int switches, rev[maxn], value[maxn];
vector<int> go[maxn], c, x, y;

void move(vector<int>& a, int value) {
  int old = a.size();
  a.push_back(value);
  for (int i = 0; i < old; ++i) {
    a[i] = a[i + 1];
  }
  a.pop_back();
}

int build_edge(int l, int r) {
  if (l == r) {
    return value[l];
  } else {
    int mid = l + r >> 1;
    int lo = build_edge(l, mid);
    int ro = build_edge(mid + 1, r);
    if (lo == cycle && ro == cycle) {
      return cycle;
    } else {
      --switches;
      x.push_back(lo);
      y.push_back(ro);
      return switches;
    }
  }
}

void create_circuit(int m, vector<int> a) {
  int n = a.size(), len = 0, source = a[0];
  move(a, 0);
  for (; (1 << len) < n; ++len);
  int all = 1 << len;
  for (int i = 0; i < all; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  int old = a.size();
  a.resize(all);
  vector<int> arr;
  for (int i = all - old; i < all; ++i) {
    arr.push_back(rev[i]);
  }
  sort(arr.begin(), arr.end());
  for (int i = 0; i < all - old; ++i) {
    value[i] = cycle;
  }
  for (int i = all - old; i < all; ++i) {
    value[i] = a[lower_bound(arr.begin(), arr.end(), rev[i]) - arr.begin()];
  }
  int o = build_edge(0, all - 1);
  for (auto& v : x) {
    if (v == cycle) {
      v = o;
    }
  }
  for (auto& v : y) {
    if (v == cycle) {
      v = o;
    }
  }
  c.resize(m + 1, o);
  c[0] = source;
  answer(c, x, y);
}
