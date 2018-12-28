#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, t, k, last, ch[N][26], father[N], len[N], c[N], sorted[N], f[N][21], a[N], visit[N];
char s[N], num[N];

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
  scanf("%s%s%d", s, num, &k);
  n = strlen(s);
  a[0] = num[0] == '0';
  for (int i = 1; i < n; ++i) {
    a[i] = a[i - 1] + (num[i] == '0');
  }
  for (int i = 0; i < n; ++i) {
    extend(s[i] - 'a');
  }
  radix_sort();
  for (int i = 2; i <= t; ++i) {
    int u = sorted[i];
    visit[u] = len[father[u]];
    f[u][0] = father[u];
    for (int j = 1; (1 << j) <= t; ++j) {
      f[u][j] = f[f[u][j - 1]][j - 1];
    }
  }
  int u = 1;
  long long answer = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    u = ch[u][s[i] - 'a'];
    for (; a[i] - (!j ? 0 : a[j - 1]) > k; ++j);
    int length = i - j + 1, x = u;
    for (int j = 19; ~j; --j) {
      if (len[f[x][j]] >= length) {
        x = f[x][j];
      }
    }
    if (x != 1) {
      answer += max(0, min(len[x], length) - visit[x]);
      visit[x] = max(visit[x], min(len[x], length));
      for (x = father[x]; x != 1 && visit[x] != len[x]; x = father[x]) {
        answer += len[x] - visit[x];
        visit[x] = len[x];
      }
    }
  }
  printf("%lld\n", answer);
  return 0;
}
