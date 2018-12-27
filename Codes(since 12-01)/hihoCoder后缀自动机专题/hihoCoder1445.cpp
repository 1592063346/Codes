#include<bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

int n, t, last, ch[N][26], father[N], len[N];
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

int main() {
  len[0] = -1;
  last = newnode(0);
  scanf("%s", s);
  n = strlen(s);
  for (int i = 0; i < n; ++i) {
    extend(s[i] - 'a');
  }
  long long answer = 0;
  for (int i = 2; i <= t; ++i) {
    answer += len[i] - len[father[i]];
  }
  printf("%lld\n", answer);
  return 0;
}
