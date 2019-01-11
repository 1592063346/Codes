#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, size[N];
vector<int> graph[N], answer;

void dfs(int u, int father) {
  size[u] = 1;
  for (auto v : graph[u]) {
    if (v != father) {
      dfs(v, u);
      size[u] += size[v];
    }
  }
}

void print(int u, int father) {
  for (auto v : graph[u]) {
    if (v != father && !(size[v] & 1)) {
      print(v, u);
    }
  }
  answer.push_back(u);
  for (auto v : graph[u]) {
    if (v != father && (size[v] & 1)) {
      print(v, u);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    if (x) {
      graph[x].push_back(i);
      graph[i].push_back(x);
    }
  }
  dfs(1, 0);
  if (n & 1) {
    puts("YES");
    print(1, 0);
    for (int i = 0; i < answer.size(); ++i) {
      printf("%d\n", answer[i]);
    }
  } else {
    puts("NO");
  }
  return 0;
}
