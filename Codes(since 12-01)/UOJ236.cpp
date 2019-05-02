#include "railroad.h"
#include<bits/stdc++.h>

using namespace std;

const int N = 456789, inf = 1e9 + 1;

int h[N], foo[N], father[N], tt;

long long plan_roller_coaster(vector<int> s, vector<int> t) {
  s.push_back(inf);
  t.push_back(1);
  int n = s.size();
  for (int i = 0; i < n; ++i) {
    h[++tt] = s[i];
    h[++tt] = t[i];
  }
  sort(h + 1, h + 1 + tt);
  tt = unique(h + 1, h + 1 + tt) - h - 1;
  for (int i = 1; i <= tt; ++i) {
    father[i] = i;
  }
  for (int i = 0; i < n; ++i) {
    s[i] = lower_bound(h + 1, h + 1 + tt, s[i]) - h;
    t[i] = lower_bound(h + 1, h + 1 + tt, t[i]) - h;
    ++foo[s[i]];
    --foo[t[i]];
  }
  int bar = tt;
  function<int (int)> find = [&] (int x) {
    return father[x] == x ? x : father[x] = find(father[x]);
  };
  auto merge = [&] (int x, int y) {
    if (find(x) != find(y)) {
      father[find(x)] = find(y);
      --bar;
      return true;
    } else {
      return false;
    }
  };
  for (int i = 0; i < n; ++i) {
    merge(s[i], t[i]);
  }
  long long answer = 0;
  vector<pair<int, int>> edges;
  for (int i = 1; i < tt; ++i) {
    foo[i] += foo[i - 1];
    if (foo[i] > 0) {
      answer += (long long) (h[i + 1] - h[i]) * foo[i];
      merge(i, i + 1);
    } else if (foo[i] < 0) {
      merge(i, i + 1);
    } else {
      edges.emplace_back(i, i + 1);
    }
  }
  sort(edges.begin(), edges.end(), [&] (const pair<int, int>& x, const pair<int, int>& y) {
    return h[x.second] - h[x.first] < h[y.second] - h[y.first];
  });
  for (auto e : edges) {
    if (bar == 1) {
      break;
    }
    if (merge(e.first, e.second)) {
      answer += h[e.second] - h[e.first];
    }
  }
  return answer;
}
