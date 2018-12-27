#include<bits/stdc++.h>

using namespace std;

#define rg register

typedef long long ll;
typedef unsigned long long ull;

const int N = 255;

int n, m, c[26];
bool tag[N][N][N];
char s[N][N];
ull hash_val[N][N][N], bas[N], pre[N], suf[N], hash_bas[N];

inline ull random_num() {
  return (1ull * rand() << 45) | (1ull * rand() << 30) | (1ull * rand() << 15) | rand();
}

void hash_init() {
  bas[0] = hash_bas[0] = 1;
  for (rg int i = 1; i < 26; ++i) {
    bas[i] = bas[i - 1] * 100ull;
  }
  for (rg int i = 1; i <= n; ++i) {
    hash_bas[i] = hash_bas[i - 1] * 19260817ull;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  hash_init();
  for (rg int i = 1; i <= n; ++i) {
    scanf("%s", s[i] + 1);
  }
  for (rg int i = 1; i <= n; ++i) {
    for (rg int j = 1; j <= m; ++j) {
      ull res = 0;
      int t = 0;
      memset(c, 0, sizeof c);
      for (rg int k = j; k <= m; ++k) {
        if (++c[s[i][k] - 'a'] & 1) {
          ++t;
        } else {
          --t;
        }
        res += bas[s[i][k] - 'a'];
        if (t >= 2) {
          tag[i][j][k] = true;
        }
        hash_val[i][j][k] = t <= 1 ? res : random_num();
      }
    }
  }
  ll ans = 0;
  for (int i = 1; i <= m; ++i) {
    for (rg int j = i; j <= m; ++j) {
      memset(c, 0, sizeof c);
      for (rg int k = 1; k <= n; ++k) {
        pre[k] = pre[k - 1] * 19260817ull + hash_val[k][i][j];
      }
      for (rg int k = n; k; --k) {
        suf[k] = suf[k + 1] * 19260817ull + hash_val[k][i][j];
      }
      for (rg int k = 1; k <= n; ++k) {
        if (tag[k][i][j]) {
          continue;
        }
        int l = 1, r = min(k, n - k + 1);
        while (l ^ r) {
          int mid = (l + r >> 1) + 1;
          if (pre[k] - pre[k - mid] * hash_bas[mid] == suf[k] - suf[k + mid] * hash_bas[mid]) {
            l = mid;
          } else {
            r = mid - 1;
          }
        }
        ans += l;
      }
      for (rg int k = 1; k < n; ++k) {
        int l = 0, r = min(k, n - k);
        while (l ^ r) {
          int mid = (l + r >> 1) + 1;
          if (pre[k] - pre[k - mid] * hash_bas[mid] == suf[k + 1] - suf[k + 1 + mid] * hash_bas[mid]) {
            l = mid;
          } else {
            r = mid - 1;
          }
        }
        ans += l;
      }
    }
  }
  printf("%I64d\n", ans);
  return 0;
}
