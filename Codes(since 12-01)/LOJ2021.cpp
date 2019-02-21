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
map<int, bool> s[N][N], appeared, mem[N];

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
  s[0][0][1] = true;
  mem[0][1] = true;
  for (int i = 0; i < max_days - 1; ++i) {
    for (int j = 0; j <= i; ++j) {
      for (auto p : s[i][j]) {
        if (!mem[j + 1].count(p.first)) {
          mem[j + 1][p.first] = true;
          s[i + 1][j + 1][p.first] = true;
        }
        if ((long long) p.first * j <= 1e8) {
          if (!mem[j].count(p.first * j)) {
            mem[j][p.first * j] = true;
            s[i + 1][j][p.first * j] = true;
          }
        }
      }
    }
  }
  vector<pair<int, int>> all;
  for (int i = 0; i < max_days; ++i) {
    for (int j = 0; j <= i; ++j) {
      for (auto p : s[i][j]) {
        if (!appeared.count(p.first)) {
          appeared[p.first] = true;
          all.emplace_back(p.first, p.first - i - 1);
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
