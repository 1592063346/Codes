#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, k, r[N];
char str[N];
vector<int> go[N];

int main() {
  scanf("%d%d%s", &n, &k, str + 1);
  vector<int> stack_t;
  for (int i = 1; i <= n; ++i) {
    if (str[i] == '(') {
      if (stack_t.size()) {
        go[stack_t.back()].push_back(i);
      }
      stack_t.push_back(i);
    } else {
      r[stack_t.back()] = i;
      stack_t.pop_back();
    }
  }
  priority_queue<int, vector<int>, greater<int>> que;
  for (int i = 1; i <= n; i = r[i] + 1) {
    que.push(i);
  }
  for (int i = 1; i <= (n - k) >> 1; ++i) {
    int x = que.top();
    que.pop();
    for (auto v : go[x]) {
      que.push(v);
    }
  }
  while (que.size()) {
    int x = que.top();
    que.pop();
    for (int i = x; i <= r[x]; ++i) {
      printf("%c", str[i]);
    }
  }
  return puts(""), 0;
}
