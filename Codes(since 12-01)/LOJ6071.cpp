#include<bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10, mod = 1e9 + 7;

int n, last, t, start[N], ch[N][26], father[N], len[N], c[N], sorted[N], f[26], g[N];
char s[N];

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int newnode(int from) {
  len[++t] = len[from] + 1;
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

int main() {
  len[0] = -1;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s + start[i]);
    start[i + 1] = start[i] + strlen(s + start[i]);
  }
  for (int i = n; i; --i) {
    last = newnode(0);
    for (int j = start[i]; j < start[i + 1]; ++j) {
      extend(s[j] - 'a');
    }
    for (int j = 0; j <= start[i + 1] - start[i]; ++j) {
      c[j] = 0;
    }
    for (int j = 1; j <= t; ++j) {
      ++c[len[j]];
    }
    for (int j = 1; j <= start[i + 1] - start[i]; ++j) {
      c[j] += c[j - 1];
    }
    for (int j = t; j; --j) {
      sorted[c[len[j]]--] = j;
    }
    for (int j = t; j != 1; --j) {
      int u = sorted[j];
      g[u] = 1;
      for (int k = 0; k < 26; ++k) {
        if (ch[u][k]) {
          add(g[u], g[ch[u][k]]);
        } else {
          add(g[u], f[k]);
        }
      }
    }
    for (int j = 0; j < 26; ++j) {
      if (ch[1][j]) {
        f[j] = g[ch[1][j]];
      }
    }
    for (int j = 1; j <= t; ++j) {
      memset(ch[j], 0, sizeof ch[j]);
      father[j] = 0;
      len[j] = 0;
    }
    t = 0;
  }
  int answer = 1;
  for (int i = 0; i < 26; ++i) {
    add(answer, f[i]);
  }
  printf("%d\n", answer);
  return 0;
}
