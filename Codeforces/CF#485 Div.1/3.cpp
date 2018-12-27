#include<bits/stdc++.h>

using namespace std;

const int N = 1 << 22;

int n, m, all, a[N];
bool tag[N], visit[N];

void dfs(int s) {
  visit[s] = true;
  if (tag[s] && !visit[all ^ s]) {
    dfs(all ^ s);
  }
  for (int i = 0; i < n; ++i) {
    if ((s >> i & 1) && (!visit[s ^ (1 << i)])) {
      dfs(s ^ (1 << i));
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  all = (1 << n) - 1;
  for (int i = 0; i < m; ++i) {
    scanf("%d", &a[i]);
    tag[a[i]] = true;
  }
  int answer = 0;
  for (int i = 0; i < m; ++i) {
    if (!visit[a[i]]) {
      dfs(a[i]);
      ++answer;
    }
  }
  printf("%d\n", answer);
  return 0;
}
