#include<bits/stdc++.h>

using namespace std;

#define rg register

typedef long long ll;

int T;

struct Matrix {
  int x1, y1, x2, y2;
  Matrix () {}
  Matrix operator & (const Matrix& a) const {
    Matrix res;
    res.x1 = max(x1, a.x1);
    res.y1 = max(y1, a.y1);
    res.x2 = min(x2, a.x2);
    res.y2 = min(y2, a.y2);
    return res;
  }
  inline ll s() {
    return 1ll * (x2 - x1 + 1) * (y2 - y1 + 1);
  }
  inline ll f() {
    if (((x1 & 1) && (y1 & 1)) || (!(x1 & 1) && !(y1 & 1))) {
      return 1ll * (y2 - y1 + 1 >> 1) * (x2 - x1 + 1) + (y2 - y1 + 1 & 1) * (x2 - x1 + 1 >> 1);
    } else {
      return 1ll * (y2 - y1 + 2 >> 1) * (x2 - x1 + 1) - (y2 - y1 + 1 & 1) * (x2 - x1 + 1 >> 1);
    }
  }
} a, b, c, d;

int main() {
  scanf("%d", &T);
  for (rg int i = 1; i <= T; ++i) {
    int n, m; scanf("%d%d%d%d%d%d%d%d%d%d", &n, &m, &a.x1, &a.y1, &a.x2, &a.y2, &b.x1, &b.y1, &b.x2, &b.y2);
    c.x1 = 1, c.y1 = 1, c.x2 = n, c.y2 = m;
    ll black_num = c.f();
    black_num -= a.f();
    black_num += b.s() - b.f();
    d = a & b;
    if (d.x1 <= d.x2 && d.y1 <= d.y2) {
      black_num += d.f();
    }
    printf("%I64d %I64d\n", c.s() - black_num, black_num);
  }
  return 0;
}
