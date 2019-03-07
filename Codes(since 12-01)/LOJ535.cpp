#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

struct event_t {
  int l, r, opt;

  event_t() {}
  event_t(int l, int r, int opt): l(l), r(r), opt(opt) {}
};

int n, a[N], number[N], maxv[N << 2], addv[N << 2];
vector<pair<int, int>> pre_max, suf_min;
vector<event_t> events[N];

void modify(int p) {
  for (; p <= n; p += p & -p) {
    ++number[p];
  }
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    result += number[p];
  }
  return result;
}

void add(int o, int v) {
  maxv[o] += v;
  addv[o] += v;
}

void push_down(int o) {
  if (addv[o]) {
    add(o << 1, addv[o]);
    add(o << 1 | 1, addv[o]);
    addv[o] = 0;
  }
}

void modify(int l, int r, int o, int ql, int qr, int v) {
  if (ql <= l && r <= qr) {
    add(o, v);
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr, v);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    } else {
      modify(l, mid, o << 1, ql, qr, v);
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    }
    maxv[o] = max(maxv[o << 1], maxv[o << 1 | 1]);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  long long answer = 0;
  for (int i = n; i; --i) {
    answer += query(a[i]);
    modify(a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    if (!pre_max.size() || a[i] > pre_max.back().first) {
      pre_max.emplace_back(a[i], i);
    }
  }
  for (int i = n; i; --i) {
    if (!suf_min.size() || a[i] < suf_min.back().first) {
      suf_min.emplace_back(a[i], i);
    }
  }
  reverse(suf_min.begin(), suf_min.end());
  for (int i = 1; i <= n; ++i) {
    int l, r, ql, qr;
    l = 0;
    r = pre_max.size() - 1;
    while (l != r) {
      int mid = l + r >> 1;
      if (pre_max[mid].first > a[i]) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    ql = pre_max[l].second;
    l = 0;
    r = suf_min.size() - 1;
    while (l != r) {
      int mid = (l + r >> 1) + 1;
      if (suf_min[mid].first < a[i]) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    qr = suf_min[l].second;
    if (ql < i && i < qr) {
      events[i + 1].emplace_back(ql, i - 1, 1);
      events[qr + 1].emplace_back(ql, i - 1, -1);
    }
  }
  int sub_max = 0;
  for (int i = 1; i <= n; ++i) {
    for (auto event : events[i]) {
      modify(1, n, 1, event.l, event.r, event.opt);
    }
    cmax(sub_max, maxv[1] << 1);
  }
  printf("%lld\n", answer - sub_max);
  return 0;
}
