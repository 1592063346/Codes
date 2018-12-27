#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 15;
const double pi = acos(-1.0);

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int m, mod, n, o, s, u, rev[N], len, g0[N], g[N], tmp_g[N], f[N], tmp[N], tmp_f[N];

struct point {
  double x, y;

  point () {}
  point (double x, double y): x(x), y(y) {}

  point operator + (const point& a) const {
    return point (x + a.x, y + a.y);
  }

  point operator - (const point& a) const {
    return point (x - a.x, y - a.y);
  }

  point operator * (const point& a) const {
    return point (x * a.x - y * a.y, x * a.y + y * a.x);
  }
} complex_a[N], complex_b[N];

void fft(point* c, int n, int t) {
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(c[i], c[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    point x = point (cos(pi / i), t * sin(pi / i));
    for (int j = 0; j < n; j += i << 1) {
      point y = point (1, 0);
      for (int k = 0; k < i; ++k, y = y * x) {
        point p = c[j + k], q = y * c[i + j + k];
        c[j + k] = p + q;
        c[i + j + k] = p - q;
      }
    }
  }
  if (t == -1) {
    for (int i = 0; i < n; ++i) {
      c[i].x /= n;
    }
  }
}

void mul(int* a, int* b, int* c) {
  for (len = 0; (1 << len) <= m << 1; ++len);
  int n = 1 << len;
  for (int i = 0; i < n; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  for (int i = 0; i < n; ++i) {
    complex_a[i] = complex_b[i] = point (0, 0);
    if (i <= m) {
      complex_a[i].x = a[i];
      complex_b[i].x = b[i];
    }
  }
  fft(complex_a, n, 1);
  fft(complex_b, n, 1);
  for (int i = 0; i < n; ++i) {
    complex_a[i] = complex_a[i] * complex_b[i];
  }
  fft(complex_a, n, -1);
  for (int i = 0; i <= m; ++i) {
    c[i] = (int) (complex_a[i].x + 0.5) % mod;
  }
}

void add(int* a, int* b) {
  for (int i = 0; i <= m; ++i) {
    a[i] = (a[i] + b[i]) % mod;
  }
}

void qpow(int p) {
  if (!p) {
    g[0] = 1;
    return;
  } else {
    qpow(p >> 1);
    memcpy(tmp_f, f, sizeof f);
    memcpy(tmp_g, g, sizeof g);
    if (p & 1) {
      mul(tmp_g, g0, tmp_g);
      add(tmp_f, tmp_g);
    }
    mul(tmp_f, g, tmp_f);
    add(f, tmp_f);
    mul(g, tmp_g, g);
  }
}

int main() {
  scanf("%d%d%d%d%d%d", &m, &mod, &n, &o, &s, &u);
  cmin(n, m);
  for (int i = 1; i <= m; ++i) {
    g0[i] = ((long long) i * i * o + (long long) i * s + u) % mod;
  }
  qpow(n);
  printf("%d\n", f[m]);
  return 0;
}
