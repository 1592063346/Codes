#include<bits/stdc++.h>

using namespace std;

const int N = 123456, limit = 100000;

class bit {
  long long a[N];

 public:
  bit() {
    memset(a, 0, sizeof a);
  }

  void modify(int x, long long y) {
    while (x <= limit) {
      a[x] = max(a[x], y);
      x += x & -x;
    }
  }

  long long query(int x) {
    long long result = 0;
    while (x) {
      result = max(result, a[x]);
      x -= x & -x;
    }
    return result;
  }
};

struct node_t {
  int l, r, k;
  long long b;

  node_t() {
  }

  node_t(int k, long long b): k(k), b(b) {
    l = r = 0;
  }

  long long get(int x) {
    return (long long) k * x + b;
  }
};

long long get(int k, int x, long long b) {
  return (long long) k * x + b;
}

class segment_t {
  int root[N], tt;
  node_t nodes[N * 20];

 public:
  segment_t() {
    memset(root, 0, sizeof root);
    tt = 0;
  }

  void insert(int l, int r, int& x, int k, long long b) {
    if (!x) {
      nodes[x = ++tt] = node_t(k, b);
      return;
    }
    if (get(k, l, b) >= nodes[x].get(l) && get(k, r, b) >= nodes[x].get(r)) {
      nodes[x].k = k;
      nodes[x].b = b;
      return;
    } else if (get(k, l, b) <= nodes[x].get(l) && get(k, r, b) <= nodes[x].get(r)) {
      return;
    } else {
      int mid = l + r >> 1;
      if (nodes[x].get(mid) >= get(k, mid, b)) {
        if (nodes[x].get(l) >= get(k, l, b)) {
          insert(mid + 1, r, nodes[x].r, k, b);
        } else {
          insert(l, mid, nodes[x].l, k, b);
        }
      } else {
        if (nodes[x].get(r) <= get(k, r, b)) {
          insert(l, mid, nodes[x].l, nodes[x].k, nodes[x].b);
        } else {
          insert(mid + 1, r, nodes[x].r, nodes[x].k, nodes[x].b);
        }
        nodes[x].k = k;
        nodes[x].b = b;
      }
    }
  }

  long long query(int l, int r, int x, int y) {
    if (!x) {
      return 0;
    } else {
      long long result = nodes[x].get(y);
      if (l == r) {
        return result;
      } else {
        int mid = l + r >> 1;
        return max(result, y <= mid ? query(l, mid, nodes[x].l, y) : query(mid + 1, r, nodes[x].r, y));
      }
    }
  }

  void modify(int x, int k, long long b) {
    while (x) {
      insert(1, limit, root[x], k, b);
      x -= x & -x;
    }
  }

  long long query(int x) {
    int y = x;
    long long result = 0;
    while (x <= limit) {
      result = max(result, query(1, limit, root[x], y));
      x += x & -x;
    }
    return result;
  }
};

int n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  vector<pair<pair<int, int>, int>> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first.first >> a[i].first.second >> a[i].second;
    --a[i].first.first;
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i].first.first >> b[i].first.second >> b[i].second;
    --b[i].first.first;
  }
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  auto solve = [&] (vector<pair<pair<int, int>, int>> a, vector<pair<pair<int, int>, int>> b) {
    long long answer = 0;
    bit t1;
    segment_t t2;
    for (int i = n - 1, j = n - 1; ~i; --i) {
      while (~j && b[j].first.first >= a[i].first.first) {
        t1.modify(b[j].first.second, (long long) (b[j].first.second - b[j].first.first) * b[j].second);
        t2.modify(b[j].first.second, b[j].second, -b[j].first.first * (long long) b[j].second);
        --j;
      }
      answer = max(answer, t1.query(a[i].first.second) * a[i].second);
      answer = max(answer, t2.query(a[i].first.second) * a[i].second);
    }
    return answer;
  };
  cout << max(solve(a, b), solve(b, a)) << '\n';
  return 0;
}
