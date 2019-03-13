#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10, mod = 998244353;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

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

int tt, n, q, a, f[N][N], l[N], r[N], w[N], h[N], all, minv[N], left_p[N];
map<int, bool> values;

int dp(int x) {
  vector<int> pos;
  for (int i = 1; i <= all; ++i) {
    if (minv[i] == x) {
      pos.push_back(i);
    }
  }
  if (!pos.size()) {
    return -1;
  }
  memset(left_p, 0, sizeof left_p);
  for (int i = 1; i <= q; ++i) {
    if (w[i] == x) {
      int ql = lower_bound(pos.begin(), pos.end(), l[i]) - pos.begin() + 1;
      int qr = lower_bound(pos.begin(), pos.end(), r[i]) - pos.begin();
      cmax(left_p[qr], ql);
    }
  }
  memset(f, 0, sizeof f);
  f[0][0] = 1;
  for (int i = 1; i <= pos.size(); ++i) {
    int p0 = qpow(x - 1, h[pos[i - 1] + 1] - h[pos[i - 1]]);
    int p1 = (qpow(x, h[pos[i - 1] + 1] - h[pos[i - 1]]) - p0 + mod) % mod;
    for (int j = 0; j < i; ++j) {
      add(f[i][i], mul(f[i - 1][j], p1));
      if (j >= left_p[i]) {
        add(f[i][j], mul(f[i - 1][j], p0));
      }
    }
  }
  int result = 0;
  for (int i = 1; i <= pos.size(); ++i) {
    add(result, f[pos.size()][i]);
  }
  return result;
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d%d", &n, &q, &a);
    all = 0;
    values.clear();
    for (int i = 1; i <= q; ++i) {
      scanf("%d%d%d", &l[i], &r[i], &w[i]);
      ++r[i];
      h[++all] = l[i];
      h[++all] = r[i];
      values[w[i]] = true;
    }
    h[++all] = 1;
    h[++all] = n + 1;
    sort(h + 1, h + 1 + all);
    all = unique(h + 1, h + 1 + all) - h - 1;
    fill(minv + 1, minv + 1 + all, a + 1);
    for (int i = 1; i <= q; ++i) {
      l[i] = lower_bound(h + 1, h + 1 + all, l[i]) - h;
      r[i] = lower_bound(h + 1, h + 1 + all, r[i]) - h;
      for (int j = l[i]; j < r[i]; ++j) {
        cmin(minv[j], w[i]);
      }
    }
    int answer = 1;
    for (auto v : values) {
      int x = dp(v.first);
      if (!~x) {
        puts("0");
        goto next_case;
      } else {
        answer = mul(answer, x);
      }
    }
    for (int i = 1; i < all; ++i) {
      if (minv[i] == a + 1) {
        answer = mul(answer, qpow(a, h[i + 1] - h[i]));
      }
    }
    printf("%d\n", answer);
    next_case: continue;
  }
  return 0;
}
