#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, a, b, tt, last, len[N << 1], ch[N << 1][26], father[N << 1], l[N], f[N];
char s[N];

int newnode(int p) {
  ++tt;
  len[tt] = len[p] + 1;
  return tt;
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

int main() {
  scanf("%d%d%d%s", &n, &a, &b, s + 1);
  len[0] = -1;
  last = newnode(0);
  for (int i = 1; i <= n; ++i) {
    l[i] = i;
  }
  for (int i = 1; i <= n; ++i) {
    int r = 0;
    for (int j = 1, u = 1; i + j - 1 <= n; ++j) {
      u = ch[u][s[i + j - 1] - 'a'];
      if (!u) {
        break;
      }
      r = j;
    }
    extend(s[i] - 'a');
    for (int j = 1; j <= r; ++j) {
      cmin(l[i + j - 1], i - 1);
    }
  }
  memset(f, 0x3f, sizeof f);
  f[0] = 0;
  for (int i = 1; i <= n; ++i) {
    f[i] = f[i - 1] + a;
    for (int j = l[i]; j < i; ++j) {
      cmin(f[i], f[j] + b);
    }
  }
  printf("%d\n", f[n]);
  return 0;
}
