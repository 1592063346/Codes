#include<bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;

int n, l, r, a[N], b[N], f[N];

int main() {
  scanf("%d%d%d", &n, &l, &r);
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  vector<int> s0, s1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &b[i]);
    if (!b[i]) {
      s0.push_back(a[i]);
    } else {
      s1.push_back(a[i]);
    }
  }
  sort(s1.begin(), s1.end(), greater<int>());
  int t = r;
  r = sum - l;
  l = sum - t;
  memset(f, -1, sizeof f);
  f[0] = 0;
  for (auto v : s0) {
    for (int j = sum; j >= v; --j) {
      f[j] = max(f[j], f[j - v]);
    }
  }
  int answer = 0;
  for (auto v : s1) {
    for (int j = sum; j >= v; --j) {
      if (~f[j - v]) {
        f[j] = max(f[j], f[j - v] + (j >= l && j <= r));
        answer = max(answer, f[j]);
      }
    }
  }
  printf("%d\n", answer);
  return 0;
}
