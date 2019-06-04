#include<bits/stdc++.h>

using namespace std;

const int N = 234567, alpha = 26, base = 5001, mod = 998244353;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

struct matrix_t {
  int x, y, a[alpha + 1][alpha + 1];

  matrix_t() {
    memset(a, 0, sizeof a);
  }

  int* operator [] (int p) {
    return a[p];
  }

  matrix_t operator * (matrix_t b) {
    matrix_t result;
    result.x = x;
    result.y = b.y;
    for (int i = 0; i < x; ++i) {
      for (int j = 0; j < b.y; ++j) {
        for (int k = 0; k < y; ++k) {
          add(result[i][j], mul(a[i][k], b[k][j]));
        }
      }
    }
    return result;
  }
};

int n, q, tt, last, ch[N][alpha], father[N], len[N], coef[N][alpha + 1];
bool visit[N];
matrix_t power0[base], power1[base];
string s;

int new_node(int x) {
  len[++tt] = len[x] + 1;
  return tt;
}

void extend(int c) {
  int p = last, np = new_node(p);
  while (p && !ch[p][c]) {
    ch[p][c] = np;
    p = father[p];
  }
  if (!p) {
    father[np] = 1;
  } else {
    int q = ch[p][c];
    if (len[p] + 1 == len[q]) {
      father[np] = q;
    } else {
      int nq = new_node(p);
      memcpy(ch[nq], ch[q], sizeof ch[q]);
      father[nq] = father[q];
      father[np] = father[q] = nq;
      while (p && ch[p][c] == q) {
        ch[p][c] = nq;
        p = father[p];
      }
    }
  }
  last = np;
}

void dfs(int x) {
  if (visit[x]) {
    return;
  }
  visit[x] = true;
  coef[x][alpha] = 1;
  for (int i = 0; i < alpha; ++i) {
    if (ch[x][i]) {
      dfs(ch[x][i]);
      for (int j = 0; j <= alpha; ++j) {
        add(coef[x][j], coef[ch[x][i]][j]);
      }
    } else {
      add(coef[x][i], 1);
    }
  }
}

void matrix_init() {
  power0[0].x = power0[0].y = power1[0].x = power1[0].y = alpha + 1;
  for (int i = 0; i <= alpha; ++i) {
    power0[0][i][i] = power1[0][i][i] = 1;
  }
  matrix_t& tran = power0[1];
  tran.x = tran.y = alpha + 1;
  for (int i = 0; i < alpha; ++i) {
    if (ch[1][i]) {
      dfs(ch[1][i]);
      for (int j = 0; j < alpha; ++j) {
        add(tran[j][i], coef[ch[1][i]][j]);
      }
      tran[alpha][i] = coef[ch[1][i]][alpha];
    }
  }
  tran[alpha][alpha] = 1;
  for (int i = 2; i < base; ++i) {
    power0[i] = power0[i - 1] * power0[1];
  }
  power1[1].x = power1[1].y = alpha + 1;
  power1[1] = power0[base - 1] * power0[1];
  for (int i = 2; i < base; ++i) {
    power1[i] = power1[i - 1] * power1[1];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q >> s;
  len[0] = -1;
  last = new_node(0);
  for (int i = 0; i < n; ++i) {
    extend(s[i] - 'a');
  }
  matrix_init();
  while (q--) {
    int x;
    cin >> x;
    matrix_t result;
    result.x = 1;
    result.y = alpha + 1;
    result[0][alpha] = 1;
    result = result * power0[x % base] * power1[x / base];
    int answer = 0;
    for (int i = 0; i < result.y; ++i) {
      add(answer, result[0][i]);
    }
    cout << answer << '\n';
  }
  return 0;
}
