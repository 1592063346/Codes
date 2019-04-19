#include<bits/stdc++.h>

using namespace std;

const int N = 1e7 + 10, M = 6660, mod = 998244353;

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

int tt, l, r, all, primes[N], maxp[N], maxpid[N];
pair<int, int> info[N];
bitset<500> coef[500];
bool is_prime[N];

void sieve(int n) {
  fill(is_prime + 1, is_prime + 1 + n, true);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes[++all] = i;
      maxp[i] = i;
      maxpid[i] = all;
    }
    for (int j = 1; j <= all; ++j) {
      int p = primes[j];
      if (i * p > n) {
        break;
      }
      is_prime[i * p] = false;
      maxp[i * p] = max(p, maxp[i]);
      if (i % p == 0) {
        break;
      }
    }
  }
}

int main() {
  scanf("%d", &tt);
  sieve(N - 10);
  while (tt--) {
    scanf("%d%d", &l, &r);
    int rank = 0;
    if (r - l + 1 > M) {
      for (int i = 1; i <= all && primes[i] <= r; ++i) {
        if (r / primes[i] != (l - 1) / primes[i]) {
          ++rank;
        }
      }
    } else {
      int total = 0, sq = sqrt(r);
      for (int i = max(l, 2); i <= r; ++i) {
        info[++total] = {maxp[i], i};
      }
      sort(info + 1, info + 1 + total);
      for (int i = 0; i < 500; ++i) {
        coef[i].reset();
      }

      auto get_coef = [&] (int x) {
        bitset<500> coefx;
        if (maxp[x] > sq) {
          x /= maxp[x];
        }
        while (x != 1) {
          int p = maxp[x], t = 0;
          for (; x % p == 0; x /= p) {
            ++t;
          }
          coefx[maxpid[p]] = t & 1;
        }
        return coefx;
      };

      auto insert = [&] (int x, int y = 0) {
        bitset<500> coefx = get_coef(x);
        if (y) {
          coefx ^= get_coef(y);
        }
        for (int i = 499; ~i; --i) {
          if (coefx[i]) {
            if (coef[i][i]) {
              coefx ^= coef[i];
            } else {
              coef[i] = coefx;
              return true;
            }
          }
        }
        return false;
      };

      for (int i = 1, j; i <= total; ++i) {
        if (info[i].first <= sq) {
          rank += insert(info[i].second);
        } else if (info[i].first != info[i - 1].first) {
          j = info[i].second;
          ++rank;
        } else {
          rank += insert(info[i].second, j);
        }
      }
    }
    printf("%d\n", qpow(2, r - l + 1 - rank));
  }
  return 0;
}
