#include<bits/stdc++.h>

using namespace std;

const int N = 55, mod = 1e9 + 7;

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

int n, a[N][N], b[N][N];
bool old[N][N];

int matrix_tree() {
  int result = 1;
  for (int i = 1; i < n; ++i) {
    int rev = i;
    for (int j = i + 1; j < n; ++j) {
      if (a[j][i]) {
        rev = j;
        break;
      }
    }
    if (rev != i) {
      result = (mod - result) % mod;
      for (int j = i; j < n; ++j) {
        swap(a[i][j], a[rev][j]);
      }
    }
    for (int j = i + 1; j < n; ++j) {
      int p = mul(a[j][i], qpow(a[i][i], mod - 2));
      for (int k = i; k < n; ++k) {
        sub(a[j][k], mul(p, a[i][k]));
      }
    }
    result = mul(result, a[i][i]);
  }
  return result;
}

class TreeDistance {
public:
  int countTrees(vector<int> p, int c) {
    n = p.size() + 1;
    for (int i = 0; i < p.size(); ++i) {
      old[p[i]][i + 1] = old[i + 1][p[i]] = true;
    }
    for (int x = 0; x < n; ++x) {
      memset(a, 0, sizeof a);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          int v = old[i][j] ? x : 1;
          add(a[j][j], v);
          sub(a[i][j], v);
        }
      }
      for (int i = 0, v = 1; i < n; ++i, v = mul(v, x)) {
        b[x][i] = v;
      }
      b[x][n] = matrix_tree();
    }
    for (int i = 0; i < n; ++i) {
      int rev = i;
      for (int j = i + 1; j < n; ++j) {
        if (b[j][i]) {
          rev = j;
          break;
        }
      }
      if (rev != i) {
        for (int j = i; j <= n; ++j) {
          swap(b[i][j], b[rev][j]);
        }
      }
      for (int j = i + 1; j < n; ++j) {
        int p = mul(b[j][i], qpow(b[i][i], mod - 2));
        for (int k = i; k <= n; ++k) {
          sub(b[j][k], mul(p, b[i][k]));
        }
      }
    }
    for (int i = n - 1; ~i; --i) {
      for (int j = i + 1; j < n; ++j) {
        sub(b[i][n], mul(b[i][j], b[j][n]));
      }
      b[i][n] = mul(b[i][n], qpow(b[i][i], mod - 2));
    }
    int answer = 0;
    for (int i = n - 1; i >= max(0, n - 1 - c); --i) {
      add(answer, b[i][n]);
    }
    return answer;
  }
};
/*
TreeDistance solver;

int main() {
  int n, k;
  scanf("%d", &n);
  vector<int> p(n - 1);
  for (int i = 0; i < n - 1; ++i) {
    scanf("%d", &p[i]);
  }
  scanf("%d", &k);
  printf("%d\n", solver.countTrees(p, k));
  return 0;
}
*/
