#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, q, a[N], answer;
vector<int> pos_set[N << 2];

int cmp(const int* buffer1, const int* buffer2, int len) {
  --len;
  for (; len && *buffer1 == *buffer2; ++buffer1, ++buffer2, --len);
  return *buffer1 - *buffer2;
}

void push_up(int l, int r, int o) {
  pos_set[o] = pos_set[o << 1 | 1];
  for (auto p : pos_set[o << 1]) {
    while (1) {
      int p2 = pos_set[o].back(), result;
      if ((result = cmp(a + p, a + p2, r - p2 + 1)) > 0) {
        break;
      } else if (result == 0) {
        if ((r - p2 + 1 << 1) > r - p + 1) {
          pos_set[o].pop_back();
        }
        pos_set[o].push_back(p);
        break;
      } else {
        pos_set[o].pop_back();
        if (pos_set[o].empty()) {
          pos_set[o].push_back(p);
          break;
        }
      }
    }
  }
}

void build(int l, int r, int o) {
  if (l == r) {
    pos_set[o].push_back(l);
  } else {
    int mid = l + r >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
    push_up(l, r, o);
  }
}

void modify(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    return;
  } else {
    int mid = l + r >> 1;
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      modify(l, mid, o << 1, ql, qr);
      modify(mid + 1, r, o << 1 | 1, ql, qr);
    }
    push_up(l, r, o);
  }
}

void query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    for (auto p : pos_set[o]) {
      int result;
      if ((result = cmp(a + p, a + answer, qr - max(answer, p) + 1)) != 0) {
        if (result < 0) {
          answer = p;
        }
      } else {
        answer = max(answer, p);
      }
    }
  } else {
    int mid = l + r >> 1;
    if (qr <= mid) {
      query(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      query(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      query(l, mid, o << 1, ql, qr);
      query(mid + 1, r, o << 1 | 1, ql, qr);
    }
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  build(1, n, 1);
  while (q--) {
    int opt, l, r, v;
    scanf("%d%d%d", &opt, &l, &r);
    if (opt == 1) {
      scanf("%d", &v);
      for (int i = l; i <= r; ++i) {
        a[i] += v;
      }
      modify(1, n, 1, l, r);
    } else {
      answer = r;
      query(1, n, 1, l, r);
      printf("%d\n", answer);
    }
  }
  return 0;
}
