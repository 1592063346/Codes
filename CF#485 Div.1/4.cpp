#include<bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10, f[5] = {1, 10, 100, 1000, 10000};
const long double pi = acos(-1);

struct complex_t {
  long double x, y;

  complex_t () {}
  complex_t (long double x, long double y): x(x), y(y) {}

  complex_t operator + (complex_t a) {
    return complex_t (x + a.x, y + a.y);
  }

  complex_t operator - (complex_t a) {
    return complex_t (x - a.x, y - a.y);
  }

  complex_t operator * (complex_t a) {
    return complex_t (x * a.x - y * a.y, x * a.y + y * a.x);
  }
} com_a[N], com_b[N];

int l, rev[N];

void fft(complex_t* c, int n, int type) {
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) {
      swap(c[i], c[rev[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    complex_t x(cos(pi / i), type * sin(pi / i));
    for (int j = 0; j < n; j += i << 1) {
      complex_t y(1, 0);
      for (int k = 0; k < i; ++k, y = y * x) {
        complex_t p = c[j + k], q = y * c[i + j + k];
        c[j + k] = p + q;
        c[i + j + k] = p - q;
      }
    }
  }
}

char s[N];

struct big_integer {
  vector<int> num;

  big_integer () {}
  big_integer (int value) {
    num.push_back(value);
  }

  void read() {
    scanf("%s", s);
    int len = strlen(s);
    num.resize(len);
    for (int i = 0; i < len; ++i) {
      num[i] = s[len - i - 1] - '0';
    }
  }

  big_integer operator * (big_integer a) {
    int len1 = num.size();
    int len2 = a.num.size();
    for (l = 0; (1 << l) <= (len1 + len2) / 4 + 1; ++l);
    int n = 1 << l;
    for (int i = 0; i < n; ++i) {
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << l - 1);
    }
    for (int i = 0; i < n; ++i) {
      com_a[i] = com_b[i] = complex_t(0, 0);
    }
    for (int i = 0; i < len1; ++i) {
      com_a[i / 4].x += num[i] * f[i % 4];
    }
    for (int i = 0; i < len2; ++i) {
      com_b[i / 4].x += a.num[i] * f[i % 4];
    }
    fft(com_a, n, 1);
    fft(com_b, n, 1);
    for (int i = 0; i < n; ++i) {
      com_a[i] = com_a[i] * com_b[i];
    }
    fft(com_a, n, -1);
    big_integer result;
    for (int i = 0, rest = 0; i <= (len1 + len2) / 4 + 1; ++i) {
      long long now = rest + (com_a[i].x / n + 0.5);
      rest = now / f[4];
      now %= f[4];
      for (int j = 0; j < 4; ++j) {
        result.num.push_back(now % 10);
        now /= 10;
      }
    }
    for (; result.num.size() > 1 && !result.num.back(); result.num.pop_back());
    return result;
  }

  bool operator >= (big_integer a) {
    if (num.size() != a.num.size()) {
      return num.size() > a.num.size();
    }
    for (int i = num.size() - 1; ~i; --i) {
      if (num[i] != a.num[i]) {
        return num[i] > a.num[i];
      }
    }
    return true;
  }
} n;

big_integer qpow3(int x) {
  big_integer result(1), v(3);
  for (; x; x >>= 1, v = v * v) {
    if (x & 1) {
      result = result * v;
    }
  }
  return result;
}

int main() {
  n.read();
  if (n.num.size() == 1 && n.num[0] == 1) {
    return puts("1"), 0;
  }
  int y = n.num.size() - 1;
  int x = (y + log10(n.num[y])) / log10(3);
  x = max(0, x - 1);
  big_integer p = qpow3(x);
  while (1) {
    if (p * big_integer(3) >= n) {
      if (p * big_integer(2) >= n) {
        return printf("%d\n", x * 3 + 2), 0;
      } else {
        return printf("%d\n", x * 3 + 3), 0;
      }
    } else {
      if (p * big_integer(4) >= n) {
        return printf("%d\n", x * 3 + 4), 0;
      }
    }
    ++x;
    p = p * big_integer(3);
  }
  return 0;
}
