#include<bits/stdc++.h>

using namespace std;

const int N = 8e3 + 10, mod = 1e9 + 7;
const vector<pair<int, int>> step = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

int r, p[4], a[N][N], n;

pair<int, int> operator + (const pair<int, int>& a, const pair<int, int>& b) {
  return {a.first + b.first, a.second + b.second};
}

int main() {
  scanf("%d%d%d%d%d", &r, &p[0], &p[1], &p[2], &p[3]);
  int total = qpow(p[0] + p[1] + p[2] + p[3], mod - 2);
  for (int i = 0; i < 4; ++i) {
    p[i] = mul(p[i], total);
  }
  vector<pair<int, int>> points;
  for (int i = -r; i <= r; ++i) {
    for (int j = -r; j <= r; ++j) {
      if (i * i + j * j <= r * r) {
        points.emplace_back(i, j);
      }
    }
  }
  n = points.size();
  for (int i = 0; i < n; ++i) {
    pair<int, int> point = points[i];
    a[i][i] = a[i][n] = 1;
    for (int j = 0; j < 4; ++j) {
      pair<int, int> newp = point + step[j];
      if (newp.first * newp.first + newp.second * newp.second <= r * r) {
        int id = lower_bound(points.begin(), points.end(), newp) - points.begin();
        a[i][id] = mod - p[j];
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    int rev = i;
    for (int j = i + 1; j < n; ++j) {
      if (a[j][i]) {
        rev = j;
      }
    }
    if (rev != i) {
      for (int j = i; j <= n; ++j) {
        swap(a[i][j], a[rev][j]);
      }
    }
    vector<int> need;
    for (int j = i; j <= n; ++j) {
      if (a[i][j]) {
        need.push_back(j);
      }
    }
    int inv = qpow(a[i][i], mod - 2);
    for (int j = i + 1; j < n; ++j) {
      int coef = mul(a[j][i], inv);
      if (coef) {
        for (auto x : need) {
          sub(a[j][x], mul(a[i][x], coef));
        }
      }
    }
  }
  for (int i = n - 1; ~i; --i) {
    for (int j = i + 1; j < n; ++j) {
      sub(a[i][n], mul(a[i][j], a[j][n]));
    }
    a[i][n] = mul(a[i][n], qpow(a[i][i], mod - 2));
  }
  printf("%d\n", a[lower_bound(points.begin(), points.end(), pair<int, int>(0, 0)) - points.begin()][n]);
  return 0;
}
