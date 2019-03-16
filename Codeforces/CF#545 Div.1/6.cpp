#include<bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10;

int n, q, m, number[N], ch[N][2], father[N], degree[N], size[N], type[N], tt;
vector<int> adj[N];
bool rev[N], visit[N];
char cmd[8];

void add(int p, int v) {
  for (; p <= m; p += p & -p) {
    number[p] += v;
  }
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) {
    result += number[p];
  }
  return result;
}

bool is_root(int u) {
  return ch[father[u]][0] != u && ch[father[u]][1] != u;
}

int side(int f, int u) {
  return ch[f][1] == u;
}

void reverse(int u) {
  swap(ch[u][0], ch[u][1]);
  rev[u] = !rev[u];
}

void push(int u) {
  if (rev[u]) {
    if (ch[u][0]) {
      reverse(ch[u][0]);
    }
    if (ch[u][1]) {
      reverse(ch[u][1]);
    }
    rev[u] = false;
  }
  if (ch[u][0]) {
    type[ch[u][0]] = type[u];
  }
  if (ch[u][1]) {
    type[ch[u][1]] = type[u];
  }
}

void pull(int u) {
  size[u] = size[ch[u][0]] + size[ch[u][1]] + 1;
}

void rotate(int u) {
  int f = father[u], s1 = side(f, u), s2 = side(father[f], f), ano = ch[u][!s1];
  father[u] = father[f];
  if (!is_root(f)) {
    ch[father[f]][s2] = u;
  }
  father[ano] = f;
  ch[f][s1] = ano;
  father[f] = u;
  ch[u][!s1] = f;
  pull(f);
  pull(u);
}

void splay(int u) {
  vector<int> pstack(1, u);
  for (int i = u; !is_root(i); i = father[i]) {
    pstack.push_back(father[i]);
  }
  for (; pstack.size(); pstack.pop_back()) {
    push(pstack.back());
  }
  for (; !is_root(u); rotate(u)) {
    if (!is_root(father[u])) {
      if (side(father[u], u) == side(father[father[u]], father[u])) {
        rotate(father[u]);
      } else {
        rotate(u);
      }
    }
  }
}

void access(int u) {
  for (int x = 0; u; x = u, u = father[u]) {
    splay(u);
    int diff = size[u] - size[ch[u][1]];
    ch[u][1] = x;
    add(type[u], -diff);
    add(tt, diff);
    pull(u);
  }
}

void make_root(int u) {
  access(u);
  splay(u);
  reverse(u);
}

int when(int u) {
  splay(u);
  return query(type[u] - 1) + size[ch[u][1]] + 1;
}

int main() {
  scanf("%d%d", &n, &q);
  m = n + q;
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
    ++degree[u];
    ++degree[v];
  }
  priority_queue<int, vector<int>, greater<int>> nodes;
  for (int i = 1; i <= n; ++i) {
    if (degree[i] == 1) {
      nodes.push(i);
    }
  }
  for (int i = 1; i <= n; ++i) {
    size[i] = 1;
  }
  while (!nodes.empty()) {
    int x = nodes.top();
    type[x] = ++tt;
    visit[x] = true;
    add(tt, 1);
    nodes.pop();
    for (auto v : adj[x]) {
      if (!visit[v]) {
        father[x] = v;
      }
      if (--degree[v] == 1) {
        nodes.push(v);
      }
    }
  }
  while (q--) {
    scanf("%s", cmd);
    int u, v;
    switch (*cmd) {
      case 'u':
        scanf("%d", &u);
        ++tt;
        make_root(u);
        type[u] = tt;
        break;
      case 'w':
        scanf("%d", &u);
        printf("%d\n", when(u));
        break;
      case 'c':
        scanf("%d%d", &u, &v);
        printf("%d\n", when(u) > when(v) ? v : u);
        break;
    }
  }
  return 0;
}
