#include<bits/stdc++.h>

using namespace std;

const int N = 3e6 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, node_cnt, answer, f[N];
char s[N];
vector<pair<int, int>> go[N];
bool is_tail[N];

void dfs(int u) {
  int number = 0, best = 0, second = 0;
  for (auto v : go[u]) {
    dfs(v.second);
    if (is_tail[v.second]) {
      ++number;
    }
  }
  for (auto v : go[u]) {
    if (is_tail[v.second]) {
      if (f[v.second] > best) {
        second = best;
        best = f[v.second];
      } else {
        cmax(second, f[v.second]);
      }
      cmax(f[u], f[v.second] + number - 1);
    }
  }
  f[u] += is_tail[u];
  cmax(answer, best + second + is_tail[u]);
  cmax(answer, best + number - 1 + is_tail[u]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s);
    int len = strlen(s), u = 0;
    for (int i = len - 1; ~i; --i) {
      int c = s[i] - 'a';
      bool found = false;
      for (auto v : go[u]) {
        if (v.first == c) {
          found = true;
          u = v.second;
        }
      }
      if (!found) {
        go[u].emplace_back(c, ++node_cnt);
        u = node_cnt;
      }
    }
    is_tail[u] = true;
  }
  dfs(0);
  printf("%d\n", answer);
  return 0;
}
