#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

char s[N], t[N];
int num[3];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  memcpy(t, s, sizeof s);
  sort(t, t + n);
  for (int i = 0; i < n; ++i) {
    if (s[i] != t[i]) {
      return puts("NO"), 0;
    }
    ++num[s[i] - 'a'];
  }
  puts(num[0] && num[1] && num[2] && (num[0] == num[2] || num[1] == num[2]) ? "YES" : "NO");
  return 0;
}
