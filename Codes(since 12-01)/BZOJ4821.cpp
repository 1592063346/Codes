#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, x[N], y[N];
long long sumx[N << 2], sumy[N << 2], addx[N << 2], addy[N << 2], s1, s2;
double sumxy[N << 2], sumx2[N << 2], s3, s4;
bool tag[N << 2];

void push_up(int o) {
  sumx[o] = sumx[o << 1] + sumx[o << 1 | 1];
  sumy[o] = sumy[o << 1] + sumy[o << 1 | 1];
  sumxy[o] = sumxy[o << 1] + sumxy[o << 1 | 1];
  sumx2[o] = sumx2[o << 1] + sumx2[o << 1 | 1];
}

void build(int l, int r, int o) {
  if (l == r) {
    sumx[o] = x[l];
    sumy[o] = y[l];
    sumxy[o] = (double) x[l] * y[l];
    sumx2[o] = (double) x[l] * x[l];
  } else {
    int mid = l + r >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
    push_up(o);
  }
}

long long sum(int l, int r) {
  return (long long) (r - l + 1) * (l + r) >> 1;
}

double sum2(int l, int r) {
  --l;
  double suml = (double) l * (l + 1) * (2 * l + 1) / 6;
  double sumr = (double) r * (r + 1) * (2 * r + 1) / 6;
  return sumr - suml;
}

void cover(int l, int r, int o) {
  tag[o] = true;
  addx[o] = 0;
  addy[o] = 0;
  sumx[o] = sum(l, r);
  sumy[o] = sum(l, r);
  sumxy[o] = sum2(l, r);
  sumx2[o] = sum2(l, r);
}

void add(int l, int r, int o, long long a, long long b) {
  addx[o] += a;
  addy[o] += b;
  sumxy[o] += (double) sumx[o] * b + (double) sumy[o] * a + (double) a * b * (r - l + 1);
  sumx2[o] += (double) sumx[o] * a * 2 + (double) a * a * (r - l + 1);
  sumx[o] += a * (r - l + 1);
  sumy[o] += b * (r - l + 1);
}

void push_down(int l, int r, int o) {
  int mid = l + r >> 1;
  if (tag[o]) {
    cover(l, mid, o << 1);
    cover(mid + 1, r, o << 1 | 1);
    tag[o] = false;
  }
  if (addx[o] || addy[o]) {
    add(l, mid, o << 1, addx[o], addy[o]);
    add(mid + 1, r, o << 1 | 1, addx[o], addy[o]);
    addx[o] = 0;
    addy[o] = 0;
  }
}

void modify_add(int l, int r, int o, int ql, int qr, int a, int b) {
  if (ql <= l && r <= qr) {
    add(l, r, o, a, b);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (qr <= mid) {
      modify_add(l, mid, o << 1, ql, qr, a, b);
    } else if (ql > mid) {
      modify_add(mid + 1, r, o << 1 | 1, ql, qr, a, b);
    } else {
      modify_add(l, mid, o << 1, ql, qr, a, b);
      modify_add(mid + 1, r, o << 1 | 1, ql, qr, a, b);
    }
    push_up(o);
  }
}

void modify_cover(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    cover(l, r, o);
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
    if (qr <= mid) {
      modify_cover(l, mid, o << 1, ql, qr);
    } else if (ql > mid) {
      modify_cover(mid + 1, r, o << 1 | 1, ql, qr);
    } else {
      modify_cover(l, mid, o << 1, ql, qr);
      modify_cover(mid + 1, r, o << 1 | 1, ql, qr);
    }
    push_up(o);
  }
}

void query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) {
    s1 += sumx[o];
    s2 += sumy[o];
    s3 += sumxy[o];
    s4 += sumx2[o];
  } else {
    int mid = l + r >> 1;
    push_down(l, r, o);
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
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &y[i]);
  }
  build(1, n, 1);
  while (m--) {
    int opt, l, r, a, b;
    scanf("%d%d%d", &opt, &l, &r);
    if (opt == 1) {
      s1 = 0;
      s2 = 0;
      s3 = 0;
      s4 = 0;
      query(1, n, 1, l, r);
      double c = s3 - (double) s1 * s2 / (r - l + 1);
      double d = s4 - (double) s1 * s1 / (r - l + 1);
      printf("%.10lf\n", c / d);
    } else if (opt == 2) {
      scanf("%d%d", &a, &b);
      modify_add(1, n, 1, l, r, a, b);
    } else {
      scanf("%d%d", &a, &b);
      modify_cover(1, n, 1, l, r);
      modify_add(1, n, 1, l, r, a, b);
    }
  }
  return 0;
}
