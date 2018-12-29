#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, t, q, last, ch[N][26], father[N], len[N], endpos[N], c[N], sorted[N], visit[N];
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
  scanf("%s", s);
  n = strlen(s);
  for (int i = 0; i < n; ++i) {
    extend(s[i] - 'a');
    endpos[last] = 1;
  }
  radix_sort();
  for (int i = t; i > 1; --i) {
    int u = sorted[i];
    endpos[father[u]] += endpos[u];
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%s", s);
    int m = strlen(s), u = 1, length = 0, answer = 0;
    for (int j = 0; j < m << 1; ++j) {
      int c = s[j % m] - 'a';
      for (; u != 1 && !ch[u][c]; u = father[u]) {
        length = len[father[u]];
      }
      if (ch[u][c]) {
        u = ch[u][c];
        ++length;
      }
      if (length >= m) {
        for (; len[father[u]] >= m; u = father[u]) {
          length = len[father[u]];
        }
      }
      if (length >= m && visit[u] != i) {
        answer += endpos[u];
        visit[u] = i;
      }
    }
    printf("%d\n", answer);
  }
  return 0;
}
