#include<bits/stdc++.h>

using namespace std;

int main() {
  int n, m, q, x, y, answer = 0;
  scanf("%d%d%d", &n, &m, &q);
  vector<int> f(n + m + 1);
  for (int i = 1; i <= n + m; ++i) {
    f[i] = i;
  }
  function<int (int)> find = [&] (int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
  };
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d", &x, &y);
    f[find(x)] = find(y + n);
  }
  for (int i = 1; i <= n + m; ++i) {
    answer += f[i] == i;
  }
  printf("%d\n", --answer);
  return 0;
}
