#include<bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10, mod = 1e9 + 7, md = 19260817;

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

template<typename T>
int mul(T x) {
  return x;
}

template<typename T, typename... U>
int mul(T x, U... y) {
  return (long long) x * mul(y...) % mod;
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

int a[N][N], h[N * N], last[N * N], ways[N * N], s[N], times[N * N], top, powv[N];

struct hash_table {
  int all;

  struct edge_t {
    edge_t* next;
    int to, id;

    edge_t() {}
    edge_t(edge_t* next, int to, int id): next(next), to(to), id(id) {}
  } *first[md];

  int find(int x) {
    for (edge_t* now = first[x % md]; now; now = now->next) {
      if (now->to == x) {
        return now->id;
      }
    }
    first[x % md] = new edge_t(first[x % md], x, ++all);
    h[all] = x;
    return all;
  }
} table;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> m >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
    }
  }
  powv[0] = 1;
  for (int i = 1; i <= n; ++i) {
    powv[i] = mul(powv[i - 1], m);
  }
  fill(ways + 1, ways + 1 + n * m, 1);
  for (int i = 1; i <= n; ++i) {
    top = 0;
    for (int j = 1; j <= m; ++j) {
      a[i][j] = table.find(a[i][j]);
      if (++times[a[i][j]] == 1) {
        s[++top] = a[i][j];
      }
    }
    for (int j = 1; j <= top; ++j) {
      int x = s[j];
      ways[x] = mul(ways[x], powv[i - last[x] - 1], m - times[x]);
      last[x] = i;
      times[x] = 0;
    }
  }
  int answer = 0;
  for (int i = 1; i <= table.all; ++i) {
    ways[i] = mul(ways[i], powv[n - last[i]]);
    ways[i] = (powv[n] - ways[i] + mod) % mod;
    add(answer, mul(h[i], ways[i]));
  }
  cout << answer << "\n";
  return 0;
}
