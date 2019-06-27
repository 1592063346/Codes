#include<bits/stdc++.h>

using namespace std;

const int N = 123456, mod = 998244353;

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

int inv(int x) {
  int y = mod, a = 0, b = 1;
  while (x) {
    int t = y / x;
    y -= t * x;
    swap(x, y);
    a -= t * b;
    swap(a, b);
  }
  if (a < 0) {
    a += mod;
  }
  return a;
}

int n, m, q, dfn_t, all, top, dfn[N], low[N], sta[N];
vector<int> adj[N];
map<int, int> cnt;

void dfs(int x, int f) {
  dfn[x] = low[x] = ++dfn_t;
  sta[++top] = x;
  bool to_f = false;
  for (auto y : adj[x]) {
    if (y != f || to_f) {
      if (!dfn[y]) {
        dfs(y, x);
        low[x] = min(low[x], low[y]);
        if (low[y] == dfn[x]) {
          int size = 0;
          while (1) {
            ++size;
            if (sta[top--] == y) {
              break;
            }
          }
          ++cnt[size];
          ++all;
        } else if (low[y] > dfn[x]) {
          ++cnt[1];
          ++all;
          --top;
        }
      } else {
        low[x] = min(low[x], dfn[y]);
      }
    } else {
      to_f = true;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(1, 0);
  while (q--) {
    int c;
    cin >> c;
    int answer = mul(c, qpow(mul(c - 1, inv(c)), all));
    for (auto p : cnt) {
      int result = qpow(c - 1, p.first);
      if (p.first & 1) {
        add(result, 1);
      } else {
        sub(result, 1);
      }
      answer = mul(answer, qpow(result, p.second));
    }
    cout << answer << '\n';
  }
  return 0;
}
