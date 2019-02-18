#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

struct event_t {
  int x, y, type, id;
} events[N];

int n, q, m, t, h[N], c[N], answer[N];

void modify(int p, int v) {
  for (; p <= t; p += p & -p) {
    cmax(c[p], v);
  }
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    cmax(result, c[p]);
  }
  return result;
}

int main() {
  scanf("%d%d", &n, &q);
  m = n + q;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &events[i].x, &events[i].y);
    h[++t] = events[i].y;
    events[i].type = 0;
  }
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d", &events[n + i].x, &events[n + i].y);
    h[++t] = events[n + i].y;
    events[n + i].type = 1;
    events[n + i].id = i;
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  for (int i = 1; i <= m; ++i) {
    events[i].y = lower_bound(h + 1, h + 1 + t, events[i].y) - h;
  }
  sort(events + 1, events + 1 + m, [&] (const event_t& a, const event_t& b) {
    return a.x == b.x ? a.type == b.type ? a.y < b.y : a.type < b.type : a.x > b.x;
  });
  for (int i = 1; i <= m; ++i) {
    if (events[i].type == 0) {
      int result = query(events[i].y);
      modify(events[i].y, result + 1);
    } else {
      answer[events[i].id] = query(events[i].y);
    }
  }
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
