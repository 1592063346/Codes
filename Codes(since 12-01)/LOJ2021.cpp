#include<bits/stdc++.h>

using namespace std;

const int N = 1e2 + 10, M = 1e6 + 10;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, m, mc, a[N], w[N], f[N][N];
unordered_map<int, bool> appeared, mem[N];

struct state_t {
  int t, level, v;

  state_t() {}
  state_t(int t, int level, int v): t(t), level(level), v(v) {}
};

int main() {
  scanf("%d%d%d", &n, &m, &mc);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &w[i]);
  }
  memset(f, 0x3f, sizeof f);
  f[0][mc] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = a[i + 1]; j <= mc; ++j) {
      cmin(f[i + 1][j - a[i + 1]], f[i][j]);
      cmin(f[i + 1][min(mc, j - a[i + 1] + w[i + 1])], f[i][j] + 1);
    }
  }
  int max_days = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= mc; ++j) {
      cmax(max_days, i - f[i][j]);
    }
  }
  cerr << max_days << "\n";
  queue<state_t> que;
  vector<pair<int, int>> all;
  que.emplace(0, 0, 1);
  mem[0][1] = true;
  appeared[1] = true;
  all.emplace_back(1, 0);
  while (!que.empty()) {
    state_t s = que.front();
    que.pop();
    if (s.t < max_days - 1) {
      que.emplace(s.t + 1, s.level + 1, s.v);
      if ((long long) s.v * s.level <= 1e8 && !mem[s.level].count(s.v * s.level)) {
        mem[s.level][s.v * s.level] = true;
        que.emplace(s.t + 1, s.level, s.v * s.level);
        if (!appeared.count(s.v * s.level)) {
          appeared[s.v * s.level] = true;
          all.emplace_back(s.v * s.level, s.v * s.level - s.t - 2);
        }
      }
    }
  }
  sort(all.begin(), all.end());
  while (m--) {
    int c;
    scanf("%d", &c);
    bool can = appeared[c] || max_days >= c;
    for (int i = 0, j = all.size() - 1; !can && i < all.size(); ++i) {
      for (; ~j && all[i].first + all[j].first > c; --j);
      if (all[i].first + all[j].first <= c && all[i].second + all[j].second + max_days >= c) {
        can = true;
      }
    }
    puts(can ? "1" : "0");
  }
  return 0;
}
