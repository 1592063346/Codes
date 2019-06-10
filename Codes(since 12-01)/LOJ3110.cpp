#include<bits/stdc++.h>

using namespace std;

const int N = 123456, mod = 1e7 + 19;

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

int n, q, t, inv[mod], type[N], h[N], all, update[N], a[N], b[N], c[N], d[N], addtag, multag, now, sum;

struct number_t {
  int foo, bar;

  number_t() {
  }

  number_t(int foo): foo(foo) {
    bar = 0;
  }

  void multiply(int x) {
    if (x == 0) {
      ++bar;
    } else {
      foo = mul(foo, x);
    }
  }

  void divide(int x) {
    if (x == 0) {
      --bar;
    } else {
      foo = mul(foo, inv[x]);
    }
  }

  int get() {
    return bar ? 0 : foo;
  }
} number[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  inv[1] = 1;
  for (int i = 2; i < mod; ++i) {
    inv[i] = mul(mod - mod / i, inv[mod % i]);
  }
  cin >> n >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> type[i];
    if (type[i] != 6) {
      cin >> a[i];
      if (type[i] == 1) {
        cin >> b[i];
      }
    }
    if (type[i] == 1 || type[i] == 5) {
      h[++all] = a[i];
    }
  }
  sort(h + 1, h + 1 + all);
  all = unique(h + 1, h + 1 + all) - h - 1;
  for (int i = 1; i <= q; ++i) {
    if (type[i] == 1 || type[i] == 5) {
      a[i] = lower_bound(h + 1, h + 1 + all, a[i]) - h;
    }
  }
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    cin >> c[i] >> d[i];
  }
  addtag = 0;
  multag = 1;
  pair<int, int> last;
  auto query = [&] (int p) {
    if (update[p] < last.first) {
      number[p] = number_t(last.second);
      update[p] = now;
    }
    number_t pau = number[p];
    pau.multiply(multag);
    return (pau.get() + addtag) % mod;
  };
  int answer = 0;
  for (int i = 1; i <= t; ++i) {
    for (int j = 1; j <= q; ++j) {
      int id = (c[i] + (long long) j * d[i]) % q + 1;
      ++now;
      if (type[id] == 1) {
        int p = a[id], v = b[id];
        v = (v % mod + mod) % mod;
        sub(sum, query(p));
        add(sum, v);
        sub(v, addtag);
        number[p] = number_t(v);
        number[p].divide(multag);
      } else if (type[id] == 6) {
        add(answer, sum);
      } else if (type[id] == 5) {
        add(answer, query(a[id]));
      } else {
        int v = a[id];
        v = (v % mod + mod) % mod;
        if (type[id] == 2) {
          add(addtag, v);
          add(sum, mul(n, v));
        } else if (type[id] == 3) {
          multag = mul(multag, v);
          addtag = mul(addtag, v);
          sum = mul(sum, v);
        } else {
          last = pair<int, int>(now, v);
          addtag = 0;
          multag = 1;
          sum = mul(v, n);
        }
      }
    }
  }
  cout << answer << '\n';
  return 0;
}
