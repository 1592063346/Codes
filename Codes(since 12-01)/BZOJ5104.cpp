#include<bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 9;

int add(int x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
  return x;
}

int sub(int x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
  return x;
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

int n, value;

struct number_t {
  int foo, bar;

  number_t() {
  }

  number_t(int foo, int bar): foo(foo), bar(bar) {
  }

  number_t operator * (number_t a) {
    return number_t((mul(foo, a.foo) + mul(value, mul(bar, a.bar))) % mod, (mul(foo, a.bar) + mul(bar, a.foo)) % mod);
  }

  number_t power(int y) {
    number_t result(1, 0), x = *this;
    for (; y; y >>= 1, x = x * x) {
      if (y & 1) {
        result = result * x;
      }
    }
    return result;
  }
};

bool exist(int x) {
  return qpow(x, mod - 1 >> 1) == 1;
}

int find(int x) {
  if (!exist(x)) {
    return -1;
  }
  int y = rand();
  while (exist(sub(mul(y, y), x))) {
    y = rand();
  }
  value = sub(mul(y, y), x);
  return number_t(y, 1).power(mod + 1 >> 1).foo;
}

int bsgs(int a, int y, int type) {
  int m = (long long) ceil(sqrt(mod)), inv = qpow(qpow(a, m), mod - 2);
  map<int, int> odd, even;
  even[1] = 0;
  for (int i = 1, j = a; i < m; ++i, j = mul(j, a)) {
    if (i & 1) {
      if (!odd.count(j)) {
        odd[j] = i;
      }
    } else {
      if (!even.count(j)) {
        even[j] = i;
      }
    }
  }
  for (int i = 0; i < m; ++i, y = mul(y, inv)) {
    if ((i * m & 1) != type) {
      if (odd.count(y)) {
        return i * m + odd[y];
      }
    } else {
      if (even.count(y)) {
        return i * m + even[y];
      }
    }
  }
  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  int sqrt5 = find(5);
  n = mul(n, sqrt5);
  int answer = mod, inv2 = mod + 1 >> 1, foo = find(sub(mul(n, n), 4)), bar, x;
  if (~foo) {
    bar = mul(add(n, foo), inv2);
    if (~(x = bsgs(mul(add(1, sqrt5), inv2), bar, 1))) {
      answer = min(answer, x);
    }
    bar = mul(sub(n, foo), inv2);
    if (~(x = bsgs(mul(add(1, sqrt5), inv2), bar, 1))) {
      answer = min(answer, x);
    }
  }
  foo = find(add(mul(n, n), 4));
  if (~foo) {
    bar = mul(add(n, foo), inv2);
    if (~(x = bsgs(mul(add(1, sqrt5), inv2), bar, 0))) {
      answer = min(answer, x);
    }
    bar = mul(sub(n, foo), inv2);
    if (~(x = bsgs(mul(add(1, sqrt5), inv2), bar, 0))) {
      answer = min(answer, x);
    }
  }
  if (answer == mod) {
    answer = -1;
  }
  cout << answer << '\n';
  return 0;
}
