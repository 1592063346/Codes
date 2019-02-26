#include<bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10;

int n;
double k[N << 2], b[N << 2];

double get_y(double k, double b, double x) {
  return k * x + b;
}

void modify(int l, int r, int o, double tk, double tb) {
  if (get_y(k[o], b[o], l) <= get_y(tk, tb, l) && get_y(k[o], b[o], r) <= get_y(tk, tb, r)) {
    k[o] = tk;
    b[o] = tb;
    return;
  } else if (get_y(k[o], b[o], l) >= get_y(tk, tb, l) && get_y(k[o], b[o], r) >= get_y(tk, tb, r)) {
    return;
  } else {
    int mid = l + r >> 1;
    if (get_y(k[o], b[o], mid) >= get_y(tk, tb, mid)) {
      if (get_y(k[o], b[o], l) >= get_y(tk, tb, l)) {
        modify(mid + 1, r, o << 1 | 1, tk, tb);
      } else {
        modify(l, mid, o << 1, tk, tb);
      }
    } else {
      if (get_y(k[o], b[o], r) <= get_y(tk, tb, r)) {
        modify(l, mid, o << 1, k[o], b[o]);
      } else {
        modify(mid + 1, r, o << 1 | 1, k[o], b[o]);
      }
      k[o] = tk;
      b[o] = tb;
    }
  }
}

double query(int l, int r, int o, int p) {
  double result = get_y(k[o], b[o], p);
  if (l == r) {
    return result;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      return max(result, query(l, mid, o << 1, p));
    } else {
      return max(result, query(mid + 1, r, o << 1 | 1, p));
    }
  }
}

int main() {
  scanf("%d", &n);
  while (n--) {
    char opt[10];
    int p;
    double s, t;
    scanf("%s", opt);
    if (*opt == 'Q') {
      scanf("%d", &p);
      printf("%d\n", (int) (query(1, 50000, 1, p) / 100));
    } else {
      scanf("%lf%lf", &s, &t);
      modify(1, 50000, 1, t, s - t);
    }
  }
  return 0;
}
