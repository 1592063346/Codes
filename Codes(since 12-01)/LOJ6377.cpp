#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m, tt, last, len[N], father[N], ch[N][26], number[N], u[N], sg[N];
bool visit[N];
char s[N], t[N * 200];

int newnode(int from) {
  len[++tt] = len[from] + 1;
  father[tt] = 0;
  memset(ch[tt], 0, sizeof ch[tt]);
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

void radix_sort() {
  for (int i = 1; i <= m; ++i) {
    number[i] = 0;
  }
  for (int i = 1; i <= tt; ++i) {
    ++number[len[i]];
  }
  for (int i = 1; i <= m; ++i) {
    number[i] += number[i - 1];
  }
  for (int i = tt; i; --i) {
    u[number[len[i]]--] = i;
  }
}

void get_sg() {
  radix_sort();
  for (int i = tt; i; --i) {
    for (int c = 0; c < 26; ++c) {
      visit[c] = false;
    }
    for (int c = 0; c < 26; ++c) {
      if (ch[u[i]][c]) {
        visit[sg[ch[u[i]][c]]] = true;
      }
    }
    for (int c = 0; c < 26; ++c) {
      if (!visit[c]) {
        sg[u[i]] = c;
        break;
      }
    }
  }
}

int main() {
  len[0] = -1;
  while (scanf("%s", s) == 1) {
    tt = 0;
    last = newnode(0);
    m = strlen(s);
    for (int i = 0; i < m; ++i) {
      extend(s[i] - 'a');
    }
    get_sg();
    scanf("%d", &n);
    int answer = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%s", t);
      m = strlen(t);
      int x = 1;
      for (int j = 0; j < m; ++j) {
        if (!ch[x][t[j] - 'a']) {
          goto next_string;
        } else {
          x = ch[x][t[j] - 'a'];
        }
      }
      answer ^= sg[x];
      next_string: continue;
    }
    puts(answer ? "Alice" : "Bob");
  }
  return 0;
}
