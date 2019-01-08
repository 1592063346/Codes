#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, m, visit[N];
vector<int> graph[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].push_back(v);
  }
  for (int i = 1; i <= n; ++i) {
    if (!visit[i]) {
      visit[i] = 1;
      for (auto j : graph[i]) {
        if (j > i) {
          visit[j] = -1;
        }
      }
    }
  }
  for (int i = n; i; --i) {
    if (visit[i] == 1) {
      for (auto j : graph[i]) {
        if (j < i) {
          visit[j] = -1;
        }
      }
    }
  }
  vector<int> answer;
  for (int i = 1; i <= n; ++i) {
    if (visit[i] == 1) {
      answer.push_back(i);
    }
  }
  printf("%d\n", answer.size());
  for (int i = 0; i < answer.size(); ++i) {
    printf("%d%c", answer[i], " \n"[i + 1 == answer.size()]);
  }
  return 0;
}
