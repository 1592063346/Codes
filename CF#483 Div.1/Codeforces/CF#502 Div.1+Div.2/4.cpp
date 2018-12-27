#include<bits/stdc++.h>

using namespace std;

int n, m, q, value[12], num[1 << 12], sum[1 << 12][105];
char s[20];

int main() {
  scanf("%d%d%d", &n, &m, &q);
  function<int ()> get_number = [&] () {
    int result = 0;
    for (int i = 0; i < n; ++i) {
      result |= (s[i] == '1') << i;
    }
    return result;
  };
  for (int i = 0; i < n; ++i) {
    scanf("%d", &value[i]);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%s", s);
    ++num[get_number()];
  }
  for (int i = 0; i < 1 << n; ++i) {
    for (int j = 0; j < 1 << n; ++j) {
      int result = 0;
      for (int k = 0; k < n; ++k) {
        if ((i >> k & 1) == (j >> k & 1)) {
          result += value[k];
        }
      }
      if (result <= 100) {
        sum[i][result] += num[j];
      }
    }
    for (int j = 1; j <= 100; ++j) {
      sum[i][j] += sum[i][j - 1];
    }
  }
  for (int i = 1; i <= q; ++i) {
    int x;
    scanf("%s%d", s, &x);
    printf("%d\n", sum[get_number()][x]);
  }
  return 0;
}
