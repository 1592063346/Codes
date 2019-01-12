#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

priority_queue<int> que;
int n, k1, k2, a[N], b[N];

int main() {
  scanf("%d%d%d", &n, &k1, &k2);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &b[i]);
    que.push(abs(a[i] - b[i]));
  }
  int k = k1 + k2;
  while (!que.empty() && k) {
    int x = que.top();
    que.pop();
    --k;
    que.push(abs(--x));
  }
  long long answer = 0;
  while (!que.empty()) {
    int x = que.top();
    que.pop();
    answer += (long long) x * x;
  }
  printf("%lld\n", answer);
  return 0;
}
