#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, a[N], addv[N << 2];
long long sum[N << 2], sum2[N << 2], coef[N << 2];
vector<int> pos[N];

void pull(int o) {
  sum[o] = sum[o << 1] + sum[o << 1 | 1];
  sum2[o] = sum2[o << 1] + sum2[o << 1 | 1];
  coef[o] = coef[o << 1] + coef[o << 1 | 1];
}

void add(int l, int r, int o, int v) {
  addv[o] += v;
  sum[o] += (r - l + 1) * v;
  sum2[o] += coef[o] * v;
}

void push(int l, int r, int o) {
  int mid = l + r >> 1;
  if (addv[o]) {
    add(l, mid, o << 1, addv[o]);
    add(mid + 1, r, o << 1 | 1, addv[o]);
    addv[o] = 0;
  }
}

void build(int l, int r, int o) {
  if (l == r) {
    coef[o] = l;
    sum[o] = !l;
  } else {
    int mid = l + r >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
    pull(o);
  }
}

void modify(int l, int r, int o, int ql, int qr, int v) {
  if (ql <= l && r <= qr) {
    add(l, r, o, v);
  } else {
    int mid = l + r >> 1;
    push(l, r, o);
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr, v);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    } else {
      modify(l, mid, o << 1, ql, qr, v);
      modify(mid + 1, r, o << 1 | 1, ql, qr, v);
    }
    pull(o);
  }
}

pair<long long, long long> operator + (const pair<long long, long long>& x, const pair<long long, long long>& y) {
  return {x.first + y.first, x.second + y.second};
}

pair<long long, long long> query(int l, int r, int o, int ql, int qr) {
  if (ql > qr) {
    return {0, 0};
  }
  if (ql <= l && r <= qr) {
    return {sum[o], sum2[o]};
  } else {
    int mid = l + r >> 1;
    push(l, r, o);
    if (qr <= mid) {
      return query(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      return query(l, mid, o << 1, ql, qr) + query(mid + 1, r, o << 1 | 1, ql, qr);
    }
  }
}

int main() {
  scanf("%d%*d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    pos[a[i]].push_back(i);
  }
  for (int i = 0; i < n; ++i) {
    if (pos[i].size()) {
      pos[i].push_back(n + 1);
    }
  }
  build(-n, n, 1);
  long long answer = 0;
  for (int i = 0; i < n; ++i) {
    int last = 0, lasts = 0, times = 0;
    vector<pair<int, int>> events;
    for (auto p : pos[i]) {
      int len = p - 1 - last;
      if (len) {
        long long r1 = query(-n, n, 1, -n, lasts - len - 2).first;
        pair<long long, long long> r2 = query(-n, n, 1, lasts - len - 1, lasts - 2);
        answer += r1 * len;
        answer += r2.first * (lasts - 1) - r2.second;
        modify(-n, n, 1, lasts - len, lasts - 1, 1);
        events.emplace_back(lasts - len, lasts - 1);
      }
      ++times;
      last = p;
      lasts = (times << 1) - p;
      if (p != n + 1) {
        answer += query(-n, n, 1, -n, lasts - 1).first;
        modify(-n, n, 1, lasts, lasts, 1);
        events.emplace_back(lasts, lasts);
      }
    }
    for (auto e : events) {
      modify(-n, n, 1, e.first, e.second, -1);
    }
  }
  printf("%lld\n", answer);
  return 0;
}
