#include<bits/stdc++.h>

using namespace std;

const int N = (1 << 20) + 10;

int n, a[N], s[2][N];

int main() {
  scanf("%d", &n);
  ++s[0][0];
  long long answer = 0;
  for (int i = 1, x = 0, v; i <= n; ++i) {
    scanf("%d", &v);
    x ^= v;
    answer += s[i & 1][x];
    ++s[i & 1][x];
  }
  printf("%lld\n", answer);
  return 0;
}
