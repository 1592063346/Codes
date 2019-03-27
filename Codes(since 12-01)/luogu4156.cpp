#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;
const long long inf = 1e18;

void cmin(long long& x, long long y) {
  if (x > y) {
    x = y;
  }
}

struct border_t {
  vector<int> p;
  int d;

  border_t() {}
  border_t(vector<int> p): p(p) {
    if (p.size() > 1) {
      d = p[1] - p[0];
    } else {
      d = 0;
    }
  }
};

int tt, n, fail[N], ql, qr;
long long w, f[N], g[N];
pair<int, long long> que[N];
char s[N];
bool visit[N];

void get_fail() {
  fail[0] = 0;
  fail[1] = 0;
  for (int i = 1, j; i < n; ++i) {
    for (j = fail[i]; j && s[j] != s[i]; j = fail[j]);
    fail[i + 1] = s[j] == s[i] ? j + 1 : 0;
  }
}

vector<border_t> get_border() {
  get_fail();
  vector<int> pos;
  for (int i = fail[n]; i; i = fail[i]) {
    pos.push_back(n - i);
  }
  vector<border_t> border;
  for (int i = 0, last = 0, diff = -1; i < pos.size(); ++i) {
    if (i + 1 < pos.size() && !~diff) {
      diff = pos[i + 1] - pos[i];
    }
    if (i + 1 == pos.size() || pos[i + 1] - pos[i] != diff) {
      vector<int> p;
      for (int j = last; j <= i; ++j) {
        p.push_back(pos[j]);
      }
      border.emplace_back(p);
      last = i + 1;
      diff = -1;
    }
  }
  return border;
}

void translate(int a, int b, long long* f, long long* g) {
  fill(g, g + b, inf);
  memset(visit, false, sizeof visit);
  for (int i = 0; i < a; ++i) {
    cmin(g[f[i] % b], f[i]);
  }
  for (int i = 0; i < b; ++i) {
    if (!visit[i]) {
      vector<int> pos;
      for (int j = i; !visit[j]; j = (j + a) % b) {
        visit[j] = true;
        pos.push_back(j);
      }
      for (int j = 0, tt = 0; ++tt <= 2 * pos.size(); j = (j + 1) % pos.size()) {
        cmin(g[pos[(j + 1) % pos.size()]], g[pos[j]] + a);
      }
    }
  }
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%lld%s", &n, &w, s);
    vector<border_t> border = get_border();
    fill(f + 1, f + n, inf);
    for (auto info : border) {
      translate(n, info.p[0], f, g);
      memset(visit, false, sizeof visit);
      for (int i = 0; i < info.p[0]; ++i) {
        if (!visit[i]) {
          vector<int> pos;
          for (int j = i; !visit[j]; j = (j + info.d) % info.p[0]) {
            visit[j] = true;
            pos.push_back(j);
          }
          pair<int, long long> ming = {0, inf};
          for (int j = 0; j < pos.size(); ++j) {
            if (g[pos[j]] < ming.second) {
              ming = {j, g[pos[j]]};
            }
          }
          ql = 0;
          qr = 0;
          que[0] = {0, ming.second};
          for (int j = (ming.first + 1) % pos.size(), k = 1; j != ming.first; j = (j + 1) % pos.size(), ++k) {
            for (; k - que[ql].first >= info.p.size(); ++ql);
            cmin(g[pos[j]], k * info.d + info.p[0] + que[ql].second);
            long long x = g[pos[j]] - k * info.d;
            for (; ql <= qr && que[qr].second >= x; --qr);
            que[++qr] = {k, x};
          }
        }
      }
      translate(info.p[0], n, g, f);
    }
    long long answer = 0;
    for (int i = 0; i < n; ++i) {
      answer += f[i] > w - n ? 0 : 1 + (w - n - f[i]) / n;
    }
    printf("%lld\n", answer);
  }
  return 0;
}
