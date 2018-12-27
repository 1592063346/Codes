#include<bits/stdc++.h>

using namespace std;

const int N = 132680;

struct matrix {
  int x1, y1, x2, y2;

  matrix () {}
  matrix (int x1, int y1, int x2, int y2): x1(x1), y1(y1), x2(x2), y2(y2) {}

  matrix operator + (const matrix& another) const {
    matrix res;
    res.x1 = max(x1, another.x1);
    res.x2 = min(x2, another.x2);
    res.y1 = max(y1, another.y1);
    res.y2 = min(y2, another.y2);
    return res;
  }
} t[N], pre_t[N], suf_t[N];

int n;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d%d", &t[i].x1, &t[i].y1, &t[i].x2, &t[i].y2);
  }
  pre_t[0] = suf_t[n + 1] = matrix (-1e9, -1e9, 1e9, 1e9);
  for (int i = 1; i <= n; ++i) {
    pre_t[i] = pre_t[i - 1] + t[i];
  }
  for (int i = n; i; --i) {
    suf_t[i] = suf_t[i + 1] + t[i];
  }
  for (int i = 1; i <= n; ++i) {
    matrix result = pre_t[i - 1] + suf_t[i + 1];
    if (result.x1 <= result.x2 && result.y1 <= result.y2) {
      return printf("%d %d\n", result.x1, result.y1), 0;
    }
  }
  return 0;
}
