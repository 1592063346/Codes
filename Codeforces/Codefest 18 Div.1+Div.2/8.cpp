#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, q, last, t, tt, ch[N][26], father[N], len[N], c[N], sorted[N], root[N], lc[N * 30], rc[N * 30], one[N * 30];
char s[N], s2[N];

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

#define lo lc[o]
#define ro rc[o]

void modify(int l, int r, int& o, int p) {
  if (!o) {
    o = ++tt;
  }
  if (l == r) {
    one[o] = l;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, lo, p);
    } else {
      modify(mid + 1, r, ro, p);
    }
    one[o] = ~one[lo] ? one[lo] : one[ro];
  }
}

int merge(int x, int y) {
  if (!x || !y) {
    return x | y;
  } else {
    int o = ++tt;
    lo = merge(lc[x], lc[y]);
    ro = merge(rc[x], rc[y]);
    one[o] = ~one[lo] ? one[lo] : one[ro];
    return o;
  }
}

int query(int l, int r, int o, int ql, int qr) {
  if (!o) {
    return -1;
  }
  if (ql <= l && r <= qr) {
    return one[o];
  } else {
    int mid = l + r >> 1, result = -1;
    if (ql <= mid) {
      result = query(l, mid, lo, ql, qr);
    } if (!~result && qr > mid) {
      result = query(mid + 1, r, ro, ql, qr);
    }
    return result;
  }
}

void print(int l, int r) {
  for (int i = l; i <= r; ++i) {
    printf("%c", s[i]);
  }
  puts("");
}

int main() {
  len[0] = -1;
  last = newnode(0);
  scanf("%s%d", s, &q);
  n = strlen(s);
  memset(one, -1, sizeof one);
  for (int i = 0; i < n; ++i) {
    extend(s[i] - 'a');
    modify(0, n - 1, root[last], i);
  }
  radix_sort();
  for (int i = t; i > 1; --i) {
    int u = sorted[i];
    root[father[u]] = merge(root[father[u]], root[u]);
  }
  for (int i = 1; i <= q; ++i) {
    int l, r;
    scanf("%d%d%s", &l, &r, s2);
    --l;
    --r;
    int m = strlen(s2);
    pair<int, int> answer(-1, -1);
    for (int j = 0, o = 1; j <= m && l + j <= r; ++j) {
      for (int k = j < m ? s2[j] - 'a' + 1 : 0; k < 26; ++k) {
        int x = ch[o][k];
        if (!x) {
          continue;
        }
        int pos = query(0, n - 1, root[x], l + j, r);
        if (~pos) {
          answer.first = pos - j;
          answer.second = pos;
          break;
        }
      }
      o = ch[o][s2[j] - 'a'];
      if (!o) {
        break;
      }
    }
    if (~answer.first) {
      print(answer.first, answer.second);
    } else {
      puts("-1");
    }
  }
  return 0;
}
