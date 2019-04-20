#include<bits/stdc++.h>

using namespace std;

const long long llinf = 1e12;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, sq;
  cin >> n;
  ++n;
  sq = sqrt(n);
  vector<int> belong(n), p(n / sq + 1);
  vector<vector<int>> convex(n / sq + 1);
  vector<long long> f(n, llinf), s(n / sq + 1), t(n / sq + 1);
  f[0] = 0;
  function<void (int)> push = [&] (int id) {
    int l = id * sq, r = min(n - 1, (id + 1) * sq - 1);
    for (int i = l; i <= r; ++i) {
      f[i] += s[id] * i + t[id];
    }
    s[id] = t[id] = 0;
  };
  auto slope = [&] (int id, int i, int j) {
    double yi = f[i] + t[id];
    double yj = f[j] + t[id];
    return (yi - yj) / (i - j);
  };
  function<void (int)> rebuild = [&] (int id) {
    int l = id * sq, r = min(n - 1, (id + 1) * sq - 1);
    convex[id].clear();
    for (int i = l, j; i <= r; ++i) {
      while ((j = convex[id].size()) > 1 && slope(id, i, convex[id][j - 2]) <= slope(id, convex[id][j - 1], convex[id][j - 2])) {
        convex[id].pop_back();
      }
      convex[id].push_back(i);
    }
    p[id] = convex[id].size() - 1;
    while (p[id] && slope(id, convex[id][p[id] - 1], convex[id][p[id]]) >= -s[id]) {
      --p[id];
    }
  };
  for (int l = 0, r = sq - 1; l < n; l = r + 1, r = min(n - 1, l + sq - 1)) {
    for (int i = l; i <= r; ++i) {
      belong[i] = l / sq;
    }
    rebuild(l / sq);
  }
  auto query = [&] (int l, int r) {
    int bl = belong[l], br = belong[r];
    long long result = llinf;
    for (int i = bl + 1; i < br; ++i) {
      result = min(result, f[convex[i][p[i]]] + s[i] * convex[i][p[i]] + t[i]);
    }
    if (bl == br) {
      for (int i = l; i <= r; ++i) {
        result = min(result, f[i] + s[bl] * i + t[bl]);
      }
    } else {
      for (int i = l; i <= (bl + 1) * sq - 1; ++i) {
        result = min(result, f[i] + s[bl] * i + t[bl]);
      }
      for (int i = br * sq; i <= r; ++i) {
        result = min(result, f[i] + s[br] * i + t[br]);
      }
    }
    return result;
  };
  function<void (int, int, int, int)> modify = [&] (int l, int r, int ss, int tt) {
    if (l > r) {
      return;
    }
    int bl = belong[l], br = belong[r];
    for (int i = bl + 1; i < br; ++i) {
      s[i] += ss;
      t[i] += tt;
      while (p[i] && slope(i, convex[i][p[i] - 1], convex[i][p[i]]) >= -s[i]) {
        --p[i];
      }
    }
    if (bl == br) {
      push(bl);
      for (int i = l; i <= r; ++i) {
        f[i] += ss * i + tt;
      }
      rebuild(bl);
    } else {
      push(bl);
      push(br);
      for (int i = l; i <= (bl + 1) * sq - 1; ++i) {
        f[i] += ss * i + tt;
      }
      for (int i = br * sq; i <= r; ++i) {
        f[i] += ss * i + tt;
      }
      rebuild(bl);
      rebuild(br);
    }
  };
  int max_value = 0;
  for (int i = 1, x; i < n; ++i) {
    cin >> x;
    max_value = max(max_value, x);
    long long minj = query(0, x);
    push(belong[x]);
    f[x] = minj + x;
    rebuild(belong[x]);
    modify(0, x - 1, 0, max_value);
    modify(x + 1, n - 1, 1, 0);
  }
  cout << query(0, n - 1) << '\n';
  return 0;
}
