#include<bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10;
const long long inf = 1e18;

void cmax(long long& x, long long y) {
  if (x < y) {
    x = y;
  }
}

int m, p;

struct info_t {
  vector<pair<int, int>> items;
  long long f[N][505];

  void init() {
    for (int i = 1; i < p; ++i) {
      f[0][i] = -inf;
    }
  }

  void push(pair<int, int> item) {
    items.push_back(item);
    int total = items.size();
    for (int i = 0; i < p; ++i) {
      f[total][i] = f[total - 1][i];
    }
    for (int i = 0; i < p; ++i) {
      cmax(f[total][(i + item.first) % p], f[total - 1][i] + item.second);
    }
  }

  void pop() {
    items.pop_back();
  }
} info1, info2;

void rebuild() {
  vector<pair<int, int>> items;
  if (!info1.items.size()) {
    items = info2.items;
    info2.items.clear();
  } else {
    items = info1.items;
    info1.items.clear();
    reverse(items.begin(), items.end());
  }
  int mid = items.size() >> 1;
  for (int i = mid; ~i; --i) {
    info1.push(items[i]);
  }
  for (int i = mid + 1; i < items.size(); ++i) {
    info2.push(items[i]);
  }
}

long long query(int l, int r) {
  long long answer = -inf;
  deque<int> que;
  int total1 = info1.items.size(), total2 = info2.items.size();
  for (int i = 0, j = r + p, k = r + p; i < p; ++i, --k) {
    if (!que.empty() && que.front() > k) {
      que.pop_front();
    }
    for (; j >= l + p - i; --j) {
      for (; !que.empty() && info2.f[total2][j % p] >= info2.f[total2][que.back() % p]; que.pop_back());
      que.push_back(j);
    }
    cmax(answer, info1.f[total1][i] + info2.f[total2][que.front() % p]);
  }
  return answer < 0 ? -1 : answer;
}

int main() {
  scanf("%*d%d%d", &m, &p);
  info1.init();
  info2.init();
  for (int i = 1; i <= m; ++i) {
    char opt[3];
    int x, y;
    scanf("%s", opt);
    if (*opt == 'I') {
      scanf("%d%d", &x, &y);
      x %= p;
      if (opt[1] == 'F') {
        info1.push({x, y});
      } else {
        info2.push({x, y});
      }
    } else if (*opt == 'D') {
      if (opt[1] == 'F') {
        if (!info1.items.size()) {
          rebuild();
        }
        if (!info1.items.size()) {
          info2.pop();
        } else {
          info1.pop();
        }
      } else {
        if (!info2.items.size()) {
          rebuild();
        }
        if (!info2.items.size()) {
          info1.pop();
        } else {
          info2.pop();
        }
      }
    } else {
      scanf("%d%d", &x, &y);
      printf("%lld\n", query(x, y));
    }
  }
  return 0;
}
