#include<bits/stdc++.h>

using namespace std;

const int N = 770, mod = 1e9 + 7;

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

int n, l, r, q, m, all, f[N][1 << 16], g[N][1 << 16], h[N];
vector<int> numbers;
vector<pair<int, int>> states;
map<int, int> id;

vector<pair<int, int>> factorize(int x) {
  vector<pair<int, int>> result;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      int number = 0;
      for (; x % i == 0; ++number, x /= i);
      result.emplace_back(i, number);
    }
  }
  if (x != 1) {
    result.emplace_back(x, 1);
  }
  return result;
}

void dfs(int t, int x, int s) {
  if (t == states.size()) {
    numbers.push_back(s);
    id[x] = numbers.size();
  } else {
    for (int i = 0, j = 1; i <= states[t].second && (long long) x * j <= n; ++i, j *= states[t].first) {
      dfs(t + 1, x * j, s | ((i == 0) << (t << 1)) | ((i == states[t].second) << (t << 1 | 1)));
    }
  }
}

void print_no_solution() {
  for (int i = 1; i <= q; ++i) {
    puts("0");
  }
}

void fmt(int* f, bool inv = false) {
  for (int i = 1; i < all; i <<= 1) {
    for (int j = 0; j < all; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        if (!inv) {
          add(f[i + j + k], f[j + k]);
        } else {
          sub(f[i + j + k], f[j + k]);
        }
      }
    }
  }
}

void or_merge(int* f, int* g) {
  fmt(f);
  fmt(g);
  for (int i = 0; i < all; ++i) {
    f[i] = mul(f[i], g[i]);
  }
  fmt(f, true);
}

int main() {
  scanf("%d%d%d%d", &n, &l, &r, &q);
  if (r % l) {
    print_no_solution();
    return 0;
  }
  n /= l;
  r /= l;
  states = factorize(r);
  dfs(0, 1, 0);
  m = numbers.size();
  all = 1 << (states.size() << 1);
  f[0][0] = 1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < all; ++j) {
      if (f[i][j]) {
        add(f[i + 1][j | numbers[i]], f[i][j]);
        add(f[i + 1][j], f[i][j]);
      }
    }
  }
  g[m + 1][0] = 1;
  for (int i = m + 1; i > 1; --i) {
    for (int j = 0; j < all; ++j) {
      if (g[i][j]) {
        add(g[i - 1][j | numbers[i - 2]], g[i][j]);
        add(g[i - 1][j], g[i][j]);
      }
    }
  }
  int answer = f[m][all - 1];
  for (int i = 1; i <= m; ++i) {
    or_merge(f[i - 1], g[i + 1]);
    h[i] = f[i - 1][all - 1];
  }
  while (q--) {
    int x;
    scanf("%d", &x);
    if (x % l) {
      puts("0");
    } else {
      x /= l;
      printf("%d\n", id[x] ? (answer - h[id[x]] + mod) % mod : 0);
    }
  }
  return 0;
}
