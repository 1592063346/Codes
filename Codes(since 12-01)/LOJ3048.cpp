#include<bits/stdc++.h>

using namespace std;

const int N = 2e7 + 10;

int n, k, tt, pid[N], root[N];
long long a[N];

struct info_t {
  int p, l, r, x;
  long long value;

  info_t() {}
  info_t(int p, int l, int r, int x, long long value): p(p), l(l), r(r), x(x), value(value) {}

  bool operator < (const info_t& a) const {
    return value < a.value;
  }
};

struct node {
  int ch[2], number;
} nodes[N];

int insert(int u, int id, long long value) {
  int x = ++tt, z = x;
  nodes[x] = nodes[u];
  ++nodes[x].number;
  for (int i = 31; ~i; --i) {
    int y = value >> i & 1;
    nodes[x].ch[y] = ++tt;
    x = tt;
    u = nodes[u].ch[y];
    nodes[x] = nodes[u];
    ++nodes[x].number;
  }
  pid[x] = id; 
  return z;
}

int query(int ul, int ur, long long value) {
  for (int i = 31; ~i; --i) {
    int y = value >> i & 1;
    if (nodes[ur].ch[!y] && nodes[nodes[ur].ch[!y]].number - nodes[nodes[ul].ch[!y]].number) {
      ul = nodes[ul].ch[!y];
      ur = nodes[ur].ch[!y];
    } else {
      ul = nodes[ul].ch[y];
      ur = nodes[ur].ch[y];
    }
  }
  return pid[ur];
}

int main() {
  scanf("%d%d", &n, &k);
  ++n;
  root[1] = insert(root[0], 1, 0);
  for (int i = 2; i <= n; ++i) {
    scanf("%lld", &a[i]);
    a[i] ^= a[i - 1];
    root[i] = insert(root[i - 1], i, a[i]);
  }
  priority_queue<info_t> que;
  for (int i = 2; i <= n; ++i) {
    int x = query(root[0], root[i - 1], a[i]);
    que.emplace(i, 1, i - 1, x, a[i] ^ a[x]);
  }
  long long answer = 0;
  while (k--) {
    info_t s = que.top();
    que.pop();
    answer += s.value;
    if (s.l != s.x) {
      int x = query(root[s.l - 1], root[s.x - 1], a[s.p]);
      que.emplace(s.p, s.l, s.x - 1, x, a[s.p] ^ a[x]);
    }
    if (s.x != s.r) {
      int x = query(root[s.x], root[s.r], a[s.p]);
      que.emplace(s.p, s.x + 1, s.r, x, a[s.p] ^ a[x]);
    }
  }
  printf("%lld\n", answer);
  return 0;
}
