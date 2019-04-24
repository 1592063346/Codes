#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, m, sq, a[N], b[N], ll[N], rr[N], xx[N], s[N], c[N], d[N], e[N], extend[N];
vector<int> sub[N];
map<int, int> number;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  sq = sqrt(n);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> ll[i] >> rr[i] >> xx[i];
  }
  for (int l = 1, r; l <= n; l += sq) {
    r = min(n, l + sq - 1);
    int max_rest = 0, all = 0, all_t = 0, part_t = 0;
    for (int i = l; i <= r; ++i) {
      cmax(max_rest, b[i] = a[i]);
    }
    for (int i = 1, j = 1; i <= m; ++i) {
      if (ll[i] <= l && r <= rr[i]) {
        --all;
      } else if (ll[i] <= r && l <= rr[i]) {
        for (int k = max(l, ll[i]); k <= min(r, rr[i]); ++k) {
          ++b[k];
        }
        max_rest = 0;
        for (int k = l; k <= r; ++k) {
          cmax(max_rest, b[k]);
        }
      }
      while (j <= m && max_rest - all > 0) {
        if (ll[j] <= l && r <= rr[j]) {
          ++all;
        } else if (ll[j] <= r && l <= rr[j]) {
          for (int k = max(l, ll[j]); k <= min(r, rr[j]); ++k) {
            --b[k];
          }
          max_rest = 0;
          for (int k = l; k <= r; ++k) {
            cmax(max_rest, b[k]);
          }
        }
        ++j;
      }
      s[i] = s[i - 1];
      if (ll[i] <= l && r <= rr[i]) {
        cmax(extend[i], max_rest - all > 0 ? m + 1 : j - 1);
        c[++all_t] = i;
        ++s[i];
      } else if (ll[i] <= r && l <= rr[i]) {
        d[++part_t] = i;
        e[part_t] = all_t;
      }
    }
    for (int i = l; i <= r; ++i) {
      all = a[i];
      for (int j = 1, k = 1; j <= part_t; ++j) {
        int p = d[j];
        all += s[p] - s[d[j - 1]];
        if (ll[p] <= i && i <= rr[p]) {
          ++all;
          while (k <= part_t && all > 0) {
            all -= s[d[k]] - s[d[k - 1]] + (ll[d[k]] <= i && i <= rr[d[k]]);
            ++k;
          }
          if (all > 0) {
            if (all > s[m] - s[d[part_t]]) {
              cmax(extend[p], m + 1);
            } else {
              cmax(extend[p], c[e[part_t] + all]);
            }
          } else if (all == 0) {
            if (ll[d[k - 1]] <= i && i <= rr[d[k - 1]]) {
              cmax(extend[p], d[k - 1]);
            } else {
              cmax(extend[p], c[e[k - 1]]);
            }
          } else {
            if (ll[d[k - 1]] <= i && i <= rr[d[k - 1]]) {
              cmax(extend[p], c[e[k - 1] + all + 1]);
            } else {
              cmax(extend[p], c[e[k - 1] + all]);
            }
          }
        }
      }
    }
  }
  int answer = 0;
  for (int i = 1; i <= m; ++i) {
    if (!number[xx[i]]++) {
      ++answer;
    }
    sub[extend[i]].push_back(xx[i]);
    for (auto foo : sub[i]) {
      if (!--number[foo]) {
        --answer;
      }
    }
    cout << answer << '\n';
  }
  return 0;
}
