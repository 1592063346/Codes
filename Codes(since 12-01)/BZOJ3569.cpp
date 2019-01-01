#include<bits/stdc++.h>

using namespace std;

template<typename T> inline void read(T& x) {
  char c = getchar();
  bool f = false;
  for (x = 0; !isdigit(c); c = getchar()) {
    if (c == '-') {
      f = true;
    }
  }
  for (; isdigit(c); c = getchar()) {
    x = x * 10 + c - '0';
  }
  if (f) {
    x = -x;
  }
}

template<typename T, typename... U> inline void read(T& x, U&... y) {
  read(x), read(y...);
}

const int N = 5e5 + 10;

struct edge {
  int to, value;
  bool visit, on_tree;

  edge () {}
  edge (int to): to(to) {
    on_tree = visit = false;
    value = 0;
  }
} edges[N << 1];

int n, m, q, all, tt, tag[N], bas[31];
bool visit[N];
vector<int> graph[N];

int random_number() {
  return (rand() << 15) | rand();
}

void dfs1(int u) {
  visit[u] = true;
  for (int i = 0; i < graph[u].size(); ++i) {
    edge& e = edges[graph[u][i]];
    if (!e.visit) {
      e.visit = edges[graph[u][i] ^ 1].visit = true;
      if (!visit[e.to]) {
        e.on_tree = true;
        dfs1(e.to);
      } else {
        int value = random_number();
        e.value = edges[graph[u][i] ^ 1].value = value;
        tag[u] ^= value;
        tag[e.to] ^= value;
      }
    }
  }
}

void dfs2(int u) {
  visit[u] = true;
  for (int i = 0; i < graph[u].size(); ++i) {
    edge& e = edges[graph[u][i]];
    if (e.on_tree) {
      dfs2(e.to);
      e.value = edges[graph[u][i] ^ 1].value = tag[e.to];
      tag[u] ^= tag[e.to];
    }
  }
}

void insert(int value) {
  for (int i = 30; ~i; --i) {
    if (value >> i & 1) {
      if (bas[i]) {
        value ^= bas[i];
      } else {
        ++all;
        bas[i] = value;
        for (int j = 0; j < i; ++j) {
          if (bas[i] >> j & 1) {
            bas[i] ^= bas[j];
          }
        }
        for (int j = i + 1; j < 31; ++j) {
          if (bas[j] >> i & 1) {
            bas[j] ^= bas[i];
          }
        }
        return;
      }
    }
  }
}

int main() {
  srand(time(0));
  read(n, m);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    read(x, y);
    edges[tt++] = edge(y);
    edges[tt++] = edge(x);
    graph[x].push_back(tt - 2);
    graph[y].push_back(tt - 1);
  }
  dfs1(1);
  memset(visit, false, sizeof visit);
  dfs2(1);
  scanf("%d", &q);
  int answer = 0;
  while (q--) {
    int k, x;
    read(k);
    memset(bas, 0, sizeof bas);
    all = 0;
    for (int i = 0; i < k; ++i) {
      read(x);
      x = (x ^ answer) - 1;
      insert(edges[x << 1].value);
    }
    if (k - all > 0) {
      puts("Disconnected");
    } else {
      ++answer;
      puts("Connected");
    }
  }
  return 0;
}
