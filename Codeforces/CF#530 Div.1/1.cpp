#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, inf = 0x3f3f3f3f;

void cmin(int& x, int y) {
  if (x > y) {
    x = y;
  }
}

int n, a[N];
long long answer;
vector<int> adj[N];

void dfs(int u, int p, int d, int s) {
  if (d & 1) {
    answer += a[u] - s;
    s = a[u];
  } else {
    int minv = inf;
    for (auto v : adj[u]) {
      if (v != p) {
        cmin(minv, a[v]);
      }
    }
    if (minv < s) {
      puts("-1");
      exit(0);
    } else if (minv != inf) {
      answer += minv - s;
      s = minv;
    }
  }
  for (auto v : adj[u]) {
    if (v != p) {
      dfs(v, u, d + 1, s);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    adj[x].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  dfs(1, 0, 1, 0);
  printf("%lld\n", answer);
  return 0;
}
