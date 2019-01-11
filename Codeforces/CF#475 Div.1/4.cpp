#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, t, q, last, ch[N][26], father[N], len[N], c[N], sorted[N], root[N], lo[N * 20], ro[N * 20], arr[N], tt;
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

void modify(int l, int r, int& o, int p) {
  if (!o) {
    o = ++tt;
  }
  if (l == r) {
    return;
  } else {
    int mid = l + r >> 1;
    if (p <= mid) {
      modify(l, mid, lo[o], p);
    } else {
      modify(mid + 1, r, ro[o], p);
    }
  }
}

int merge(int x, int y) {
  if (!x || !y) {
    return x | y;
  } else {
    int o = ++tt;
    lo[o] = merge(lo[x], lo[y]);
    ro[o] = merge(ro[x], ro[y]);
    return o;
  }
}

void get_all_pos(int l, int r, int o) {
  if (l == r) {
    arr[++tt] = l;
  } else {
    int mid = l + r >> 1;
    if (lo[o]) {
      get_all_pos(l, mid, lo[o]);
    }
    if (ro[o]) {
      get_all_pos(mid + 1, r, ro[o]);
    }
  }
}

int main() {
  len[0] = -1;
  last = newnode(0);
  scanf("%s", s);
  n = strlen(s);
  for (int i = 0; i < n; ++i) {
    extend(s[i] - 'a');
    modify(1, n, root[last], i + 1);
  }
  radix_sort();
  for (int i = t; i > 1; --i) {
    int u = sorted[i];
    root[father[u]] = merge(root[father[u]], root[u]);
  }
  scanf("%d", &q);
  while (q--) {
    int k;
    scanf("%d%s", &k, s);
    int m = strlen(s), u = 1;
    bool find = true;
    for (int i = 0; i < m; ++i) {
      int c = s[i] - 'a';
      if (!ch[u][c]) {
        find = false;
        break;
      }
      u = ch[u][c];
    }
    if (!find) {
      puts("-1");
    } else {
      tt = 0;
      get_all_pos(1, n, root[u]);
      if (tt < k) {
        puts("-1");
      } else {
        int answer = 0x3f3f3f3f;
        for (int i = 1, j = k; j <= tt; ++i, ++j) {
          answer = min(answer, arr[j] - arr[i] + m);
        }
        printf("%d\n", answer);
      }
    }
  }
  return 0;
}
