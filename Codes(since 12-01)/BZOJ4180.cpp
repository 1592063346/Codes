#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
const long long inf = 2e18;

template<typename T> void cmin(T& a, const T& b) {
  if (a > b) {
    a = b;
  }
}

int n, last, ch[N][4], len[N], father[N], c[N], sorted[N], f[N][4], t;
long long need;
char s[N];

int newnode(int from) {
  ++t;
  len[t] = len[from] + 1;
  return t;
}

void extend(int c) {
  int p = last, np = newnode(p);
  for (; p && !ch[p][c]; p = father[p]) {
    ch[p][c] = np;
  }
  if (!p) {
    father[np] = 1;
  } else {
    int q = ch[p][c];
    if (len[p] + 1 == len[q]) {
      father[np] = q;
    } else {
      int nq = newnode(p);
      memcpy(ch[nq], ch[q], sizeof ch[q]);
      father[nq] = father[q];
      father[np] = father[q] = nq;
      for (; p && ch[p][c] == q; p = father[p]) {
        ch[p][c] = nq;
      }
    }
  }
  last = np;
}

void radix_sort() {
  for (int i = 1; i <= t; ++i) {
    ++c[len[i]];
  }
  for (int i = 1; i <= n; ++i) {
    c[i] += c[i - 1];
  }
  for (int i = t; i; --i) {
    sorted[c[len[i]]--] = i;
  }
}

struct matrix {
  long long a[4][4];

  matrix () {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        a[i][j] = inf;
      }
    }
  }

  matrix operator * (matrix b) {
    matrix result;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        for (int k = 0; k < 4; ++k) {
          cmin(result.a[i][j], a[i][k] + b.a[k][j]);
        }
      }
    }
    return result;
  }

  long long find() {
    long long result = inf;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        cmin(result, a[i][j]);
      }
    }
    return result;
  }
} tran;

matrix qpow(matrix v, long long p) {
  matrix result;
  for (int i = 0; i < 4; ++i) {
    result.a[i][i] = 0;
  }
  for (; p; p >>= 1, v = v * v) {
    if (p & 1) {
      result = result * v;
    }
  }
  return result;
}

int main() {
  len[0] = -1;
  last = newnode(0);
  scanf("%lld%s", &need, s);
  n = strlen(s);
  for (int i = 0; i < n; ++i) {
    extend(s[i] - 'A');
  }
  radix_sort();
  memset(f, 0x3f, sizeof f);
  for (int i = t; i > 1; --i) {
    int u = sorted[i];
    for (int j = 0; j < 4; ++j) {
      if (!ch[u][j]) {
        f[u][j] = 1;
      } else {
        for (int k = 0; k < 4; ++k) {
          cmin(f[u][j], f[ch[u][k]][j] + 1);
        }
      }
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (ch[1][i]) {
        tran.a[i][j] = f[ch[1][i]][j];
      }
    }
  }
  long long l = 1, r = need;
  while (l != r) {
    long long mid = l + r >> 1;
    if (qpow(tran, mid).find() < need) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  printf("%lld\n", l);
  return 0;
}
