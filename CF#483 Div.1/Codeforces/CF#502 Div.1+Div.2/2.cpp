#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
char a[N], b[N];

int main() {
  scanf("%d%s%s", &n, a + 1, b + 1);
  int _01 = 0, _10 = 0, _11 = 0;
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    if (a[i] == '0' && b[i] == '1') {
      answer += _10;
      ++_01;
    } else if (a[i] == '1' && b[i] == '0') {
      answer += i - 1 - _10 - _11;
      ++_10;
    } else if (a[i] == '1' && b[i] == '1') {
      answer += i - 1 - _01 - _10 - _11;
      ++_11;
    } else {
      answer += _10 + _11;
    }
  }
  printf("%I64d\n", answer);
  return 0;
}
