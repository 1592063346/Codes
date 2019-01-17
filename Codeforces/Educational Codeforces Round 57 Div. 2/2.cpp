#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, mod = 998244353;

int n, type_pre[N], type_suf[N];
char s[N];

bool more_bits(int x) {
  return !(!x || !(x - (x & -x)));
}

int main() {
  scanf("%d%s", &n, s + 1);
  for (int i = 1; i <= n; ++i) {
    type_pre[i] = type_pre[i - 1] | (1 << s[i] - 'a');
  }
  for (int i = n; i; --i) {
    type_suf[i] = type_suf[i + 1] | (1 << s[i] - 'a');
  }
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    int l = i, r = n + 1;
    while (l != r) {
      int mid = l + r >> 1;
      if (more_bits(type_pre[i - 1] | type_suf[mid + 1])) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    answer = (answer + n - l + 1) % mod;
  }
  printf("%d\n", answer);
  return 0;
}
