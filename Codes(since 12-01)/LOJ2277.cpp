#include<bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10, mod = 998244353;

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

long long n, m, r;
int o, size[1 << 16], g[62][62][62], binom[62][62], f[N];

struct info_t {
  long long x, y, z;
} points[N];

void binom_init() {
  binom[0][0] = 1;
  for (int i = 1; i <= 61; ++i) {
    for (int j = 0; j <= i; ++j) {
      binom[i][j] = (binom[i - 1][j] + (!j ? 0 : binom[i - 1][j - 1])) % mod;
    }
  }
}

int get_bit(long long x) {
  return size[x & 0xffff] + size[x >> 16 & 0xffff] + size[x >> 32 & 0xffff] + size[x >> 48 & 0xffff];
}

int main() {
  scanf("%lld%lld%lld%d", &n, &m, &r, &o);
  for (int i = 1; i <= o; ++i) {
    scanf("%lld%lld%lld", &points[i].x, &points[i].y, &points[i].z);
  }
  ++o;
  points[o].x = n;
  points[o].y = m;
  points[o].z = r;
  sort(points + 1, points + o + 1, [&] (const info_t& a, const info_t& b) {
    if (a.x != b.x) {
      return a.x < b.x;
    }
    if (a.y != b.y) {
      return a.y < b.y;
    }
    return a.z < b.z;
  });
  binom_init();
  g[0][0][0] = 1;
  for (int i = 0; i < 62; ++i) {
    for (int j = 0; j < 62; ++j) {
      for (int k = 0; k < 62; ++k) {
        for (int l = 0; l < i; ++l) {
          add(g[i][j][k], mul(g[l][j][k], binom[i][l]));
        }
        for (int l = 0; l < j; ++l) {
          add(g[i][j][k], mul(g[i][l][k], binom[j][l]));
        }
        for (int l = 0; l < k; ++l) {
          add(g[i][j][k], mul(g[i][j][l], binom[k][l]));
        }
      }
    }
  }
  for (int i = 1; i < 1 << 16; ++i) {
    size[i] = size[i - (i & -i)] + 1;
  }
  for (int i = 1; i <= o; ++i) {
    long long x = points[i].x;
    long long y = points[i].y;
    long long z = points[i].z;
    f[i] = g[get_bit(x)][get_bit(y)][get_bit(z)];
    for (int j = 1; j < i; ++j) {
      if ((x & points[j].x) == points[j].x && (y & points[j].y) == points[j].y && (z & points[j].z) == points[j].z) {
        sub(f[i], mul(f[j], g[get_bit(x ^ points[j].x)][get_bit(y ^ points[j].y)][get_bit(z ^ points[j].z)]));
      }
    }
  }
  printf("%d\n", f[o]);
  return 0;
}
