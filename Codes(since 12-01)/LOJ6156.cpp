#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
const double pi = acos(-1);

int tt, n, mod, a[N], rev[N];
long long answer[N];

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

struct complex_t {
  double x, y;

  complex_t() {}
  complex_t(double x, double y): x(x), y(y) {}

  complex_t operator + (complex_t a) {
    return complex_t(x + a.x, y + a.y);
  }

  complex_t operator - (complex_t a) {
    return complex_t(x - a.x, y - a.y);
  }

  complex_t operator * (complex_t a) {
    return complex_t(x * a.x - y * a.y, x * a.y + y * a.x);
  }
};

void dft(vector<complex_t>& buffer, bool inv = false) {
  int n = buffer.size();
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(buffer[i], buffer[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    complex_t x(cos(pi / i), (inv ? -1 : 1) * sin(pi / i));
    for (int j = 0; j < n; j += i << 1) {
      complex_t y(1, 0);
      for (int k = 0; k < i; ++k, y = y * x) {
        complex_t p = buffer[j + k], q = y * buffer[i + j + k];
        buffer[j + k] = p + q;
        buffer[i + j + k] = p - q;
      }
    }
  }
  if (inv) {
    for (int i = 0; i < n; ++i) {
      buffer[i].x /= n;
    }
  }
}

vector<long long> pmul(vector<long long> x, vector<long long> y) {
  int n = x.size() + y.size() - 1, len = 0;
  for (; (1 << len) <= n; ++len);
  for (int i = 0; i < (1 << len); ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << len - 1);
  }
  vector<complex_t> pa, pb;
  for (auto v : x) {
    pa.emplace_back(v, 0);
  }
  for (auto v : y) {
    pb.emplace_back(v, 0);
  }
  pa.resize(1 << len, complex_t(0, 0));
  pb.resize(1 << len, complex_t(0, 0));
  dft(pa);
  dft(pb);
  for (int i = 0; i < (1 << len); ++i) {
    pa[i] = pa[i] * pb[i];
  }
  dft(pa, true);
  vector<long long> answer;
  for (auto v : pa) {
    answer.push_back((long long) (v.x + 0.1));
  }
  answer.resize(n);
  return answer;
}

int find_g(int x) {
  vector<int> factor;
  for (int i = 2; i * i <= x - 2; ++i) {
    if ((x - 1) % i == 0) {
      factor.push_back(i);
      if (i != (x - 1) / i) {
        factor.push_back((x - 1) / i);
      }
    }
  }
  for (int i = 2;; ++i) {
    bool ok = true;
    for (auto p : factor) {
      if (qpow(i, p) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) {
      return i;
    }
  }
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d%d", &n, &mod);
    memset(a, 0, sizeof a);
    long long answer0 = 0, number0 = 0;
    for (int i = 1; i <= n; ++i) {
      int x;
      scanf("%d", &x);
      x %= mod;
      ++a[x];
      if (!x) {
        answer0 += n - (++number0);
      }
    }
    int G = find_g(mod);
    vector<long long> b;
    for (int i = 0, x = 1; i < mod - 1; ++i, x = mul(x, G)) {
      b.push_back(a[x]);
    }
    vector<long long> result = pmul(b, b);
    memset(answer, 0, sizeof answer);
    answer[0] = answer0;
    for (int i = 0, j = 1; i < result.size(); ++i, j = mul(j, G)) {
      answer[j] += result[i] - (i & 1 ? 0 : b[i >> 1]) >> 1;
    }
    for (int i = 0; i < mod; ++i) {
      printf("%lld\n", answer[i]);
    }
  }
  return 0;
}
