#include<bits/stdc++.h>

using namespace std;

const int N = 156789;

class my_array {
 public:
  int a[N << 2];

  int& operator [] (int x) {
    return a[N + x];
  }
};

class segment_t {
 public:
  int ll, rr, lazy[N << 4];
  pair<int, int> value[N << 4];

  segment_t(int ll, int rr): ll(ll), rr(rr) {
    init(ll, rr, 1);
  }

  void pull(int o) {
    value[o].first = min(value[o << 1].first, value[o << 1 | 1].first);
    value[o].second = 0;
    if (value[o].first == value[o << 1].first) {
      value[o].second += value[o << 1].second;
    }
    if (value[o].first == value[o << 1 | 1].first) {
      value[o].second += value[o << 1 | 1].second;
    }
  }

  void addt(int o, int x) {
    lazy[o] += x;
    value[o].first += x;
  }

  void push(int o) {
    if (lazy[o]) {
      addt(o << 1, lazy[o]);
      addt(o << 1 | 1, lazy[o]);
      lazy[o] = 0;
    }
  }

  void init(int l, int r, int o) {
    if (l == r) {
      value[o] = {0, 1};
    } else {
      int mid = l + r >> 1;
      init(l, mid, o << 1);
      init(mid + 1, r, o << 1 | 1);
      pull(o);
    }
  }

  void modify(int l, int r, int o, int ql, int qr, int x) {
    if (ql <= l && r <= qr) {
      addt(o, x);
    } else {
      int mid = l + r >> 1;
      push(o);
      if (qr <= mid) {
        modify(l, mid, o << 1, ql, qr, x);
      } else if (ql > mid) {
        modify(mid + 1, r, o << 1 | 1, ql, qr, x);
      } else {
        modify(l, mid, o << 1, ql, qr, x);
        modify(mid + 1, r, o << 1 | 1, ql, qr, x);
      }
      pull(o);
    }
  }

  pair<int, int> query(int l, int r, int o, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return value[o];
    } else {
      int mid = l + r >> 1;
      push(o);
      if (qr <= mid) {
        return query(l, mid, o << 1, ql, qr);
      } else if (ql > mid) {
        return query(mid + 1, r, o << 1 | 1, ql, qr);
      } else {
        pair<int, int> info_l = query(l, mid, o << 1, ql, qr);
        pair<int, int> info_r = query(mid + 1, r, o << 1 | 1, ql, qr);
        if (info_l.first != info_r.first) {
          return info_l.first < info_r.first ? info_l : info_r;
        } else {
          return {info_l.first, info_l.second + info_r.second};
        }
      }
    }
  }

  void modify(int ql, int qr, int x) {
    modify(ll, rr, 1, ql, qr, x);
  }

  pair<int, int> query(int ql, int qr) {
    return query(ll, rr, 1, ql, qr);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m, tag = 0;
  cin >> n >> m;
  vector<int> a(n);
  segment_t tree(-(n + m), n + m);
  my_array number;
  auto add = [&] (int x) {
    ++number[x];
    if (x + tag >= 0 && x + tag < n) {
      tree.modify(x - number[x] + 1, x - number[x] + 1, 1);
    }
  };
  auto del = [&] (int x) {
    if (x + tag >= 0 && x + tag < n) {
      tree.modify(x - number[x] + 1, x - number[x] + 1, -1);
    }
    --number[x];
  };
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    --a[i];
    add(a[i]);
  }
  for (int i = 0, p, x; i < m; ++i) {
    cin >> p >> x;
    if (p) {
      --p;
      --x;
      del(a[p]);
      add(a[p] = x - tag);
    } else {
      if (x == 1) {
        if (number[n - 1 - tag]) {
          tree.modify(n - 1 - tag - number[n - 1 - tag] + 1, n - 1 - tag, -1);
        }
        ++tag;
        if (number[-tag]) {
          tree.modify(-tag - number[-tag] + 1, -tag, 1);
        }
      } else {
        if (number[-tag]) {
          tree.modify(-tag - number[-tag] + 1, -tag, -1);
        }
        --tag;
        if (number[n - 1 - tag]) {
          tree.modify(n - 1 - tag - number[n - 1 - tag] + 1, n - 1 - tag, 1);
        }
      }
    }
    pair<int, int> result = tree.query(-tag, n - 1 - tag);
    cout << (result.first == 0) * result.second << '\n';
  }
  return 0;
}
