#include<bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

void cmax(long long& x, long long y) {
  if (x < y) {
    x = y;
  }
}

void cmin(long long& x, long long y) {
  if (x > y) {
    x = y;
  }
}

struct state {
  long long a;
  int b, c;
  state () {}
  state (long long a, int b, int c): a(a), b(b), c(c) {}
  bool operator < (const state& other) const {
    return a < other.a;
  }
};

int n, nodes, size[N], w[N], tag[N], root;
long long k, ans = 1e18;
vector<pair<int, long long> > graph[N];
vector<state> que;

void get_root(int u, int pa) {
  size[u] = 1;
  w[u] = 0;
  for (auto v : graph[u]) {
    if (!tag[v.first] && v.first ^ pa) {
      get_root(v.first, u);
      cmax(w[u], size[v.first]);
      size[u] += size[v.first];
    }
  }
  cmax(w[u], nodes - size[u]);
  if (w[u] < w[root]) {
    root = u;
  }
}

void solve(int u, int pa, long long value, int nodes, int anc) {
  que.emplace_back(value, nodes, anc);
  for (auto v : graph[u]) {
    if (!tag[v.first] && v.first ^ pa) {
      solve(v.first, u, value + v.second, nodes + 1, anc);
    }
  }
}

bool check(long long x) {
  int p = que.size() - 1;
  pair<long long, int> maxp_0(-1e18, -1);
  pair<long long, int> maxp_1(-1e18, -1);
  pair<long long, int> minp_0(1e18, -1);
  pair<long long, int> minp_1(1e18, -1);
  for (int i = 0; i < que.size(); ++i) {
    state v = que[i];
    for (; ~p && que[p].a + v.a >= 0; --p) {
      long long value = x * que[p].b - que[p].a;
      if (value > maxp_0.first && que[p].c ^ maxp_0.second) {
        maxp_1 = maxp_0;
        maxp_0 = pair<long long, int> (value, que[p].c);
      } else if (que[p].c == maxp_0.second) {
        cmax(maxp_0.first, value);
      } else if (value > maxp_1.first && que[p].c ^ maxp_0.second) {
        maxp_1 = pair<long long, int> (value, que[p].c);
      }
    }
    if (v.a - x * v.b < (v.c == maxp_0.second ? maxp_1.first : maxp_0.first)) {
      return true;
    }
  }
  p = 0;
  for (int i = que.size() - 1; ~i; --i) {
    state v = que[i];
    for (; p < que.size() && que[p].a + v.a <= 0; ++p) {
      long long value = -(que[p].a + x * que[p].b);
      if (value < minp_0.first && que[p].c ^ minp_0.second) {
        minp_1 = minp_0;
        minp_0 = pair<long long, int> (value, que[p].c);
      } else if (que[p].c == minp_0.second) {
        cmin(minp_0.first, value);
      } else if (value < minp_1.first && que[p].c ^ minp_0.second) {
        minp_1 = pair<long long, int> (value, que[p].c);
      }
    }
    if (v.a + x * v.b > (v.c == minp_0.second ? minp_1.first : minp_0.first)) {
      return true;
    }
  }
  return false;
}

void solve(int u) {
  tag[u] = 1;
  que.clear();
  que.emplace_back(0, 0, 0);
  for (auto v : graph[u]) {
    if (!tag[v.first]) {
      solve(v.first, u, v.second, 1, v.first);
    }
  }
  sort(que.begin(), que.end());
  long long l = 0, r = 1e13;
  while (l ^ r) {
    long long mid = l + r >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cmin(ans, l);
  int old = nodes;
  for (auto v : graph[u]) {
    if (!tag[v.first]) {
      if (size[v.first] > size[u]) {
        nodes = old - size[u];
      } else {
        nodes = size[v.first];
      }
      root = 0;
      get_root(v.first, 0);
      solve(root);
    }
  }
}

int main() {
  scanf("%d%lld", &n, &k);
  for (int i = 1; i < n; ++i) {
    int u, v;
    long long w;
    scanf("%d%d%lld", &u, &v, &w);
    w -= k;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }
  w[0] = nodes = n;
  get_root(1, 0);
  solve(root);
  printf("%lld\n", ans - 1);
  return 0;
}
