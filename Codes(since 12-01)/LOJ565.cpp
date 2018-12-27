#include<bits/stdc++.h>

using namespace std;

const int N = 524288, mod = 998244353, G = 3;

void add(int& x, int y) {
  x += y;
  if (x > mod) {
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

int n, m, a[N], b[N], c[N], rev[N], len, poly_a[N], poly_b[N];
vector<int> event[N], arr[N], f[N];

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
  for (len = 0; (1 << len) <= len_a + len_b; ++len);
  int m = 1 << len;
  for (int i = 0; i < m; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  for (int i = 0; i < m; ++i) {
    poly_a[i] = poly_b[i] = 0;
    if (i <= len_a) {
      poly_a[i] = a[i];
    }
    if (i <= len_b) {
      poly_b[i] = b[i];
    }
  }
  ntt(poly_a, m, 1);
  ntt(poly_b, m, 1);
  for (int i = 0; i < m; ++i) {
    poly_a[i] = mul(poly_a[i], poly_b[i]);
  }
  ntt(poly_a, m, -1);
  for (int i = 0; i < m; ++i) {
    c[i] = poly_a[i];
  }
}

struct poly {
  vector<int> poly_s;

  poly () {
    poly_s.clear();
  }

  bool operator < (const poly& a) const {
    return poly_s.size() > a.poly_s.size();
  }
};

int main() {
  scanf("%d%d", &n, &m);
  n += 19;
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    int a, x, y;
    scanf("%d%d%d", &a, &x, &y);
    int p = mul(x, qpow(y, mod - 2));
    event[a].push_back(p);
    add(ans, p);
  }
  ans = (ans << 1) % mod;

  auto get_array = [&] (vector<int>& all) {
    priority_queue<poly> s;
    for (auto v : all) {
      poly new_poly;
      new_poly.poly_s.push_back((1 - v + mod) % mod);
      new_poly.poly_s.push_back(v);
      s.push(new_poly);
    }
    while (s.size() > 1) {
      poly l = s.top();
      s.pop();
      poly r = s.top();
      s.pop();
      int len_a = l.poly_s.size() - 1, len_b = r.poly_s.size() - 1;
      for (int i = 0; i <= len_a; ++i) {
        a[i] = l.poly_s[i];
      }
      for (int i = 0; i <= len_b; ++i) {
        b[i] = r.poly_s[i];
      }
      mul(len_a, len_b, a, b, c);
      poly new_poly;
      for (int i = 0; i <= len_a + len_b; ++i) {
        new_poly.poly_s.push_back(c[i]);
      }
      s.push(new_poly);
    }
    return s.top().poly_s;
  };

  for (int i = 0; i <= n; ++i) {
    if (event[i].size()) {
      arr[i] = get_array(event[i]);
    } else {
      arr[i].push_back(1);
    }
  }
  f[0] = arr[0];
  int total_len = event[0].size();
  for (int i = 1; i <= n; ++i) {
    int old = total_len >> 1;
    fill(a, a + old + 1, 0);
    for (int j = 0; j <= total_len; ++j) {
      add(a[j >> 1], f[i - 1][j]);
    }
    for (int j = 0; j <= event[i].size(); ++j) {
      b[j] = arr[i][j];
    }
    mul(old, event[i].size(), a, b, c);
    total_len = old + event[i].size();
    for (int j = 0; j <= total_len; ++j) {
      f[i].push_back(c[j]);
    }
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 1; j < f[i].size(); j += 2) {
      sub(ans, f[i][j]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
