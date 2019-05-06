#include<bits/stdc++.h>

using namespace std;

const int N = 123456;
const long long llinf = 9e18;

struct number_t {
  long long foo, bar;

  number_t() {
  }

  number_t(long long foo, long long bar): foo(foo), bar(bar) {
  }

  bool operator < (const number_t& a) const {
    return (__int128) foo * a.bar < (__int128) bar * a.foo;
  }

  bool operator < (const long long& a) const {
    return foo < (__int128) bar * a;
  }

  bool operator == (const number_t& a) const {
    return (__int128) foo * a.bar == (__int128) bar * a.foo;
  }

  bool operator <= (const number_t& a) const {
    return *this < a || *this == a;
  }

  long long floor() {
    return foo < 0 ? -((-foo - 1) / bar + 1) : foo / bar;
  }

  long long ceil() {
    return foo < 0 ? -(-foo / bar) : foo / bar + (foo % bar ? 1 : 0);
  }
};

struct info_t {
  long long k, b;
  int id;

  bool operator < (const info_t& a) const {
    return k == a.k ? b < a.b : k < a.k;
  }
} info[N];

number_t intersection(info_t x, info_t y) {
  number_t result(y.b - x.b, x.k - y.k);
  if (result.bar < 0) {
    result.foo = -result.foo;
    result.bar = -result.bar;
  }
  return result;
}

int n, m, answer[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.setf(ios::fixed);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> info[i].k >> info[i].b;
    info[i].id = i;
  }
  sort(info + 1, info + 1 + n);
  fill(answer + 1, answer + 1 + n, -1);
  for (int take = 1; take <= m; ++take) {
    vector<info_t> sta;
    for (int i = 1; i <= n; ++i) {
      if (~answer[info[i].id]) {
        continue;
      }
      int j;
      while ((sta.size() && info[i].b > sta.back().b) || ((j = sta.size()) > 1 && intersection(sta[j - 1], info[i]) < intersection(sta[j - 2], sta.back()).ceil())) {
        sta.pop_back();
      }
      sta.push_back(info[i]);
    }
    if (!sta.size()) {
      break;
    }
    vector<pair<long long, int>> covered;
    int number = 0;
    for (int i = 1; i <= n; ++i) {
      if (~answer[info[i].id]) {
        int l = 0, r = sta.size() - 1;
        while (l != r) {
          int mid = (l + r >> 1) + 1;
          if (sta[mid].k >= info[i].k || intersection(sta[mid], info[i]) < intersection(sta[mid], sta[mid - 1])) {
            r = mid - 1;
          } else {
            l = mid;
          }
        }
        if (sta[l].k < info[i].k && intersection(sta[l], info[i]).floor() + 1 >= 0) {
          covered.emplace_back(intersection(sta[l], info[i]).floor() + 1, 1);
        } else {
          ++number;
        }
        l = 0, r = sta.size() - 1;
        while (l != r) {
          int mid = l + r >> 1;
          if (sta[mid].k <= info[i].k || intersection(sta[mid], sta[mid + 1]) < intersection(sta[mid], info[i])) {
            l = mid + 1;
          } else {
            r = mid;
          }
        }
        if (sta[l].k > info[i].k) {
          covered.emplace_back(intersection(sta[l], info[i]).ceil(), -1);
        }
      }
    }
    sort(covered.begin(), covered.end());
    for (int i = 0, j = 0; i < sta.size(); ++i) {
      long long down = i == 0 ? 0 : intersection(sta[i - 1], sta[i]).ceil();
      while (j < covered.size() && covered[j].first <= down) {
        number += covered[j].second;
        ++j;
      }
      int min_number = number;
      long long up = i + 1 < sta.size() ? intersection(sta[i], sta[i + 1]).floor() : llinf;
      while (j < covered.size() && covered[j].first <= up) {
        int k = j;
        while (k < covered.size() && covered[j].first == covered[k].first) {
          number += covered[k].second;
          ++k;
        }
        min_number = min(min_number, number);
        j = k;
      }
      if (min_number == take - 1) {
        answer[sta[i].id] = take;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    cout << answer[i] << " \n"[i == n];
  }
  return 0;
}
