#include<bits/stdc++.h>

using namespace std;

const int N = 56789, bnum = 3456, bsize = 20;
const long long llinf = 1e18;

double int_x(pair<int, long long> x, pair<int, long long> y) {
  return (double) (y.second - x.second) / (x.first - y.first);
}

long long f(pair<int, long long> foo, long long x) {
  return x * foo.first + foo.second;
}

class convex_t {
 public:
  int x;
  long long y;
  vector<pair<int, long long>> q;

  convex_t() {
  }

  convex_t(vector<pair<int, long long>>& init) {
    q.clear();
    for (int i = 0; i < init.size(); ++i) {
      int j;
      while ((j = q.size()) > 1 && int_x(init[i], q[j - 1]) <= int_x(init[i], q[j - 2])) {
        q.pop_back();
      }
      q.push_back(init[i]);
    }
    x = y = 0;
  }

  void update(int added) {
    y += added;
  }

  long long value() {
    while (x + 1 < q.size() && f(q[x], y) <= f(q[x + 1], y)) {
      ++x;
    }
    return f(q[x], y);
  }
};

int n, m, belong[N];
long long a[N], sum[bnum], psum[N], maxsum[bsize + 10];
convex_t pre[bnum], suf[bnum], all[bnum];

void rebuild(int id) {
  int l = (id - 1) * bsize + 1, r = min(n, id * bsize);
  psum[l - 1] = 0;
  for (int i = l; i <= r; ++i) {
    psum[i] = psum[i - 1] + a[i];
  }
  sum[id] = psum[r];
  fill(maxsum + 1, maxsum + r - l + 2, -llinf);
  vector<pair<int, long long>> pref, suff, allf;
  for (int i = l; i <= r; ++i) {
    pref.emplace_back(i - l + 1, psum[i] - psum[l - 1]);
    suff.emplace_back(r - i + 1, psum[r] - psum[i - 1]);
    for (int j = i; j <= r; ++j) {
      maxsum[j - i + 1] = max(maxsum[j - i + 1], psum[j] - psum[i - 1]);
    }
  }
  for (int i = 1; i <= r - l + 1; ++i) {
    allf.emplace_back(i, maxsum[i]);
  }
  reverse(suff.begin(), suff.end());
  pre[id] = convex_t(pref);
  suf[id] = convex_t(suff);
  all[id] = convex_t(allf);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int l = 1, r; l <= n; l += bsize) {
    r = min(n, l + bsize - 1);
    for (int i = l; i <= r; ++i) {
      belong[i] = l / bsize + 1;
    }
    rebuild(l / bsize + 1);
  }
  while (m--) {
    string opt;
    int l, r, x;
    cin >> opt >> l >> r;
    if (opt[0] == 'A') {
      cin >> x;
      int ll = belong[l], rr = belong[r];
      for (int i = ll + 1; i < rr; ++i) {
        sum[i] += bsize * x;
        pre[i].update(x);
        suf[i].update(x);
        all[i].update(x);
      }
      if (ll == rr) {
        for (int i = (ll - 1) * bsize + 1; i <= min(n, ll * bsize); ++i) {
          a[i] += pre[ll].y + (l <= i && i <= r) * x;
        }
        rebuild(ll);
      } else {
        for (int i = (ll - 1) * bsize + 1; i <= ll * bsize; ++i) {
          a[i] += pre[ll].y + (l <= i && i <= r) * x;
        }
        for (int i = (rr - 1) * bsize + 1; i <= min(n, rr * bsize); ++i) {
          a[i] += pre[rr].y + (l <= i && i <= r) * x;
        }
        rebuild(ll);
        rebuild(rr);
      }
    } else {
      int ll = belong[l], rr = belong[r];
      long long answer = 0, maxpre = 0, maxsuf = 0, maxl = 0, maxr = 0, s = 0;
      for (int i = ll + 1; i < rr; ++i) {
        answer = max(answer, maxsuf + pre[i].value());
        answer = max(answer, all[i].value());
        maxpre = max(maxpre, s + pre[i].value());
        maxsuf = max(maxsuf + sum[i], suf[i].value());
        s += sum[i];
      }
      if (ll == rr) {
        long long foo = 0, bar = 0;
        for (int i = l; i <= r; ++i) {
          foo += a[i] + pre[ll].y;
          bar = min(bar, foo);
          answer = max(answer, foo - bar);
        }
      } else {
        long long foo = 0, bar = 0;
        for (int i = ll * bsize; i >= l; --i) {
          foo += a[i] + pre[ll].y;
          bar = min(bar, foo);
          maxl = max(maxl, foo);
          answer = max(answer, foo - bar);
        }
        foo = bar = 0;
        for (int i = (rr - 1) * bsize + 1; i <= r; ++i) {
          foo += a[i] + pre[rr].y;
          bar = min(bar, foo);
          maxr = max(maxr, foo);
          answer = max(answer, foo - bar);
        }
      }
      answer = max(answer, s + maxl + maxr);
      answer = max(answer, maxl + maxpre);
      answer = max(answer, maxr + maxsuf);
      cout << answer << '\n';
    }
  }
  return 0;
}
