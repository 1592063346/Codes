#include<bits/stdc++.h>

using namespace std;

const int N = 123456;
const long long llinf = 1e18;

int n, l, father[N], padd[N], psub[N], ps[N], id[N];
long long s[N], d[N];
vector<pair<int, int>> adj[N];
vector<int> dir;
bool on_dir[N];

class bit {
 public:
  long long maxv[N];

  void reset() {
    fill(maxv, maxv + N, -llinf);
  }

  void insert(int x, long long y) {
    while (x <= n) {
      maxv[x] = max(maxv[x], y);
      x += x & -x;
    }
  }

  long long query(int x) {
    long long result = -llinf;
    while (x) {
      result = max(result, maxv[x]);
      x -= x & -x;
    }
    return result;
  }
} tadd, tsub;

pair<long long, int> operator + (pair<long long, int> x, long long y) {
  return pair<long long, int>(x.first + y, x.second);
}

pair<long long, int> dfs(int x, int f) {
  father[x] = f;
  pair<long long, int> d(0, x);
  for (auto e : adj[x]) {
    int y = e.first;
    if (y != f && !on_dir[y]) {
      d = max(d, dfs(y, x) + e.second);
    }
  }
  return d;
}

vector<int> get_dir() {
  int x = dfs(1, 0).second;
  int y = dfs(x, 0).second;
  vector<int> result;
  for (; y != x; y = father[y]) {
    result.push_back(y);
  }
  result.push_back(x);
  return result;
}

bool check(long long w) {
  long long max0 = -llinf, max1 = -llinf, max2 = -llinf, max3 = -llinf;
  tadd.reset();
  tsub.reset();
  for (int i = 0, j = dir.size() - 1; i < dir.size(); ++i) {
    int x = padd[i];
    while (~j && d[x] + s[x] + d[psub[j]] - s[psub[j]] > w) {
      int y = psub[j];
      tadd.insert(id[y], d[y] + s[y]);
      tsub.insert(id[y], d[y] - s[y]);
      --j;
    }
    max0 = max(max0, d[x] + s[x] - w + l + tadd.query(id[x] - 1));
    max1 = max(max1, d[x] + s[x] - w + l + tsub.query(id[x] - 1));
    max2 = max(max2, d[x] - s[x] - w + l + tadd.query(id[x] - 1));
    max3 = max(max3, d[x] - s[x] - w + l + tsub.query(id[x] - 1));
  }
  int p0 = dir.size(), p1 = 0, p2 = -1, p3 = dir.size() - 1;
  for (int i = 0; i < dir.size(); ++i) {
    int x = ps[i];
    while (p0 - 1 >= 0 && s[x] + s[ps[p0 - 1]] >= max0) {
      --p0;
    }
    while (p1 < dir.size() && -s[x] + s[ps[p1]] < max1) {
      ++p1;
    }
    while (p2 + 1 < dir.size() && s[x] - s[ps[p2 + 1]] >= max2) {
      ++p2;
    }
    while (p3 >= 0 && -s[x] - s[ps[p3]] < max3) {
      --p3;
    }
    if (max(p0, p1) <= min(p2, p3)) {
      return true;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  while (cin >> n >> l) {
    if (!n) {
      break;
    }
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
    }
    int maxe = 0;
    for (int i = 1, x, y, z; i < n; ++i) {
      cin >> x >> y >> z;
      maxe = max(maxe, z);
      adj[x].emplace_back(y, z);
      adj[y].emplace_back(x, z);
    }
    memset(on_dir, false, sizeof on_dir);
    dir = get_dir();
    for (auto x : dir) {
      on_dir[x] = true;
    }
    for (int i = 1; i < dir.size(); ++i) {
      int x = dir[i - 1], y = dir[i];
      for (auto e : adj[x]) {
        if (e.first == y) {
          s[y] = s[x] + e.second;
          break;
        }
      }
    }
    for (int i = 0; i < dir.size(); ++i) {
      d[dir[i]] = dfs(dir[i], 0).first;
    }
    for (int i = 0; i < dir.size(); ++i) {
      id[dir[i]] = i + 1;
      padd[i] = psub[i] = ps[i] = dir[i];
    }
    sort(padd, padd + dir.size(), [&] (const int& x, const int& y) {
      return d[x] + s[x] < d[y] + s[y];
    });
    sort(psub, psub + dir.size(), [&] (const int& x, const int& y) {
      return d[x] - s[x] < d[y] - s[y];
    });
    sort(ps, ps + dir.size(), [&] (const int& x, const int& y) {
      return s[x] < s[y];
    });
    long long ll = 0, rr = (long long) maxe * n;
    while (ll != rr) {
      long long mid = ll + rr >> 1;
      if (check(mid)) {
        rr = mid;
      } else {
        ll = mid + 1;
      }
    }
    cout << ll << '\n';
  }
  return 0;
}
