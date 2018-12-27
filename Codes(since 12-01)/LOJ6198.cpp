#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, w[N], c[N], x[N], y[N], sa[N], suffix_rank[N], f[N], root[N], ch[N * 300][2], node_cnt;
vector<pair<int, int>> sets[N];
vector<int> number[N];
char str[N];

int find(int x) {
  return f[x] == x ? x : f[x] = find(f[x]);
}

void build_sa(int m) {
  for (int i = 0; i < n; ++i) {
    ++c[x[i] = str[i]];
  }
  for (int i = 1; i < m; ++i) {
    c[i] += c[i - 1];
  }
  for (int i = n - 1; ~i; --i) {
    sa[--c[x[i]]] = i;
  }
  for (int k = 1; k <= n; k <<= 1) {
    int p = 0;
    for (int i = n - 1; i >= n - k; --i) {
      y[p++] = i;
    }
    for (int i = 0; i < n; ++i) {
      if (sa[i] >= k) {
        y[p++] = sa[i] - k;
      }
    }
    fill(c, c + m, 0);
    for (int i = 0; i < n; ++i) {
      ++c[x[y[i]]];
    }
    for (int i = 1; i < m; ++i) {
      c[i] += c[i - 1];
    }
    for (int i = n - 1; ~i; --i) {
      sa[--c[x[y[i]]]] = y[i];
    }
    swap(x, y);
    x[sa[0]] = 0;
    p = 1;
    for (int i = 1; i < n; ++i) {
      x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p - 1 : p++;
    }
    if (p >= n) {
      break;
    }
    m = p;
  }
}

void build_height() {
  for (int i = 0; i < n; ++i) {
    suffix_rank[sa[i]] = i;
  }
  for (int i = 0, k = 0; i < n; ++i) {
    k -= k ? 1 : 0;
    if (!suffix_rank[i]) {
      continue;
    }
    int j = sa[suffix_rank[i] - 1];
    for (; str[i + k] == str[j + k]; ++k);
    sets[k].emplace_back(i, j);
  }
}

void insert(int o, int value) {
  for (int i = 16; ~i; --i) {
    int c = value >> i & 1;
    if (!ch[o][c]) {
      ch[o][c] = ++node_cnt;
    }
    o = ch[o][c];
  }
}

int find(int u, int v, int d) {
  if (d < 0) {
    return 0;
  } else {
    int answer = -1;
    if (ch[u][0] && ch[v][1]) {
      answer = max(answer, find(ch[u][0], ch[v][1], d - 1) + (1 << d));
    }
    if (ch[u][1] && ch[v][0]) {
      answer = max(answer, find(ch[u][1], ch[v][0], d - 1) + (1 << d));
    }
    if (!~answer) {
      if (ch[u][0] && ch[v][0]) {
        answer = max(answer, find(ch[u][0], ch[v][0], d - 1));
      }
      if (ch[u][1] && ch[v][1]) {
        answer = max(answer, find(ch[u][1], ch[v][1], d - 1));
      }
    }
    return answer;
  }
}

int merge(int u, int v) {
  u = find(u);
  v = find(v);
  int result = find(root[u], root[v], 16);
  if (number[u].size() > number[v].size()) {
    swap(u, v);
  }
  for (auto x : number[u]) {
    insert(root[v], x);
    number[v].push_back(x);
  }
  number[u].clear();
  f[u] = v;
  return result;
}

int main() {
  scanf("%d%s", &n, str);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &w[i]);
    number[i].push_back(w[i]);
    root[i] = ++node_cnt;
    insert(root[i], w[i]);
  }
  build_sa('z' + 1);
  build_height();
  for (int i = 0; i < n; ++i) {
    f[i] = i;
  }
  int answer = 0;
  for (int i = n; ~i; --i) {
    for (auto v : sets[i]) {
      int x = v.first;
      int y = v.second;
      answer = max(answer, merge(x, y) + i);
    }
  }
  printf("%d\n", answer);
  return 0;
}
