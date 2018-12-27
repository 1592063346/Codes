#include<bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

int tt, n, t, last, ch[N][11], father[N], len[N], answer[N], c[N], sorted[N], value[N];
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
  if (!ch[p][c]) {
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

int main() {
  len[0] = -1;
  last = newnode(0);
  scanf("%d", &tt);
  for (int i = 1; i <= tt; ++i) {
    scanf("%s", s + n);
    n += strlen(s + n);
    s[n] = ':';
    ++n;
  }
  for (int i = 0; i < n; ++i) {
    extend(s[i] - '0');
  }
  radix_sort();
  value[1] = 1;
  int result = 0;
  for (int i = 1; i <= t; ++i) {
    int u = sorted[i];
    add(result, answer[u]);
    for (int j = 0; j < 10; ++j) {
      if (ch[u][j]) {
        add(answer[ch[u][j]], (answer[u] * 10ll + 1ll * j * value[u]) % mod);
        add(value[ch[u][j]], value[u]);
      }
    }
  }
  printf("%d\n", result);
  return 0;
}
