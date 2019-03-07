#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, a, b, c, m, q, add[N << 2];
vector<int> h;
char t[N];

void modify(int l, int r, int o, int ql, int qr, int v) {
  if (ql > qr) {
    return;
  }
  if (ql <= l && r <= qr) {
    add[o] += v;
  } else {
    int mid = l + r >> 1;
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr, v);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    } else {
      modify(l, mid, o << 1, ql, qr, v);
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    }
  }
}

int query(int l, int r, int o, int p) {
  if (l == r) {
    return add[o];
  } else {
    int mid = l + r >> 1;
    if (p < h[mid + 1]) {
      return add[o] + query(l, mid, o << 1, p);
    } else {
      return add[o] + query(mid + 1, r, o << 1 | 1, p);
    }
  }
}

int id(int x) {
  return lower_bound(h.begin(), h.end(), x) - h.begin();
}

void modify(int p, int opt) {
  int l = (((long long) p * -a) % n + n) % n, r = (((long long) p * -a + c) % n + n) % n;
  if (t[p] == '0') {
    swap(l, r);
  }
  if (l <= r) {
    modify(0, h.size() - 1, 1, id(l), id(r) - 1, opt);
  } else {
    modify(0, h.size() - 1, 1, id(l), id(n) - 1, opt);
    modify(0, h.size() - 1, 1, id(0), id(r) - 1, opt);
  }
}

int main() {
  scanf("%d%d%d%d%d%s%d", &n, &a, &b, &c, &m, t, &q);
  h.push_back(0);
  h.push_back(n);
  for (int i = 0; i < m; ++i) {
    h.push_back((((long long) i * -a) % n + n) % n);
    h.push_back((((long long) i * -a + c) % n + n) % n);
  }
  sort(h.begin(), h.end());
  h.erase(unique(h.begin(), h.end()), h.end());
  for (int i = 0; i < m; ++i) {
    modify(i, 1);
  }
  while (q--) {
    int opt, p;
    scanf("%d%d", &opt, &p);
    if (opt == 1) {
      int value = ((long long) p * a + b) % n;
      printf("%d\n", query(0, h.size() - 1, 1, value));
    } else {
      modify(p, -1);
      t[p] = t[p] == '0' ? '1' : '0';
      modify(p, 1);
    }
  }
  return 0;
}
