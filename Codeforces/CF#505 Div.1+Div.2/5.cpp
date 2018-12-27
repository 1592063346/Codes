#include<bits/stdc++.h>

using namespace std;

const int N = 55;

struct state {
  int x, y, id;
} begin_t[N], end_t[N];

int n, m;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &begin_t[i].x, &begin_t[i].y);
    begin_t[i].id = i;
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &end_t[i].x, &end_t[i].y);
    end_t[i].id = i;
  }
  function<vector<vector<int>> (state*)> calc = [&] (state* info) {
    sort(info + 1, info + 1 + m, [&] (const state& a, const state& b) {
      return a.x < b.x;
    });
    vector<vector<int>> event;
    while (1) {
      bool need = false;
      for (int i = 1; i <= m; ++i) {
        if (info[i].x > i) {
          event.push_back({info[i].x, info[i].y, info[i].x - 1, info[i].y});
          if (--info[i].x > i) {
            need = true;
          }
        }
      }
      for (int i = m; i; --i) {
        if (info[i].x < i) {
          event.push_back({info[i].x, info[i].y, info[i].x + 1, info[i].y});
          if (++info[i].x < i) {
            need = true;
          }
        }
      }
      if (!need) {
        break;
      }
    }
    for (int i = 1; i <= m; ++i) {
      for (; info[i].y < info[i].id; ++info[i].y) {
        event.push_back({info[i].x, info[i].y, info[i].x, info[i].y + 1});
      }
      for (; info[i].y > info[i].id; --info[i].y) {
        event.push_back({info[i].x, info[i].y, info[i].x, info[i].y - 1});
      }
    }
    for (int i = 1; i <= m; ++i) {
      for (; info[i].x < info[i].id; ++info[i].x) {
        event.push_back({info[i].x, info[i].y, info[i].x + 1, info[i].y});
      }
      for (; info[i].x > info[i].id; --info[i].x) {
        event.push_back({info[i].x, info[i].y, info[i].x - 1, info[i].y});
      }
    }
    return event;
  };
  vector<vector<int>> ans_begin = calc(begin_t);
  vector<vector<int>> ans_end = calc(end_t);
  reverse(ans_end.begin(), ans_end.end());
  printf("%d\n", ans_begin.size() + ans_end.size());
  for (auto step : ans_begin) {
    printf("%d %d %d %d\n", step[0], step[1], step[2], step[3]);
  }
  for (auto step : ans_end) {
    printf("%d %d %d %d\n", step[2], step[3], step[0], step[1]);
  }
  return 0;
}
