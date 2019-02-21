#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, M = 316;

int p, m, n, _remainder[N], in_block[N], times[N];
long long result, answer[N];
char s[N];
bool e[N];
pair<pair<int, int>, int> queries[N];
pair<int, long long> tnode[N << 2];

pair<int, long long> operator + (const pair<int, long long>& a, const pair<int, long long>& b) {
  return {a.first + b.first, a.second + b.second};
}

void add(int v) {
  result += times[v]++;
}

void del(int v) {
  result -= --times[v];
}

void modify(int l, int r, int o, int p, pair<int, long long> v) {
  tnode[o] = tnode[o] + v;
  if (l == r) {
    return;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, o << 1, p, v);
    } else {
      modify(mid + 1, r, o << 1 | 1, p, v);
    }
  }
}

pair<int, long long> query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return tnode[o];
  } else {
    int mid = l + r >> 1;
    if (qr <= mid) {
      return query(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      return query(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      return query(l, mid, o << 1, ql, qr) + query(mid + 1, r, o << 1 | 1, ql, qr);
    }
  }
}

int main() {
  scanf("%d%s%d", &p, s + 1, &m);
  n = strlen(s + 1);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &queries[i].first.first, &queries[i].first.second);
    queries[i].second = i;
  }
  if (p == 2 || p == 5) {
    if (p == 2) {
      e['2'] = true;
      e['4'] = true;
      e['6'] = true;
      e['8'] = true;
      e['0'] = true;
    } else {
      e['5'] = true;
      e['0'] = true;
    }
    sort(queries + 1, queries + 1 + m, [&] (const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
      return a.first.second < b.first.second;
    });
    for (int i = 1, j = 1; i <= n; ++i) {
      if (e[s[i]]) {
        modify(1, n, 1, i, {1, i});
      }
      for (; j <= m && queries[j].first.second == i; ++j) {
        pair<int, long long> p = query(1, n, 1, queries[j].first.first, n);
        answer[queries[j].second] = p.second - (long long) (queries[j].first.first - 1) * p.first;
      }
    }
  } else {
    ++n;
    _remainder[n] = 0;
    vector<int> h(1, 0);
    for (int i = n - 1, b = 10; i; --i, b = b * 10 % p) {
      _remainder[i] = ((s[i] - '0') * b % p + _remainder[i + 1]) % p;
      h.push_back(_remainder[i]);
    }
    sort(h.begin(), h.end());
    for (int i = 1; i <= n; ++i) {
      _remainder[i] = lower_bound(h.begin(), h.end(), _remainder[i]) - h.begin();
    }
    for (int i = 1; i <= n; ++i) {
      in_block[i] = (i - 1) / M + 1;
    }
    for (int i = 1; i <= m; ++i) {
      ++queries[i].first.second;
    }
    sort(queries + 1, queries + 1 + m, [&] (const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
      return in_block[a.first.first] == in_block[b.first.first] ? a.first.second < b.first.second : in_block[a.first.first] < in_block[b.first.first];
    });
    int ql = 1, qr = 0;
    for (int i = 1; i <= m; ++i) {
      for (; qr < queries[i].first.second; add(_remainder[++qr]));
      for (; qr > queries[i].first.second; del(_remainder[qr--]));
      for (; ql < queries[i].first.first; del(_remainder[ql++]));
      for (; ql > queries[i].first.first; add(_remainder[--ql]));
      answer[queries[i].second] = result;
    }
  }
  for (int i = 1; i <= m; ++i) {
    printf("%lld\n", answer[i]);
  }
  return 0;
}
