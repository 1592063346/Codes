#include<bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10, M = 224;

int n, q, a[N], block[N], times[2][N];
long long answer[N];

struct query_t {
  int l, r, id, coef;

  query_t() {}
  query_t(int l, int r, int id, int coef): l(l), r(r), id(id), coef(coef) {}
};

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    block[i] = (i - 1) / M + 1;
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  scanf("%d", &q);
  vector<query_t> queries;
  for (int i = 1; i <= q; ++i) {
    int l1, r1, l2, r2;
    scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
    queries.emplace_back(r1, r2, i, 1);
    if (l1 != 1) {
      queries.emplace_back(l1 - 1, r2, i, -1);
    }
    if (l2 != 1) {
      queries.emplace_back(r1, l2 - 1, i, -1);
    }
    if (l1 != 1 && l2 != 1) {
      queries.emplace_back(l1 - 1, l2 - 1, i, 1);
    }
  }
  sort(queries.begin(), queries.end(), [&] (const query_t& a, const query_t& b) {
    return block[a.l] == block[b.l] ? a.r < b.r : block[a.l] < block[b.l];
  });
  int ql = 0, qr = 0;
  long long result = 0;
  for (auto info : queries) {
    for (; ql < info.l; ++ql) {
      result += times[1][a[ql + 1]];
      ++times[0][a[ql + 1]];
    }
    for (; ql > info.l; --ql) {
      result -= times[1][a[ql]];
      --times[0][a[ql]];
    }
    for (; qr < info.r; ++qr) {
      result += times[0][a[qr + 1]];
      ++times[1][a[qr + 1]];
    }
    for (; qr > info.r; --qr) {
      result -= times[0][a[qr]];
      --times[1][a[qr]];
    }
    answer[info.id] += info.coef * result;
  }
  for (int i = 1; i <= q; ++i) {
    printf("%lld\n", answer[i]);
  }
  return 0;
}
