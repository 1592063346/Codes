#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m, q, d[N], opt[N], value[N], numbers[11];

struct info_t {
  int l, r, number;

  info_t() {}
  info_t(int l, int r, int number): l(l), r(r), number(number) {}

  info_t operator + (info_t a) {
    return info_t(l, a.r, number + a.number - (r == 0 && a.l == 0));
  }
} info[N << 2];

void build(int l, int r, int o) {
  if (l == r) {
    info[o] = info_t(value[l] != 0, value[l] != 0, value[l] == 0);
  } else {
    int mid = l + r >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
    info[o] = info[o << 1] + info[o << 1 | 1];
  }
}

void modify(int l, int r, int o, int p) {
  if (l == r) {
    info[o] = info_t(value[l] != 0, value[l] != 0, value[l] == 0);
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

void modify(int p) {
  --numbers[value[p]];
  if (opt[p]) {
    value[p] = d[p] * d[p == 1 ? m : p - 1] % 10;
  } else {
    value[p] = (d[p] + d[p == 1 ? m : p - 1]) % 10;
  }
  ++numbers[value[p]];
  modify(1, m, 1, p);
}

bool check(int p, int len) {
  int l = p + len, r = p - len + n;
  info_t result = query(1, m, 1, l, r);
  if (result.number > 2) {
    return true;
  } else if (result.number == 2) {
    if (result.l == 0 && result.r == 0 && value[l == 1 ? m : l - 1] == 0 && value[r == m ? 1 : r + 1] == 0) {
      return false;
    } else {
      return true;
    }
  } else if (result.number == 1) {
    if ((result.l == 0 && value[l == 1 ? m : l - 1] == 0) || (result.r == 0 && value[r == m ? 1 : r + 1] == 0)) {
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

int main() {
  scanf("%d%d", &n, &q);
  m = n << 1;
  for (int i = 1; i <= n; ++i) {
    char type[3];
    scanf("%d%s", &d[i], type);
    opt[i] = *type == '*';
    d[n + i] = d[i];
    opt[n + i] = opt[i];
  }
  for (int i = 1; i <= m; ++i) {
    if (opt[i]) {
      value[i] = d[i] * d[i == 1 ? m : i - 1] % 10;
    } else {
      value[i] = (d[i] + d[i == 1 ? m : i - 1]) % 10;
    }
    ++numbers[value[i]];
  }
  build(1, m, 1);
  while (q--) {
    int op, pos, x;
    char type[3];
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d%s", &pos, &x, type);
      ++pos;
      d[pos] = d[n + pos] = x;
      opt[pos] = opt[n + pos] = *type == '*';
      modify(pos);
      modify(pos + 1);
      modify(n + pos);
      modify(pos == n ? 1 : n + pos + 1);
    } else {
      scanf("%d", &pos);
      ++pos;
      int old = value[pos];
      numbers[value[pos]] -= 2;
      numbers[d[pos]] += 2;
      value[pos] = d[pos];
      value[n + pos] = d[pos];
      if (!numbers[0]) {
        puts("-1");
      } else {
        int l = 0, r = n >> 1;
        while (l != r) {
          int mid = (l + r >> 1) + 1;
          if (!check(pos, mid)) {
            r = mid - 1;
          } else {
            l = mid;
          }
        }
        printf("%d\n", l);
      }
      value[pos] = old;
      value[n + pos] = old;
      numbers[d[pos]] -= 2;
      numbers[value[pos]] += 2;
    }
  }
  return 0;
}
