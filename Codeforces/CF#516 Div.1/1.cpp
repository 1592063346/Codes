#include<bits/stdc++.h>

using namespace std;

#define rg register

const int N = 1e5 + 10;

int n, _count[27];
char s[N];

int main() {
  scanf("%d%s", &n, s);
  for (rg int i = 0; i < n; ++i) {
    ++_count[s[i] - 'a'];
  }
  for (rg int i = 0; i < 26; ++i) {
    for (rg int j = 0; j < _count[i]; ++j) {
      printf("%c", 'a' + i);
    }
  }
  return puts(""), 0;
}
