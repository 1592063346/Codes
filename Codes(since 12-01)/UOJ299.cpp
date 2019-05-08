#include<bits/stdc++.h>

using namespace std;

const int N = 234567;

struct matrix_t {
  double a[2][2];

  matrix_t() {
    memset(a, 0, sizeof a);
  }

  double* operator [] (int x) {
    return a[x];
  }

  matrix_t operator + (matrix_t b) {
    matrix_t result;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        result[i][j] = a[i][j] + b[i][j];
      }
    }
    return result;
  }

  matrix_t operator * (matrix_t b) {
    matrix_t result;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 2; ++k) {
          result[i][j] += a[i][k] * b[k][j];
        }
      }
    }
    return result;
  }
};

struct info_t {
  matrix_t foo, bar;

  info_t operator + (info_t a) {
    info_t result;
    result.foo = foo * a.foo;
    result.bar = foo * a.bar + bar * a.foo;
    return result;
  }
};

int n, m;
double p[N][2];

class segment_t {
 public:
  info_t info[N << 2];

  void build(int l, int r, int x) {
    if (l == r) {
      info[x].foo[0][0] = 1 - p[l][0];
      info[x].foo[0][1] = info[x].bar[0][1] = p[l][0];
      info[x].foo[1][0] = 1 - p[l][1];
      info[x].foo[1][1] = info[x].bar[1][1] = p[l][1];
    } else {
      int mid = l + r >> 1;
      build(l, mid, x << 1);
      build(mid + 1, r, x << 1 | 1);
      info[x] = info[x << 1] + info[x << 1 | 1];
    }
  }

  info_t query(int l, int r, int x, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return info[x];
    } else {
      int mid = l + r >> 1;
      if (qr <= mid) {
        return query(l, mid, x << 1, ql, qr);
      } else if (ql > mid) {
        return query(mid + 1, r, x << 1 | 1, ql, qr);
      } else {
        return query(l, mid, x << 1, ql, qr) + query(mid + 1, r, x << 1 | 1, ql, qr);
      }
    }
  }

  info_t query(int l, int r) {
    return query(0, n + 1, 1, l, r);
  }
} tree;

double get(pair<int, int> l, pair<int, int> r) {
  info_t result = tree.query(l.first + 1, r.first);
  return result.bar[l.second][r.second] / result.foo[l.second][r.second];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.setf(ios::fixed);
  string type;
  cin >> n >> m >> type >> p[1][0];
  for (int i = 2; i <= n; ++i) {
    cin >> p[i][1] >> p[i][0];
  }
  p[n + 1][0] = p[n + 1][1] = 0;
  tree.build(0, n + 1, 1);
  set<pair<int, int>> now;
  now.emplace(0, 0);
  now.emplace(n + 1, 0);
  double answer = get(pair<int, int>(0, 0), pair<int, int>(n + 1, 0));
  while (m--) {
    int i, c;
    cin >> type >> i;
    if (type == "add") {
      cin >> c;
      set<pair<int, int>>::iterator rr = now.lower_bound(pair<int, int>(i, 0)), ll = rr;
      --ll;
      answer -= get(*ll, *rr);
      answer += get(*ll, pair<int, int>(i, c));
      answer += get(pair<int, int>(i, c), *rr);
      now.emplace(i, c);
    } else {
      pair<int, int> x = *now.lower_bound(pair<int, int>(i, 0));
      now.erase(now.lower_bound(pair<int, int>(i, 0)));
      set<pair<int, int>>::iterator rr = now.lower_bound(pair<int, int>(i, 0)), ll = rr;
      --ll;
      answer -= get(*ll, x);
      answer -= get(x, *rr);
      answer += get(*ll, *rr);
    }
    cout << setprecision(6) << answer << '\n';
  }
  return 0;
}
