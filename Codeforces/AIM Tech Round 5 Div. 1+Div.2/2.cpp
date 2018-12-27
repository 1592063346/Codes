#include<bits/stdc++.h>

using namespace std;

const int N = 2250;

int n, m;
char sa[N], sb[N];

int main() {
  scanf("%d%d", &n, &m);
  int pos = 0;
  for (; n >= 4; n -= 4, ++pos) {
    sa[pos] = '5';
    sb[pos] = '4';
  }
  sa[pos] = '5';
  sb[pos] = '5';
  printf("%s\n%s\n", sa, sb);
  return 0;
}
