#include<bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

int n, p1[N], p2[N], ch[N][2], size[N];
long long k, value[N];

int main() {
  scanf("%d%I64d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    p1[i] = p2[i] = 1;
  }
  for (int i = 2; i <= n; ++i) {
    int u;
    long long v;
    scanf("%d%I64d", &u, &v);
    value[i] = value[u] ^ v;
  }
  long long answer = 0;
  for (int i = 61; ~i; --i) {
    int tt = i & 1 ? n : 0;
    for (int j = 1; j <= n; ++j) {
      int c = value[j] >> i & 1;
      if (!ch[p1[j]][c]) {
        ch[p1[j]][c] = ++tt;
        ch[tt][0] = ch[tt][1] = size[tt] = 0;
      }
      ++size[ch[p1[j]][c]];
    }
    long long same = 0;
    for (int j = 1; j <= n; ++j) {
      int c = value[j] >> i & 1;
      same += size[ch[p2[j]][c]];
    }
    bool rev = 0;
    if (k > same) {
      rev = 1;
      k -= same;
      answer |= 1ll << i;
    }
    for (int j = 1; j <= n; ++j) {
      int c = value[j] >> i & 1;
      p1[j] = ch[p1[j]][c];
      p2[j] = ch[p2[j]][c ^ rev];
    }
  }
  printf("%I64d\n", answer);
  return 0;
}
