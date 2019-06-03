#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, m, a[N], p[N], go[N];
bool visit[N];
long long k, answer[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    p[i] = i;
  }
  for (int i = n; i; --i) {
    a[i] -= a[i - 1];
  }
  cin >> m >> k;
  for (int i = 1, x; i <= m; ++i) {
    cin >> x;
    swap(p[x], p[x + 1]);
  }
  for (int i = 1; i <= n; ++i) {
    go[p[i]] = i;
  }
  for (int i = 1; i <= n; ++i) {
    if (!visit[i]) {
      vector<int> cycle(1, i);
      for (int x = go[i]; x != i; x = go[x]) {
        cycle.push_back(x);
      }
      for (auto x : cycle) {
        visit[x] = true;
      }
      int times = k % cycle.size(), y = cycle[0];
      while (times--) {
        y = go[y];
      }
      for (auto x : cycle) {
        answer[y] = a[x];
        y = go[y];
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    answer[i] += answer[i - 1];
    cout << answer[i] << '\n';
  }
  return 0;
}
