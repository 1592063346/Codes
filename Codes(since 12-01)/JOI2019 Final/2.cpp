#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, c[N];
pair<int, int> s[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &s[i].first, &s[i].second);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &c[i]);
  }
  sort(s + 1, s + 1 + n, [&] (const pair<int, int>& x, const pair<int, int>& y) {
    return x.second == y.second ? x.first < y.first : x.second < y.second;
  });
  sort(c + 1, c + 1 + m);
  int answer = 0;
  for (int i = n, j = m; i && j; --i) {
    if (s[i].first <= c[j]) {
      --j;
      ++answer;
    }
  }
  printf("%d\n", answer);
  return 0;
}
