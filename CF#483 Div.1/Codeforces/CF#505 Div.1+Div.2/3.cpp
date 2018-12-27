#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
char str[N];

char ch(int pos) {
  return str[pos % n];
}

int main() {
  scanf("%s", str);
  n = strlen(str);
  int cnt = 1, answer = 1;
  for (int i = 1; i < (n << 1); ++i) {
    if (ch(i) != ch(i - 1)) {
      answer = max(answer, ++cnt);
    } else {
      cnt = 1;
    }
  }
  printf("%d\n", min(answer, n));
  return 0;
}
