#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
long long a[N], bas[N], xorsum;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    xorsum ^= a[i];
  }
  vector<int> position;
  for (int i = 0; i < 62; ++i) {
    if (xorsum >> i & 1) {
      position.push_back(i);
    }
  }
  for (int i = 0; i < 62; ++i) {
    if (!(xorsum >> i & 1)) {
      position.push_back(i);
    }
  }
  function<void (long long)> insert = [&] (long long value) {
    for (int i = 61; ~i; --i) {
      int p = position[i];
      if (value >> p & 1) {
        if (bas[p]) {
          value ^= bas[p];
        } else {
          bas[p] = value;
          for (int j = 0; j < i; ++j) {
            int q = position[j];
            if (bas[p] >> q & 1) {
              bas[p] ^= bas[q];
            }
          }
          for (int j = i + 1; j < 62; ++j) {
            int q = position[j];
            if (bas[q] >> p & 1) {
              bas[q] ^= bas[p];
            }
          }
          return;
        }
      }
    }
  };
  for (int i = 1; i <= n; ++i) {
    insert(a[i]);
  }
  long long answer = xorsum;
  for (int i = 0; i < 62; ++i) {
    answer ^= bas[i];
  }
  printf("%lld\n", answer);
  return 0;
}
