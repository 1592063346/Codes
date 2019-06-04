#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, a[N], son[N], d[N];
vector<int> values[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 2; i <= n; ++i) {
    cin >> a[i];
    ++son[a[i]];
  }
  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (!son[i]) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    sort(values[x].begin(), values[x].end());
    int t = 0;
    while (values[x].size()) {
      d[x] = max(d[x], ++t + values[x].back());
      values[x].pop_back();
    }
    values[a[x]].push_back(d[x]);
    if (--son[a[x]] == 0) {
      q.push(a[x]);
    }
  }
  cout << d[1] << '\n';
  return 0;
}
