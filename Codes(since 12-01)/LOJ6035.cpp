#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int l, n, m, w[N], d[N];
long long t1[N], t2[N];

int main() {
  scanf("%d%d%d", &l, &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &w[i]);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &d[i]);
  }
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> que;
  for (int i = 1; i <= n; ++i) {
    que.push({w[i], i});
  }
  for (int i = 1; i <= l; ++i) {
    pair<long long, int> x = que.top();
    que.pop();
    t1[i] = x.first;
    que.push({x.first + w[x.second], x.second});
  }
  while (que.size()) {
    que.pop();
  }
  for (int i = 1; i <= m; ++i) {
    que.push({d[i], i});
  }
  for (int i = 1; i <= l; ++i) {
    pair<long long, int> x = que.top();
    que.pop();
    t2[i] = x.first;
    que.push({x.first + d[x.second], x.second});
  }
  long long answer = 0;
  for (int i = 1; i <= l; ++i) {
    answer = max(answer, t1[i] + t2[l - i + 1]);
  }
  printf("%lld\n", answer);
  return 0;
}
