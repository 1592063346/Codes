#include<bits/stdc++.h>
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

const int N = 1e5 + 10, block = 1667;

int n, m, p, a[N], in_block[N];
bitset<N> f[61][10];

int main() {
  scanf("%d%d%d", &n, &m, &p);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    in_block[i] = (i - 1) / block + 1;
  }
  for (int i = in_block[n]; i; --i) {
    for (int j = (i - 1) * block + 1; j <= min(n, i * block); ++j) {
      f[i][0][a[j]] = 1;
    }
    for (int j = i + 1; j < i + 10 && j <= in_block[n]; ++j) {
      f[i][j - i] = f[i][j - i - 1] | f[j][0];
    }
  }
  int last_answer = 0;
  while (m--) {
    int k;
    scanf("%d", &k);
    bitset<N> answer;
    while (k--) {
      int l, r;
      scanf("%d%d", &l, &r);
      if (p && last_answer) {
        l = (l ^ last_answer) % n + 1;
        r = (r ^ last_answer) % n + 1;
        if (l > r) {
          swap(l, r);
        }
      }
      if (in_block[l] == in_block[r]) {
        for (int i = l; i <= r; ++i) {
          answer[a[i]] = 1;
        }
      } else {
        for (int i = l; i <= in_block[l] * block; ++i) {
          answer[a[i]] = 1;
        }
        for (int i = (in_block[r] - 1) * block + 1; i <= r; ++i) {
          answer[a[i]] = 1;
        }
        l = in_block[l] + 1;
        r = in_block[r] - 1;
        for (; l + 10 <= r; l += 10) {
          answer |= f[l][9];
        }
        if (l <= r) {
          answer |= f[l][r - l];
        }
      }
    }
    printf("%d\n", last_answer = answer.count());
  }
  return 0;
}
