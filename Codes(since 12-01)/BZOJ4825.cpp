#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, root, h[N], opt[N], value[N], ch[N][2], father[N], tag[N << 2];
set<int> numbers;

void push_down(int o) {
  if (tag[o]) {
    tag[o << 1] += tag[o];
    tag[o << 1 | 1] += tag[o];
    tag[o] = 0;
  }
}

void modify(int l, int r, int o, int ql, int qr, bool add, int v) {
  if (ql <= l && r <= qr) {
    if (add) {
      tag[o] += v;
    } else {
      tag[o] = v;
    }
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (qr <= mid) {
      modify(l, mid, o << 1, ql, qr, add, v);
    } else if (ql > mid) {
      modify(mid + 1, r, o << 1 | 1, ql, qr, add, v);
    } else {
      modify(l, mid, o << 1, ql, qr, add, v);
      modify(mid + 1, r, o << 1 | 1, ql, qr, add, v);
    }
  }
}

int query(int l, int r, int o, int p) {
  if (l == r) {
    return tag[o];
  } else {
    int mid = l + r >> 1;
    push_down(o);
    if (p <= mid) {
      return query(l, mid, o << 1, p);
    } else {
      return query(mid + 1, r, o << 1 | 1, p);
    }
  }
}

int main() {
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &opt[i]);
    if (opt[i] == 1) {
      scanf("%d", &value[i]);
      h[++n] = value[i];
    }
  }
  sort(h + 1, h + 1 + n);
  for (int i = 1; i <= m; ++i) {
    if (opt[i] == 1) {
      value[i] = lower_bound(h + 1, h + 1 + n, value[i]) - h;
    }
  }
  for (int i = 1; i <= m; ++i) {
    int answer;
    if (opt[i] == 1) {
      numbers.insert(value[i]);
      set<int>:: iterator l = numbers.find(value[i]), r = l;
      bool find_l = true, find_r = true;
      if (l == numbers.begin()) {
        find_l = false;
      }
      --l;
      if (++r == numbers.end()) {
        find_r = false;
      }
      if (!find_l && !find_r) {
        root = value[i];
        modify(1, n, 1, value[i], value[i], false, answer = 1);
      } else if ((find_l && !find_r) || (find_l && find_r && query(1, n, 1, *l) > query(1, n, 1, *r))) {
        ch[*l][1] = value[i];
        father[value[i]] = *l;
        modify(1, n, 1, value[i], value[i], false, answer = query(1, n, 1, *l) + 1);
      } else {
        ch[*r][0] = value[i];
        father[value[i]] = *r;
        modify(1, n, 1, value[i], value[i], false, answer = query(1, n, 1, *r) + 1);
      }
    } else if (opt[i] == 2 || opt[i] == 4) {
      int p = *numbers.begin();
      answer = query(1, n, 1, p);
      modify(1, n, 1, p, p, false, 1);
      if (root != p) {
        modify(1, n, 1, father[p], n, true, 1);
        ch[father[p]][0] = 0;
        if (ch[p][1]) {
          int c = ch[p][1];
          ch[father[p]][0] = c;
          father[c] = father[p];
        }
        father[p] = 0;
        father[root] = p;
        ch[p][1] = root;
        root = p;
      }
      if (opt[i] == 4) {
        numbers.erase(root);
        if (ch[root][1]) {
          if (root != n) {
            modify(1, n, 1, root + 1, n, true, -1);
          }
          root = ch[root][1];
          father[root] = 0;
        } else {
          root = 0;
        }
      }
    } else {
      int p = *--numbers.end();
      answer = query(1, n, 1, p);
      modify(1, n, 1, p, p, false, 1);
      if (root != p) {
        modify(1, n, 1, 1, father[p], true, 1);
        ch[father[p]][1] = 0;
        if (ch[p][0]) {
          int c = ch[p][0];
          ch[father[p]][1] = c;
          father[c] = father[p];
        }
        father[p] = 0;
        father[root] = p;
        ch[p][0] = root;
        root = p;
      }
      if (opt[i] == 5) {
        numbers.erase(root);
        if (ch[root][0]) {
          if (root != 1) {
            modify(1, n, 1, 1, root - 1, true, -1);
          }
          root = ch[root][0];
          father[root] = 0;
        } else {
          root = 0;
        }
      }
    }
    printf("%d\n", answer);
  }
  return 0;
}
