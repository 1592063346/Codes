#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int n, m, q, id[N];
char s[N][N], go[N];
string t[N];

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i] + 1);
  }
  for (int i = 1; i <= m; ++i) {
    t[i].resize(n);
    for (int j = 0; j < n; ++j) {
      t[i][j] = s[n - j - 1][i];
    }
  }
  for (int i = 1; i <= m; ++i) {
    id[i] = i;
  }
  sort(id + 1, id + 1 + m, [&] (const int& x, const int& y) {
    return t[x] < t[y];
  });
  t[0].resize(n);
  t[m + 1].resize(n);
  for (int i = 0; i < n; ++i) {
    t[0][i] = '0';
    t[m + 1][i] = '1';
  }
  while (q--) {
    scanf("%s", go + 1);
    int l = 0, r = m + 1;
    for (int i = m; i; --i) {
      if (go[id[i]] == '1') {
        r = id[i];
      }
    }
    for (int i = 1; i <= m; ++i) {
      if (go[id[i]] == '0') {
        l = id[i];
      }
    }
    if (t[l] > t[r]) {
      puts("0");
    } else {
      int l_value = 0, r_value = 0;
      for (int i = 0, j = 1; i < n; ++i, j = (j << 1) % mod) {
        add(l_value, (t[l][n - i - 1] & 1) * j);
        add(r_value, (t[r][n - i - 1] & 1) * j);
      }
      if (r == m + 1) {
        add(r_value, 1);
      }
      printf("%d\n", (r_value - l_value + mod) % mod);
    }
  }
  return 0;
}
