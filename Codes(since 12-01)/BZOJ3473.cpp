#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int tt, n, t, k, last, ch[N][27], father[N], len[N], c[N], sorted[N], f[N][21], size[N];
set<int> endpos[N];
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
  scanf("%d%d", &tt, &k);
  for (int i = 1; i <= tt; ++i) {
    scanf("%s", s + n);
    n += strlen(s + n);
    s[n++] = 'z' + 1;
  }
  for (int i = 0, from = 1; i < n; ++i) {
    extend(s[i] - 'a');
    if (s[i] - 'a' == 26) {
      ++from;
    } else {
      endpos[last].insert(from);
    }
  }
  radix_sort();
  for (int i = t; i > 1; --i) {
    int u = sorted[i];
    size[u] = endpos[u].size();
    if (endpos[u].size() > endpos[father[u]].size()) {
      swap(endpos[u], endpos[father[u]]);
    }
    for (set<int>:: iterator it = endpos[u].begin(); it != endpos[u].end(); ++it) {
      endpos[father[u]].insert(*it);
    }
    endpos[u].clear();
  }
  size[0] = k + 1;
  size[1] = endpos[1].size();
  for (int i = 2; i <= t; ++i) {
    int u = sorted[i];
    f[u][0] = father[u];
    for (int j = 1; (1 << j) <= t; ++j) {
      f[u][j] = f[f[u][j - 1]][j - 1];
    }
  }
  int u = 1;
  long long answer = 0;
  for (int i = 0, from = -1; i < n; ++i) {
    if (s[i] == 'z' + 1) {
      printf("%lld%c", answer, " \n"[i + 1 == n]);
      answer = 0;
      from = i;
      u = 1;
    } else {
      u = ch[u][s[i] - 'a'];
      int x = u;
      for (int j = 19; ~j; --j) {
        if (size[f[x][j]] < k) {
          x = f[x][j];
        }
      }
      if (size[x] < k) {
        x = f[x][0];
      }
      answer += min(len[x], i - from);
    }
  }
  return 0;
}
