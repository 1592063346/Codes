#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n, k;
char a[N], b[N];

int main() {
  scanf("%d%d%s%s", &n, &k, a + 1, b + 1);
  int all = 1;
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    all = min((long long) all << 1, (long long) INT_MAX);
    if (a[i] == 'b') {
      --all;
    }
    if (b[i] == 'a') {
      --all;
    }
    answer += min(all, k);
  }
  printf("%lld\n", answer);
  return 0;
}
