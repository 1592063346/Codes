#include<bits/stdc++.h>

using namespace std;

const int N = 65;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

long long n, m, k;
int tt, mod, up, bit_n[N], bit_m[N], bit_k[N];
bool visit[N][2][2][2];
pair<int, int> f[N][2][2][2];

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

pair<int, int> dp(int p, bool lim_n, bool lim_m, bool lim_k) {
  if (!~p) {
    return {0, 1};
  }
  if (visit[p][lim_n][lim_m][lim_k]) {
    return f[p][lim_n][lim_m][lim_k];
  }
  visit[p][lim_n][lim_m][lim_k] = true;
  f[p][lim_n][lim_m][lim_k] = {0, 0};
  for (int i = 0; i <= (lim_n ? bit_n[p] : 1); ++i) {
    for (int j = 0; j <= (lim_m ? bit_m[p] : 1); ++j) {
      int c = i ^ j;
      if (!lim_k || c >= bit_k[p]) {
        pair<int, int> go = dp(p - 1, lim_n & (i == bit_n[p]), lim_m & (j == bit_m[p]), lim_k & (c == bit_k[p]));
        add(f[p][lim_n][lim_m][lim_k].first, (go.first + mul(go.second, ((long long) c << p) % mod)) % mod);
        add(f[p][lim_n][lim_m][lim_k].second, go.second);
      }
    }
  }
  return f[p][lim_n][lim_m][lim_k];
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%lld%lld%lld%d", &n, &m, &k, &mod);
    long long sub = k;
    --n;
    --m;
    memset(bit_n, 0, sizeof bit_n);
    memset(bit_m, 0, sizeof bit_m);
    memset(bit_k, 0, sizeof bit_k);
    memset(visit, false, sizeof visit);
    up = 0;
    for (int t = 0; n; ++t, n >>= 1) {
      bit_n[t] = n & 1;
      cmax(up, t);
    }
    for (int t = 0; m; ++t, m >>= 1) {
      bit_m[t] = m & 1;
      cmax(up, t);
    }
    for (int t = 0; k; ++t, k >>= 1) {
      bit_k[t] = k & 1;
      cmax(up, t);
    }
    pair<int, int> answer = dp(up, true, true, true);
    printf("%d\n", (answer.first - (answer.second * (sub % mod) % mod) + mod) % mod);
  }
  return 0;
}
