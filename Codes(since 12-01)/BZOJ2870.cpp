#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

template<typename T>
void cmax(T& x, T y) {
  if (x < y) {
    x = y;
  }
}

template<typename T>
void cmin(T& x, T y) {
  if (x > y) {
    x = y;
  }
}

int n, m, tt, min_diff, all, pu, pv, px, value[N], size[N], maxlen1[N], maxlen2[N], tag1[N], tag2[N];
vector<int> adj[N], nodes[N];
vector<pair<int, int>> go[N];
long long answer;
bool visit[N];

void dfs(int u, int p) {
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v != p) {
      nodes[u].push_back(v);
      dfs(v, u);
    }
  }
}

int newnode(int p, int x) {
  value[++m] = x;
  go[p].push_back(make_pair(m, 0));
  go[m].push_back(make_pair(p, 0));
  return m;
}

void build(int l, int r, int u, int anc) {
  if (l == r) {
    go[u].push_back(make_pair(nodes[anc][l], 1));
    go[nodes[anc][l]].push_back(make_pair(u, 1));
  } else {
    int mid = l + r >> 1;
    build(l, mid, l == mid ? u : newnode(u, value[anc]), anc);
    build(mid + 1, r, mid + 1 == r ? u : newnode(u, value[anc]), anc);
  }
}

void rebuild(int u) {
  if (nodes[u].size()) {
    build(0, nodes[u].size() - 1, u, u);
    for (int i = 0; i < nodes[u].size(); ++i) {
      rebuild(nodes[u][i]);
    }
  }
}

void find_edge(int u, int p) {
  size[u] = 1;
  for (int i = 0; i < go[u].size(); ++i) {
    int v = go[u][i].first;
    if (v != p && !visit[v]) {
      find_edge(v, u);
      size[u] += size[v];
      if (abs(all - 2 * size[v]) < min_diff) {
        min_diff = abs(all - 2 * size[v]);
        pu = u;
        pv = v;
        px = go[u][i].second;
      }
    }
  }
}

void get_all_info(int u, int p, int s, int minv, int* maxlen, int* tag, vector<int>& values) {
  values.push_back(value[u]);
  cmin(minv, value[u]);
  if (u <= n) {
    if (tag[minv] != tt) {
      tag[minv] = tt;
      maxlen[minv] = s;
    } else {
      cmax(maxlen[minv], s);
    }
  }
  for (int i = 0; i < go[u].size(); ++i) {
    int v = go[u][i].first;
    if (v != p && !visit[v]) {
      get_all_info(v, u, s + go[u][i].second, minv, maxlen, tag, values);
    }
  }
}

void solve(int u, int s) {
  if (s == 1) {
    return;
  }
  all = s;
  min_diff = s + 1;
  find_edge(u, 0);
  vector<int> value1, value2;
  int tu = ++tt;
  get_all_info(pu, pv, 0, 0xffff, maxlen1, tag1, value1);
  int tv = ++tt;
  get_all_info(pv, pu, 0, 0xffff, maxlen2, tag2, value2);
  sort(value1.begin(), value1.end());
  sort(value2.begin(), value2.end());
  for (int i = (int) value1.size() - 1, j = (int) value2.size() - 1, k = -1; ~i; --i) {
    for (; ~j && value2[j] >= value1[i]; --j) {
      cmax(k, tag2[value2[j]] == tv ? maxlen2[value2[j]] : -1);
    }
    if (~k && tag1[value1[i]] == tu) {
      cmax(answer, (long long) (maxlen1[value1[i]] + k + 1 + px) * value1[i]);
    }
  }
  for (int i = (int) value2.size() - 1, j = (int) value1.size() - 1, k = -1; ~i; --i) {
    for (; ~j && value1[j] >= value2[i]; --j) {
      cmax(k, tag1[value1[j]] == tu ? maxlen1[value1[j]] : -1);
    }
    if (~k && tag2[value2[i]] == tv) {
      cmax(answer, (long long) (maxlen2[value2[i]] + k + 1 + px) * value2[i]);
    }
  }
  int old = s, oldu = pu, oldv = pv, sizeu = s - size[pv], sizev = size[pv];
  visit[oldv] = true;
  solve(oldu, sizeu);
  visit[oldv] = false;
  visit[oldu] = true;
  solve(oldv, sizev);
  visit[oldu] = false;
}

int main() {
  scanf("%d", &n);
  m = n;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &value[i]);
    cmax(answer, (long long) value[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, 0);
  rebuild(1);
  solve(1, m);
  printf("%lld\n", answer);
  return 0;
}
