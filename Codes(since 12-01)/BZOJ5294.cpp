#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, a[N];

struct info_t {
  int len, num1, info0[2][2], info1[2][4][2][3];
  long long answer0, answer1;

  info_t operator + (info_t a) {
    info_t result;
    memset(result.info0, 0, sizeof result.info0);
    memset(result.info1, 0, sizeof result.info1);
    result.len = len + a.len;
    result.num1 = num1 + a.num1;
    for (int i = 0; i < 2; ++i) {
      result.info0[0][i] = info0[0][i] + a.info0[0][(num1 & 1) ^ i];
    }
    for (int i = 0; i < 2; ++i) {
      result.info0[1][i] = a.info0[1][i] + info0[1][(a.num1 & 1) ^ i];
    }
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (i == 3) {
          result.info1[0][3][0][j] = info1[0][3][0][j];
          result.info1[0][3][1][j] = info1[0][3][1][j];
        } else {
          result.info1[0][i][i & 1][j] = info1[0][i][i & 1][j];
        }
        if ((i != 3 && i - num1 < 0) || (j != 2 && j - len + num1 < 0)) {
          continue;
        }
        int c = max(0, i - num1), d = max(0, j - len + num1);
        for (int k = c; k <= (i == 3 ? 3 : c); ++k) {
          for (int l = d; l <= (j == 2 ? 2 : d); ++l) {
            if (i == 3) {
              result.info1[0][3][0][j] += a.info1[0][k][num1 & 1][l];
              result.info1[0][3][1][j] += a.info1[0][k][!(num1 & 1)][l];
            } else {
              result.info1[0][i][i & 1][j] += a.info1[0][k][k & 1][l];
            }
          }
        }
      }
    }
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (i == 3) {
          result.info1[1][3][0][j] = a.info1[1][3][0][j];
          result.info1[1][3][1][j] = a.info1[1][3][1][j];
        } else {
          result.info1[1][i][i & 1][j] = a.info1[1][i][i & 1][j];
        }
        if ((i != 3 && i - a.num1 < 0) || (j != 2 && j - a.len + a.num1 < 0)) {
          continue;
        }
        int c = max(0, i - a.num1), d = max(0, j - a.len + a.num1);
        for (int k = c; k <= (i == 3 ? 3 : c); ++k) {
          for (int l = d; l <= (j == 2 ? 2 : d); ++l) {
            if (i == 3) {
              result.info1[1][3][0][j] += info1[1][k][a.num1 & 1][l];
              result.info1[1][3][1][j] += info1[1][k][!(a.num1 & 1)][l];
            } else {
              result.info1[1][i][i & 1][j] += info1[1][k][k & 1][l];
            }
          }
        }
      }
    }
    result.answer0 = answer0 + a.answer0;
    for (int i = 0; i < 2; ++i) {
      result.answer0 += (long long) info0[1][i] * a.info0[0][i];
    }
    result.answer1 = answer1 + a.answer1;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 3; ++j) {
        for (int k = 3; i + k >= 3; --k) {
          for (int l = 2; j + l >= 2; --l) {
            result.answer1 += (long long) info1[1][i][0][j] * a.info1[0][k][1][l] + (long long) info1[1][i][1][j] * a.info1[0][k][0][l];
          }
        }
      }
    }
    return result;
  }
} info[N << 2];

void build(int l, int r, int o) {
  if (l == r) {
    info[o].len = 1;
    info[o].num1 = a[l];
    info[o].info0[0][a[l]] = 1;
    info[o].info0[1][a[l]] = 1;
    if (a[l]) {
      info[o].info1[0][1][1][0] = 1;
      info[o].info1[1][1][1][0] = 1;
    } else {
      info[o].info1[0][0][0][1] = 1;
      info[o].info1[1][0][0][1] = 1;
      info[o].answer0 = 1;
    }
  } else {
    int mid = l + r >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
    info[o] = info[o << 1] + info[o << 1 | 1];
  }
}

void modify(int l, int r, int o, int p) {
  if (l == r) {
    info[o].answer0 = 0;
    info[o].answer1 = 0;
    memset(info[o].info0, 0, sizeof info[o].info0);
    memset(info[o].info1, 0, sizeof info[o].info1);
    info[o].len = 1;
    info[o].num1 = a[l];
    info[o].info0[0][a[l]] = 1;
    info[o].info0[1][a[l]] = 1;
    if (a[l]) {
      info[o].info1[0][1][1][0] = 1;
      info[o].info1[1][1][1][0] = 1;
    } else {
      info[o].info1[0][0][0][1] = 1;
      info[o].info1[1][0][0][1] = 1;
      info[o].answer0 = 1;
    }
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, o << 1, p);
    } else {
      modify(mid + 1, r, o << 1 | 1, p);
    }
    info[o] = info[o << 1] + info[o << 1 | 1];
  }
}

info_t query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return info[o];
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
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  build(1, n, 1);
  scanf("%d", &m);
  while (m--) {
    int opt, l, r;
    scanf("%d", &opt);
    if (opt == 1) {
      scanf("%d", &l);
      a[l] = !a[l];
      modify(1, n, 1, l);
    } else {
      scanf("%d%d", &l, &r);
      info_t result = query(1, n, 1, l, r);
      printf("%lld\n", result.answer0 + result.answer1);
    }
  }
  return 0;
}
