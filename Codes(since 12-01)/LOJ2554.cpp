#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, mod = 998244353, G = 3;

int T, n, l[N], size[N], f[N], poly_a[N], poly_b[N], rev[N], a[N], b[N], c[N];

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
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

void ntt(int* c, int n, int type) {
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

void mul(int len_a, int len_b, int* a, int* b, int* c) {
  int len = 0;
  for (; (1 << len) <= len_a + len_b; ++len);
  int n = 1 << len;
  for (int i = 0; i < n; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  for (int i = 0; i < n; ++i) {
    poly_a[i] = poly_b[i] = 0;
    if (i <= len_a) {
      poly_a[i] = a[i];
    }
    if (i <= len_b) {
      poly_b[i] = b[i];
    }
  }
  ntt(poly_a, n, 1);
  ntt(poly_b, n, 1);
  for (int i = 0; i < n; ++i) {
    poly_a[i] = mul(poly_a[i], poly_b[i]);
  }
  ntt(poly_a, n, -1);
  for (int i = 0; i <= len_a + len_b; ++i) {
    c[i] = poly_a[i];
  }
}

void solve(int l, int r) {
  if (l == r) {
    add(f[l], mul(l - 1, f[l - 1]));
  } else {
    int mid = l + r >> 1;
    solve(l, mid);
    for (int i = l; i <= mid; ++i) {
      a[i - l] = mul(i - 1, f[i]);
      b[i - l] = f[i];
    }
    mul(mid - l, mid - l, a, b, c);
    for (int i = max(l << 1, mid + 1); i <= r; ++i) {
      add(f[i], c[i - (l << 1)]);
    }
    if (l > 2) {
      for (int i = l; i <= mid; ++i) {
        a[i - l] = f[i];
      }
      for (int i = 2; i <= min(l - 1, r - l); ++i) {
        b[i - 2] = f[i];
      }
      mul(mid - l, min(l - 1, r - l) - 2, a, b, c);
      for (int i = max(l + 2, mid + 1); i <= r; ++i) {
        add(f[i], mul(i - 2, c[i - l - 2]));
      }
    }
    solve(mid + 1, r);
  }
}

int main() {
  scanf("%d%d", &T, &n);
  f[0] = 1;
  f[1] = 2;
  if (n > 1) {
    solve(2, n);
  }
  for (int kase = 1; kase <= T; ++kase) {
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &l[i]);
      l[i] = i - l[i] + 1;
    }
    bool no_solution = l[n] != 1;
    vector<int> stack_t;
    memset(size, 0, sizeof size);
    for (int i = n; i; --i) {
      if (stack_t.size()) {
        ++size[stack_t.back()];
        if (l[i] < l[stack_t.back()]) {
          no_solution = true;
        }
      }
      stack_t.push_back(i);
      for (; stack_t.size() && l[stack_t.back()] == i; stack_t.pop_back());
    }
    if (no_solution) {
      puts("0");
    } else {
      int answer = 1;
      for (int i = 1; i <= n; ++i) {
        answer = mul(answer, f[size[i]]);
      }
      printf("%d\n", answer);
    }
  }
  return 0;
}
