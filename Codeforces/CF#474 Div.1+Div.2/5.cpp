#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int n, value[N], root, all, size[N], max_subt[N], odd, even, odd_size, even_size, answer;
bool visit[N];
vector<int> graph[N];

void find_root(int u, int father) {
  size[u] = 1;
  max_subt[u] = 0;
  for (auto v : graph[u]) {
    if (v != father && !visit[v]) {
      find_root(v, u);
      size[u] += size[v];
      max_subt[u] = max(max_subt[u], size[v]);
    }
  }
  max_subt[u] = max(max_subt[u], all - size[u]);
  if (max_subt[u] < max_subt[root]) {
    root = u;
  }
}

void dfs_get_sum(int u, int father, int sum, int d, int type) {
  if (d & 1) {
    add(sum, value[u]);
  } else {
    sub(sum, value[u]);
  }
  if (d & 1) {
    odd_size += type;
    if (type == 1) {
      add(odd, sum);
    } else {
      sub(odd, sum);
    }
  } else {
    even_size += type;
    if (type == 1) {
      sub(even, sum);
    } else {
      add(even, sum);
    }
  }
  for (auto v : graph[u]) {
    if (v != father && !visit[v]) {
      dfs_get_sum(v, u, sum, d + 1, type);
    }
  }
}

void dfs_get_answer(int u, int father, int sum, int d) {
  if (d & 1) {
    sub(sum, value[u]);
  } else {
    add(sum, value[u]);
  }
  if (d & 1) {
    int now = (mod - sum) % mod;
    add(answer, mul(now, even_size));
    add(answer, even);
  } else {
    int now = sum;
    add(answer, mul(now, odd_size));
    add(answer, odd);
  }
  for (auto v : graph[u]) {
    if (v != father && !visit[v]) {
      dfs_get_answer(v, u, sum, d + 1);
    }
  }
}

void solve(int u) {
  visit[u] = true;
  odd = even = odd_size = even_size = 0;
  for (auto v : graph[u]) {
    if (!visit[v]) {
      dfs_get_sum(v, 0, 0, 1, 1);
    }
  }
  add(answer, mul(mul(value[u], even_size), 2));
  add(answer, mul(even, 2));
  for (auto v : graph[u]) {
    if (!visit[v]) {
      dfs_get_sum(v, 0, 0, 1, -1);
      dfs_get_answer(v, 0, (mod - value[u]) % mod, 0);
      dfs_get_sum(v, 0, 0, 1, 1);
    }
  }
  int old = all;
  for (auto v : graph[u]) {
    if (!visit[v]) {
      if (size[v] > size[u]) {
        all = old - size[u];
      } else {
        all = size[v];
      }
      root = 0;
      find_root(v, u);
      solve(root);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &value[i]);
    if (value[i] < 0) {
      value[i] = mod + value[i];
    }
    add(answer, value[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  max_subt[0] = n + 1;
  all = n;
  find_root(1, 0);
  solve(root);
  printf("%d\n", answer);
  return 0;
}
