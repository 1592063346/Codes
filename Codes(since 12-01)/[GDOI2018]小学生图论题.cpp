#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10, mod = 998244353, root = 3;

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

int n, m, rev[N];
vector<int> k;

void dft(vector<int>& buffer, bool inv = false) {
  int n = buffer.size();
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(buffer[i], buffer[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    int x = qpow(root, inv ? mod - 1 - (mod - 1) / (i << 1) : (mod - 1) / (i << 1));
    for (int j = 0; j < n; j += i << 1) {
      int y = 1;
      for (int k = 0; k < i; ++k, y = mul(y, x)) {
        int p = buffer[j + k], q = mul(y, buffer[i + j + k]);
        buffer[j + k] = (p + q) % mod;
        buffer[i + j + k] = (p - q + mod) % mod;
      }
    }
  }
  if (inv) {
    int x = qpow(n, mod - 2);
    for (int i = 0; i < n; ++i) {
      buffer[i] = mul(buffer[i], x);
    }
  }
}

vector<int> pmul(vector<int> x, vector<int> y) {
  int n = x.size() + y.size() - 1, len = 0;
  for (; (1 << len) < n; ++len);
  int size = 1 << len;
  for (int i = 0; i < size; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  x.resize(size);
  y.resize(size);
  dft(x);
  dft(y);
  for (int i = 0; i < size; ++i) {
    x[i] = mul(x[i], y[i]);
  }
  dft(x, true);
  return vector<int>(x.begin(), x.begin() + n);
}

vector<int> solve(int l, int r) {
  if (l == r) {
    vector<int> x(k[l] + 1, 1);
    for (int i = 1; i < k[l]; ++i) {
      x[i] = 2;
    }
    return x;
  } else {
    int mid = l + r >> 1;
    return pmul(solve(l, mid), solve(mid + 1, r));
  }
}

int main() {
  scanf("%d%d", &n, &m);
  int all = 0;
  k.resize(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &k[i]);
    all += k[i];
    for (int j = 0; j < k[i]; ++j) {
      scanf("%*d");
    }
  }
  for (int i = 0; i < n - all; ++i) {
    k.push_back(1);
  }
  vector<int> x = solve(0, k.size() - 1);
  int inv2 = mod + 1 >> 1, answer = 1;
  for (int i = 1; i < n; ++i) {
    add(answer, mul(qpow(inv2, (long long) i * (n - i) % (mod - 1)), x[i]));
  }
  printf("%d\n", answer);
  return 0;
}
