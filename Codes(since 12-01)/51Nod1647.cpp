#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, max_len = 1e6 + 10;

int n, t, tt, q, all, ch[max_len << 1][26], father[max_len << 1], len[max_len << 1], c[max_len], sorted[max_len << 1], endpos[max_len << 1], trie_t[max_len][26], f[max_len << 1][21], last_node[max_len];
char s[max_len];
vector<int> nodes[N];

int newnode(int from) {
  ++t;
  len[t] = len[from] + 1;
  return t;
}

void extend(int& last, int c) {
  int p = last;
  if (ch[p][c]) {
    int q = ch[p][c];
    if (len[p] + 1 == len[q]) {
      last = q;
    } else {
      int nq = newnode(p);
      memcpy(ch[nq], ch[q], sizeof ch[q]);
      father[nq] = father[q];
      father[q] = nq;
      for (; p && ch[p][c] == q; p = father[p]) {
        ch[p][c] = nq;
      }
      last = nq;
    }
  } else {
    int np = newnode(p);
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
}

void radix_sort() {
  for (int i = 1; i <= t; ++i) {
    ++c[len[i]];
  }
  for (int i = 1; i <= all; ++i) {
    c[i] += c[i - 1];
  }
  for (int i = t; i; --i) {
    sorted[c[len[i]]--] = i;
  }
}

void insert(int from, int m) {
  int u = 0;
  for (int i = 0; i < m; ++i) {
    int c = s[i] - 'a';
    if (!trie_t[u][c]) {
      trie_t[u][c] = ++tt;
      last_node[tt] = last_node[u];
      extend(last_node[tt], c);
      ++endpos[last_node[tt]];
    }
    u = trie_t[u][c];
    nodes[from].push_back(u);
  }
}

int main() {
  len[0] = -1;
  last_node[0] = newnode(0);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s);
    int m = strlen(s);
    all += m;
    insert(i, m);
  }
  radix_sort();
  for (int i = 2; i <= t; ++i) {
    int u = sorted[i];
    f[u][0] = father[u];
    for (int j = 1; (1 << j) <= t; ++j) {
      f[u][j] = f[f[u][j - 1]][j - 1];
    }
  }
  for (int i = t; i > 1; --i) {
    int u = sorted[i];
    endpos[father[u]] += endpos[u];
  }
  scanf("%d", &q);
  while (q--) {
    int p, x, y;
    scanf("%d%d%d", &p, &x, &y);
    --x;
    --y;
    int length = y - x + 1;
    int u = last_node[nodes[p][y]];
    for (int i = 20; ~i; --i) {
      if (len[f[u][i]] >= length) {
        u = f[u][i];
      }
    }
    printf("%d\n", endpos[u]);
  }
  return 0;
}
