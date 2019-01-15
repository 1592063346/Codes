#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

int n, m, f[N << 1];
char grid[N][N];

int find(int x) {
  return f[x] == x ? x : f[x] = find(f[x]);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", grid[i] + 1);
  }
  for (int i = 1; i <= n + m; ++i) {
    f[i] = i;
  }
  bool ok = true;
  for (int a = 1; a <= n; ++a) {
    for (int b = 1; b <= m; ++b) {
      if (grid[a][b] == '#') {
        f[find(a)] = find(n + b);
      }
    }
  }
  for (int a = 1; a <= n; ++a) {
    for (int b = 1; b <= m; ++b) {
      if (find(a) == find(n + b) && grid[a][b] != '#') {
        ok = false;
      }
    }
  }
  puts(ok ? "Yes" : "No");
  return 0;
}
