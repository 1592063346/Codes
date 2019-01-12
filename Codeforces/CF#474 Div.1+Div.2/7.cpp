#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 18, mod = 998244353, G = 3;

int n, a, b, fac[N], invfac[N], poly_a[N], poly_b[N], rev[N];

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

int binom(int n, int m) {
  return mul(fac[n], mul(invfac[m], invfac[n - m]));
}

void init_binom(int n) {
  fac[0] = invfac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  invfac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    invfac[i] = mul(invfac[i + 1], i + 1);
  }
}

void ntt(int n, int* c, int type) {
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(c[i], c[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    int x = qpow(G, type == 1 ? (mod - 1) / (i << 1) : mod - 1 - (mod - 1) / (i << 1));
    for (int j = 0; j < n; j += i << 1) {
      int y = 1;
      for (int k = 0; k < i; ++k, y = mul(y, x)) {
        int p = c[j + k], q = mul(y, c[i + j + k]);
        c[j + k] = (p + q) % mod;
        c[i + j + k] = (p - q + mod) % mod;
      }
    }
  }
  if (type == -1) {
    int inv = qpow(n, mod - 2);
    for (int i = 0; i < n; ++i) {
      c[i] = mul(c[i], inv);
    }
  }
}

vector<int> mul(vector<int>& a, vector<int>& b) {
  int la = a.size() - 1, lb = b.size() - 1, len = 0;
  for (; (1 << len) <= la + lb; ++len);
  int n = 1 << len;
  for (int i = 0; i < n; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  fill(poly_a, poly_a + n, 0);
  fill(poly_b, poly_b + n, 0);
  for (int i = 0; i <= la; ++i) {
    poly_a[i] = a[i];
  }
  for (int i = 0; i <= lb; ++i) {
    poly_b[i] = b[i];
  }
  ntt(n, poly_a, 1);
  ntt(n, poly_b, 1);
  for (int i = 0; i < n; ++i) {
    poly_a[i] = mul(poly_a[i], poly_b[i]);
  }
  ntt(n, poly_a, -1);
  vector<int> result;
  for (int i = 0; i <= la + lb; ++i) {
    result.push_back(poly_a[i]);
  }
  return result;
}

struct poly_t {
  vector<int> poly;

  poly_t() {}
  poly_t(vector<int>& init) {
    poly = init;
  }

  bool operator < (const poly_t& a) const {
    return poly.size() > a.poly.size();
  }
};

int main() {
  scanf("%d%d%d", &n, &a, &b);
  --n;
  if (a + b - 2 > n || !a || !b) {
    return puts("0"), 0;
  }
  if (!n) {
    return printf("%d\n", a == 1 && b == 1), 0;
  }
  init_binom(n);
  priority_queue<poly_t> que;
  for (int i = 0; i < n; ++i) {
    vector<int> init = {i, 1};
    que.push(poly_t(init));
  }
  while (que.size() > 1) {
    poly_t x = que.top();
    que.pop();
    poly_t y = que.top();
    que.pop();
    vector<int> new_poly = mul(x.poly, y.poly);
    que.push(poly_t(new_poly));
  }
  vector<int> answer = que.top().poly;
  printf("%d\n", mul(binom(a + b - 2, a - 1), answer[a + b - 2]));
  return 0;
}
