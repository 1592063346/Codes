#include<bits/stdc++.h>

using namespace std;

const int N = 34567, mod = 10007;

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int x, int y) {
  int result = 1;
  for (; y; y >>= 1, x = mul(x, x)) {
    if (y & 1) {
      result = mul(result, x);
    }
  }
  return result;
}

int n, q, k[N], p[N], b[N], kk[N], bb[N], parent[N], top[N], father[N], ch[N][2];

int find(int x) {
  return parent[x] == x ? x : parent[x] = find(parent[x]);
}

bool is_root(int x) {
  int f = father[x];
  return ch[f][0] != x && ch[f][1] != x;
}

int side(int x) {
  int f = father[x];
  return ch[f][1] == x;
}

void pull(int x) {
  int l = ch[x][0], r = ch[x][1];
  kk[x] = k[x];
  bb[x] = b[x];
  top[x] = x;
  if (l) {
    top[x] = top[l];
    bb[x] = (mul(kk[x], bb[l]) + bb[x]) % mod;
    kk[x] = mul(kk[x], kk[l]);
  }
  if (r) {
    bb[x] = (mul(kk[r], bb[x]) + bb[r]) % mod;
    kk[x] = mul(kk[r], kk[x]);
  }
}

void rotate(int x) {
  int f = father[x], s = side(x), ano = ch[x][!s], fs = side(f);
  father[x] = father[f];
  if (!is_root(f)) {
    ch[father[f]][fs] = x;
  }
  father[ano] = f;
  ch[f][s] = ano;
  father[f] = x;
  ch[x][!s] = f;
  pull(f);
  pull(x);
}

void splay(int x) {
  for (; !is_root(x); rotate(x)) {
    int f = father[x];
    if (!is_root(f)) {
      if (side(x) == side(f)) {
        rotate(f);
      } else {
        rotate(x);
      }
    }
  }
}

void access(int x) {
  for (int y = 0; x; y = x, x = father[x]) {
    splay(x);
    ch[x][1] = y;
    pull(x);
  }
}

int find_root(int x) {
  access(x);
  splay(x);
  return top[x];
}

void link(int x, int y) {
  access(x);
  splay(x);
  father[x] = y;
}

void cut(int x) {
  access(x);
  splay(x);
  father[ch[x][0]] = 0;
  ch[x][0] = 0;
  pull(x);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> k[i] >> p[i] >> b[i];
    parent[i] = i;
  }
  for (int i = 1; i <= n; ++i) {
    if (find(i) != find(p[i])) {
      parent[find(i)] = find(p[i]);
      father[i] = p[i];
    }
    pull(i);
  }
  cin >> q;
  while (q--) {
    string cmd;
    cin >> cmd;
    int a, x, y, z;
    if (cmd == "A") {
      cin >> a;
      int final_root = p[find_root(a)];
      access(final_root);
      splay(final_root);
      int k_value = kk[final_root], b_value = bb[final_root], value;
      if (k_value == 1 && b_value == 0) {
        cout << -2 << '\n';
      } else if (k_value == 1 && b_value != 0) {
        cout << -1 << '\n';
      } else {
        value = mul(b_value, qpow((1 - k_value + mod) % mod, mod - 2));
        access(a);
        splay(a);
        cout << ((mul(value, kk[a]) + bb[a]) % mod) << '\n';
      }
    } else {
      cin >> a >> x >> y >> z;
      access(a);
      splay(a);
      if (!ch[a][0]) {
        if (find_root(y) == a) {
          splay(a);
        } else {
          link(a, y);
        }
      } else {
        bool on_circle = false;
        int root = top[a], final_root = p[root];
        access(final_root);
        splay(a);
        if (top[a] == root) {
          on_circle = true;
        }
        cut(a);
        if (on_circle) {
          link(root, final_root);
        }
        if (find_root(y) == a) {
          splay(a);
        } else {
          link(a, y);
        }
      }
      p[a] = y;
      k[a] = x;
      b[a] = z;
      pull(a);
    }
  }
  return 0;
}
