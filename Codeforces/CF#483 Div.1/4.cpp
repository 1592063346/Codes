#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, xl[N], xr[N], yl[N], yr[N], min_color[N << 2], max_color[N << 2];
bool seen[N], disappeared[N];
vector<int> x, y;
vector<pair<int, int>> event[N];
set<int> colors[N << 2];

#define lo (o<<1)
#define ro (o<<1|1)

void push_up(int o, bool leaf = false) {
  while (colors[o].size() && disappeared[*colors[o].rbegin()]) {
    colors[o].erase(*colors[o].rbegin());
  }
  int max_son = leaf ? -1 : max(max_color[lo], max_color[ro]);
  int min_son = leaf ? -1 : min(min_color[lo], min_color[ro]);
  int max_now = colors[o].size() ? *colors[o].rbegin() : -1;
  if (max_now > max_son) {
    if (seen[max_now] || max_now < min_son) {
      max_color[o] = -1;
    } else {
      max_color[o] = max_now;
    }
  } else {
    max_color[o] = max_son;
  }
  min_color[o] = max(max_now, min_son);
}

void modify(int l, int r, int o, int ql, int qr, int color = 0) {
  if (ql <= l && r <= qr) {
    if (color) {
      colors[o].insert(color);
    }
    push_up(o, l == r);
  } else {
    int mid = l + r >> 1;
    if (ql <= mid) {
      modify(l, mid, lo, ql, qr, color);
    } if (qr > mid) {
      modify(mid + 1, r, ro, ql, qr, color);
    }
    push_up(o);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d%d", &xl[i], &yl[i], &xr[i], &yr[i]);
    x.push_back(xl[i]);
    x.push_back(xr[i]);
    y.push_back(yl[i]);
    y.push_back(yr[i]);
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  x.erase(unique(x.begin(), x.end()), x.end());
  y.erase(unique(y.begin(), y.end()), y.end());
  for (int i = 1; i <= n; ++i) {
    xl[i] = lower_bound(x.begin(), x.end(), xl[i]) - x.begin();
    xr[i] = lower_bound(x.begin(), x.end(), xr[i]) - x.begin();
    yl[i] = lower_bound(y.begin(), y.end(), yl[i]) - y.begin();
    yr[i] = lower_bound(y.begin(), y.end(), yr[i]) - y.begin();
    event[xl[i]].emplace_back(i, -1);
    event[xr[i]].emplace_back(i, 1);
  }
  memset(min_color, -1, sizeof min_color);
  memset(max_color, -1, sizeof max_color);
  for (int i = 0; i < x.size(); ++i) {
    for (auto v : event[i]) {
      if (v.second == 1) {
        disappeared[v.first] = true;
        modify(0, y.size() - 1, 1, yl[v.first], yr[v.first] - 1);
      } else {
        modify(0, y.size() - 1, 1, yl[v.first], yr[v.first] - 1, v.first);
      }
    }
    while (~max_color[1] && max_color[1] >= min_color[1]) {
      int color = max_color[1];
      seen[color] = true;
      modify(0, y.size() - 1, 1, yl[color], yr[color] - 1);
    }
  }
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    if (seen[i]) {
      ++answer;
    }
  }
  printf("%d\n", answer + 1);
  return 0;
}
