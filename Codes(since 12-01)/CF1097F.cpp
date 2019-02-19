#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, M = 7001;

int n, q;
bitset<M> mu[M], factor[M], s[N];
bool mu_is_0[M];

int main() {
  for (int i = 2; i * i < M; ++i) {
    for (int j = 1; j * i * i < M; ++j) {
      mu_is_0[j * i * i] = true;
    }
  }
  for (int i = 1; i < M; ++i) {
    for (int j = i; j < M; j += i) {
      mu[i][j] = !mu_is_0[j / i];
    }
  }
  for (int i = 1; i < M; ++i) {
    for (int j = i; j < M; j += i) {
      factor[j][i] = 1;
    }
  }
  scanf("%d%d", &n, &q);
  while (q--) {
    int opt, x, y, z;
    scanf("%d", &opt);
    switch (opt) {
      case 1:
        scanf("%d%d", &x, &y);
        s[x] = factor[y];
        break;
      case 2:
        scanf("%d%d%d", &x, &y, &z);
        s[x] = s[y] ^ s[z];
        break;
      case 3:
        scanf("%d%d%d", &x, &y, &z);
        s[x] = s[y] & s[z];
        break;
      case 4:
        scanf("%d%d", &x, &y);
        printf("%d", (s[x] & mu[y]).count() & 1);
        break;
    }
  }
  return 0;
}
