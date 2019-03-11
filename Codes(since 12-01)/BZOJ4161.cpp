#include<bits/stdc++.h>

using namespace std;

const int N = 4e3 + 10, mod = 1e9 + 7;

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

int n, k, a[N], h[N], f[N], v[N], g[N], result[N], inv_f[N];

void pmul(int* x, int* y) {
  memset(result, 0, sizeof result);
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      add(result[i + j], mul(x[i], y[j]));
    }
  }
  for (int i = (k << 1) - 2; i >= k; --i) {
    int p = mul(result[i], inv_f[k]);
    for (int j = 0; j <= k; ++j) {
      sub(result[i - j], mul(f[k - j], p));
    }
  }
  for (int i = 0; i < k; ++i) {
    x[i] = result[i];
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= k; ++i) {
    scanf("%d", &a[i]);
    add(a[i], mod);
  }
  for (int i = 0; i < k; ++i) {
    scanf("%d", &h[i]);
    add(h[i], mod);
  }
  if (n < k) {
    printf("%d\n", h[n]);
  } else {
    n -= k;
    for (int i = k; i < k << 1; ++i) {
      for (int j = i - 1; j >= i - k; --j) {
        add(h[i], mul(h[j], a[i - j]));
      }
    }
    copy(h + k, h + (k << 1), h);
    for (int i = k; i; --i) {
      f[k - i] = k & 1 ? a[i] : (mod - a[i]) % mod;
    }
    f[k] = (k & 1 ? mod - 1 : 1);
    for (int i = 0; i <= k; ++i) {
      inv_f[i] = qpow(f[i], mod - 2);
    }
    g[0] = 1;
    v[1] = 1;
    for (; n; n >>= 1, pmul(v, v)) {
      if (n & 1) {
        pmul(g, v);
      }
    }
    int answer = 0;
    for (int i = 0; i < k; ++i) {
      add(answer, mul(h[i], g[i]));
    }
    printf("%d\n", answer);
  }
  return 0;
}
