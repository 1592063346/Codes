#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, total[N];
char str[N];

int main() {
  scanf("%d%s", &n, str);
  int maxp = 0;
  for (int i = 0; i < n; ++i) {
    maxp = max(maxp, ++total[str[i] - 'a']);
  }
  puts(n == 1 || maxp > 1 ? "Yes" : "No");
  return 0;
}
