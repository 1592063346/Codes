#include<bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

int n, t, last, ch[N][26], father[N], len[N], c[N], sorted[N], endpos[N], answer[N];
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
    answer[len[u]] = max(answer[len[u]], endpos[u]);
    endpos[father[u]] += endpos[u];
  }
  for (int i = n - 1; i; --i) {
    answer[i] = max(answer[i], answer[i + 1]);
  }
  for (int i = 1; i <= n; ++i) {
    printf("%d\n", answer[i]);
  }
  return 0;
}
