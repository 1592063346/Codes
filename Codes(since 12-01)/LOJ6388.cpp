#include<bits/stdc++.h>

using namespace std;

const int N = 1567, mod = 998244353, root = 3;

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

int qpow(int x, int y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

int n, m, k, rev[N * N * 4];
bool appeared[N][N];

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
  for (int i = 0; i < 1 << len; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  x.resize(1 << len);
  y.resize(1 << len);
  dft(x);
  dft(y);
  for (int i = 0; i < 1 << len; ++i) {
    x[i] = mul(x[i], y[i]);
  }
  dft(x, true);
  x.resize(n);
  return x;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  vector<int> a(n * m, 0), b(n * m, 0);
  for (int i = 0, t = 0; i < n; ++i) {
    string x;
    cin >> x;
    for (int j = 0; j < m; ++j) {
      a[t++] = x[j] == '1';
    }
  }
  string opt;
  cin >> opt;
  int x = 0, y = 0, minx = 0, miny = 0;
  for (int i = 0; i < k; ++i) {
    if (opt[i] == 'a') {
      --y;
    } else if (opt[i] == 's') {
      ++x;
    } else if (opt[i] == 'w') {
      --x;
    } else {
      ++y;
    }
    minx = min(minx, x);
    miny = min(miny, y);
  }
  x = -minx;
  y = -miny;
  int maxx = x, maxy = y;
  appeared[x][y] = true;
  for (int i = 0; i < k; ++i) {
    if (opt[i] == 'a') {
      --y;
    } else if (opt[i] == 's') {
      ++x;
    } else if (opt[i] == 'w') {
      --x;
    } else {
      ++y;
    }
    maxx = max(maxx, x);
    maxy = max(maxy, y);
    appeared[x][y] = true;
  }
  for (int i = 0, t = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      b[t++] = appeared[i][j];
    }
  }
  reverse(b.begin(), b.end());
  a = pmul(a, b);
  int answer = 0;
  for (int i = 0, t = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j, ++t) {
      if (i < n - maxx && j < m - maxy && !a[n * m + t - 1]) {
        ++answer;
      }
    }
  }
  cout << answer << '\n';
  return 0;
}
