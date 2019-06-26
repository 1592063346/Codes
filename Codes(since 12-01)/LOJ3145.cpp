#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

struct edge_t {
  int x, y, z;

  bool operator < (const edge_t& a) const {
    return z < a.z;
  }
} foo[N], bar[N];

int n, m, q, old[N], father[N], size[N], answer[N];
pair<int, pair<int, int>> events[N];
bool ban[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    cin >> foo[i].x >> foo[i].y >> foo[i].z;
    old[i] = foo[i].z;
  }
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> events[i].first >> events[i].second.first >> events[i].second.second;
  }
  for (int l = 1, r; l <= q; l = r + 1) {
    r = min(q, l + 999);
    for (int i = 1; i <= n; ++i) {
      father[i] = i;
      size[i] = 1;
    }
    vector<int> queries, updates;
    for (int i = l; i <= r; ++i) {
      if (events[i].first == 1) {
        ban[events[i].second.first] = true;
        updates.push_back(events[i].second.first);
      } else {
        queries.push_back(i);
      }
    }
    int tt = 0;
    for (int i = 1; i <= m; ++i) {
      foo[i].z = old[i];
    }
    for (int i = 1; i <= m; ++i) {
      if (!ban[i]) {
        bar[++tt] = foo[i];
      }
    }
    sort(bar + 1, bar + 1 + tt);
    function<int (int, bool)> find = [&] (int x, bool remain) {
      return father[x] == x ? x : (remain ? father[x] = find(father[x], remain) : find(father[x], remain));
    };
    sort(queries.begin(), queries.end(), [&] (const int& x, const int& y) {
      return events[x].second.second > events[y].second.second;
    });
    for (auto x : queries) {
      vector<pair<int, int>> sta;
      auto merge = [&] (int x, int y, bool remain) {
        x = find(x, remain);
        y = find(y, remain);
        if (x != y) {
          if (size[x] > size[y]) {
            swap(x, y);
          }
          father[x] = y;
          size[y] += size[x];
          if (!remain) {
            sta.emplace_back(x, y);
          }
        }
      };
      while (tt && bar[tt].z >= events[x].second.second) {
        merge(bar[tt].x, bar[tt].y, true);
        --tt;
      }
      for (int i = l; i <= x; ++i) {
        if (events[i].first == 1) {
          foo[events[i].second.first].z = events[i].second.second;
        }
      }
      int here = sta.size();
      for (auto y : updates) {
        if (foo[y].z >= events[x].second.second) {
          merge(foo[y].x, foo[y].y, false);
        }
      }
      answer[x] = size[find(events[x].second.first, false)];
      for (auto y : updates) {
        foo[y].z = old[y];
      }
      while (sta.size() > here) {
        size[sta.back().second] -= size[sta.back().first];
        father[sta.back().first] = sta.back().first;
        sta.pop_back();
      }
    }
    for (auto x : updates) {
      ban[x] = false;
    }
    for (int i = l; i <= r; ++i) {
      if (events[i].first == 1) {
        old[events[i].second.first] = events[i].second.second;
      }
    }
  }
  for (int i = 1; i <= q; ++i) {
    if (events[i].first == 2) {
      cout << answer[i] << '\n';
    }
  }
  return 0;
}
