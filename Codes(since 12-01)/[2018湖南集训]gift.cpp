#include<bits/stdc++.h>

using namespace std;

const int N = 2345, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, a[N], b[N], pa[N], pb[N], binom[N][N], s[N][N], fac[N], f[N], g[N], h[N], result[N], new_result[N];
bool visita[N], visitb[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    pa[a[i]] = i;
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    pb[b[i]] = i;
  }
  int x = 0, y = 0, z = 0, w = 0;
  for (int i = 1; i <= n; ++i) {
    if (!a[i] && !b[i]) {
      ++z;
    } else if (!visita[i] && !visitb[i]) {
      bool foo, bar, loop = false;
      int j = i;
      while (1) {
        if (a[j]) {
          if (visita[j]) {
            loop = true;
            break;
          }
          visita[j] = true;
          if (pb[a[j]]) {
            visitb[pb[a[j]]] = true;
            j = pb[a[j]];
          } else {
            foo = true;
            break;
          }
        } else {
          foo = false;
          break;
        }
      }
      if (loop) {
        ++w;
        continue;
      }
      j = i;
      while (1) {
        if (b[j]) {
          visitb[j] = true;
          if (pa[b[j]]) {
            visita[pa[b[j]]] = true;
            j = pa[b[j]];
          } else {
            bar = true;
            break;
          }
        } else {
          bar = false;
          break;
        }
      }
      if (!b[i]) {
        if (foo) {
          ++y;
        } else {
          ++z;
        }
      } else if (!a[i]) {
        if (bar) {
          ++x;
        } else {
          ++z;
        }
      } else {
        if (!foo && !bar) {
          ++z;
        }
        if (foo && !bar) {
          ++y;
        }
        if (!foo && bar) {
          ++x;
        }
      }
    }
  }
  binom[0][0] = s[0][0] = fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
    binom[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
      s[i][j] = (s[i - 1][j - 1] + mul(s[i - 1][j], i - 1)) % mod;
    }
  }
  for (int i = 0; i <= x; ++i) {
    for (int j = i; j <= x; ++j) {
      add(f[i], mul(mul(binom[x][j], s[j][i]), x - j ? mul(binom[x - j + z - 1][x - j], fac[x - j]) : 1));
    }
  }
  for (int i = 0; i <= y; ++i) {
    for (int j = i; j <= y; ++j) {
      add(g[i], mul(mul(binom[y][j], s[j][i]), y - j ? mul(binom[y - j + z - 1][y - j], fac[y - j]) : 1));
    }
  }
  for (int i = 0; i <= z; ++i) {
    h[i] = mul(fac[z], s[z][i]);
  }
  memset(new_result, 0, sizeof new_result);
  for (int i = 0; i <= x; ++i) {
    result[i] = f[i];
    for (int j = 0; j <= y; ++j) {
      add(new_result[i + j], mul(result[i], g[j]));
    }
  }
  memcpy(result, new_result, sizeof new_result);
  memset(new_result, 0, sizeof new_result);
  for (int i = 0; i <= x + y; ++i) {
    for (int j = 0; j <= z; ++j) {
      add(new_result[i + j], mul(result[i], h[j]));
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << (n - i - w >= 0 ? new_result[n - i - w] : 0) << " \n"[i + 1 == n];
  }
  return 0;
}
