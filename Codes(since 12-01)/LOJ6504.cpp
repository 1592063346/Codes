#include<bits/stdc++.h>

using namespace std;

const int N = 15e4 + 10, M = 387;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

struct point_t {
  int x, y;

  point_t() {}
  point_t(int x, int y): x(x), y(y) {}

  point_t operator - (point_t a) {
    return point_t(x - a.x, y - a.y);
  }
} p[N];

long long cross(point_t a, point_t b) {
  return (long long) a.x * b.y - (long long) a.y * b.x;
}

int n, m, id[N], pre[N], suf[N], sta[N], tt;
vector<pair<pair<int, int>, int>> queries[N];
long long answer[N], area;
double angle[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &p[i].x, &p[i].y);
    angle[i] = atan2(p[i].y, p[i].x);
  }
  for (int i = 1; i <= n; ++i) {
    id[i] = i;
  }
  sort(id + 1, id + 1 + n, [&] (const int& x, const int& y) {
    return angle[x] < angle[y];
  });
  for (int i = 1; i <= m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    queries[l / M].emplace_back(make_pair(l, r), i);
  }
  for (int i = 0; i <= n / M; ++i) {
    if (!queries[i].size()) {
      continue;
    }
    sort(queries[i].begin(), queries[i].end(), [&] (const pair<pair<int, int>, int>& x, const pair<pair<int, int>, int>& y) {
      return x.first.second > y.first.second;
    });
    int l = n, r = queries[i][0].first.second, ql = 0, qr = 0;
    for (auto q : queries[i]) {
      cmin(l, q.first.first);
    }
    tt = area = 0;
    for (int j = 1; j <= n; ++j) {
      if (id[j] >= l && id[j] <= r) {
        if (qr) {
          suf[qr] = id[j];
          pre[id[j]] = qr;
          area += cross(p[qr], p[id[j]]);
        } else {
          ql = id[j];
        }
        qr = id[j];
      }
    }
    pre[ql] = qr;
    suf[qr] = ql;
    area += cross(p[qr], p[ql]);
    auto del = [&] (int x, bool sure = true) {
      int pp = pre[x], ss = suf[x];
      suf[pp] = ss;
      pre[ss] = pp;
      area -= cross(p[pp], p[x]);
      area -= cross(p[x], p[ss]);
      area += cross(p[pp], p[ss]);
      if (!sure) {
        sta[++tt] = x;
      }
    };
    auto add = [&] (int x) {
      int pp = pre[x], ss = suf[x];
      suf[pp] = x;
      pre[ss] = x;
      area -= cross(p[pp], p[ss]);
      area += cross(p[pp], p[x]);
      area += cross(p[x], p[ss]);
    };
    for (auto q : queries[i]) {
      while (r > q.first.second) {
        del(r--);
      }
      for (int j = l; j < q.first.first; ++j) {
        del(j, false);
      }
      answer[q.second] = area;
      while (tt) {
        add(sta[tt--]);
      }
    }
  }
  for (int i = 1; i <= m; ++i) {
    printf("%lld\n", answer[i]);
  }
  return 0;
}
